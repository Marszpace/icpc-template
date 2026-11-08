"""Checks the claims of the Python note on the interpreter running it (the judge has CPython 3.12.3 and PyPy 7.3.15 = Python 3.9.18).
Run: python3.12 doc/note-checks/check_python.py ; pypy3 doc/note-checks/check_python.py   (run-all.sh does both)"""
import math, platform, subprocess, sys, time
from decimal import Decimal, getcontext, ROUND_HALF_UP, ROUND_HALF_EVEN, Overflow, MAX_EMAX
from fractions import Fraction

PYPY = platform.python_implementation() == 'PyPy'
print("checking on", platform.python_implementation(), sys.version.split()[0])

# ---- big integers and the int <-> str limit (4300 digits by default, both interpreters)
try: int('9' * 5000); raise SystemExit("expected the 4300 digit limit")
except ValueError: pass
try: str(10 ** 5000); raise SystemExit("expected the 4300 digit limit")
except ValueError: pass
sys.set_int_max_str_digits(0)
assert len(str(int('9' * 5000))) == 5000
t = time.time(); assert len(str(10 ** 1000000)) == 1000001; assert time.time() - t < 10   # about 0.5 s on both

# ---- math / int helpers
n = (10 ** 16 + 1) ** 2 - 1
assert math.isqrt(n) == 10 ** 16 and int(math.sqrt(n)) != math.isqrt(n)       # float sqrt is wrong, isqrt is exact
for x in (0, 1, 2, 3, 10 ** 30, 10 ** 100 + 12345, 2 ** 400 - 1):
    r = math.isqrt(x); assert r * r <= x < (r + 1) * (r + 1)
assert (math.gcd(12, 18), math.lcm(4, 6), math.comb(50, 25), math.perm(10, 3), math.prod([1, 2, 3, 4]), math.factorial(20)) == (6, 12, 126410606437752, 720, 24, 2432902008176640000)
assert pow(3, 10 ** 18, 10 ** 9 + 7) == pow(3, 10 ** 18 % (10 ** 9 + 6), 10 ** 9 + 7)
assert pow(3, -1, 10 ** 9 + 7) * 3 % (10 ** 9 + 7) == 1
try: pow(2, -1, 4); raise SystemExit("pow(2, -1, 4) must fail")
except ValueError: pass
assert divmod(-7, 2) == (-4, 1) and -7 // 2 == -4 and -7 % 3 == 2               # floor division, unlike C++
assert (255).bit_length() == 8 and (255).bit_count() == 8 and int('ff', 16) == 255 and format(10, 'b') == '1010' and int('1010', 2) == 10
assert hasattr(math, 'cbrt') == (not PYPY)                                      # math.cbrt does not exist on PyPy 3.9

# ---- decimal
getcontext().prec = 50
ref = str(math.isqrt(2 * 10 ** 100))                                           # sqrt(2) = 1.41421356...
assert str(Decimal(2).sqrt()).replace('.', '')[:49] == ref[:49]
assert str(Decimal(10).ln()).startswith('2.30258509299404568401799145468436420760110148862')
assert str(Decimal(1).exp()).startswith('2.718281828459045235360287471352662497757247093')    # e, 49 digits (the 50th is rounded)
assert Decimal(1000).log10() == 3
assert Decimal(0.1) != Decimal('0.1') and str(Decimal('0.1')) == '0.1'         # the float constructor copies the binary value
assert Decimal('2.675').quantize(Decimal('0.01'), rounding=ROUND_HALF_UP) == Decimal('2.68')
assert Decimal('2.665').quantize(Decimal('0.01')) == Decimal('2.66') == Decimal('2.665').quantize(Decimal('0.01'), rounding=ROUND_HALF_EVEN)
assert Decimal('2.5').quantize(Decimal('1')) == 2                              # the default rounding is half even
getcontext().prec = 20
try: Decimal(3 * 10 ** 6).exp(); raise SystemExit("expected Overflow")
except Overflow: pass
getcontext().Emax = MAX_EMAX
assert str(Decimal(3 * 10 ** 6).exp()).startswith('2.79067817')               # fine once Emax is raised
getcontext().prec = 2000; t = time.time(); Decimal(2).sqrt(); Decimal(10).ln(); Decimal(1).exp(); assert time.time() - t < 10

# ---- fractions
f = Fraction(3, 4) + Fraction(1, 6)
assert f == Fraction(11, 12) and Fraction(3.14159).limit_denominator(100) == Fraction(311, 99)

# ---- recursion (each in a fresh interpreter)
def rec(mode, depth, stack=27):
    code = {
        'plain': 'def d(n): return 0 if n == 0 else 1 + d(n - 1)',
        'lru': 'import functools\n@functools.lru_cache(None)\ndef d(n): return 0 if n == 0 else 1 + d(n - 1)',
    }[mode.split('-')[0]]
    lim = 2 * depth + 100                                # lru_cache adds a frame per call
    if mode.endswith('thread'):
        prog = f"import sys, threading\nsys.setrecursionlimit({lim})\nthreading.stack_size(2**{stack})\n{code}\nout = []\nt = threading.Thread(target=lambda: out.append(d({depth})))\nt.start(); t.join()\nprint(out[0] if out else 'died')"
    else:
        prog = f"import sys\nsys.setrecursionlimit({lim})\n{code}\nprint(d({depth}))"
    r = subprocess.run([sys.executable, '-c', prog], capture_output=True, text=True, timeout=300)
    return r.returncode == 0 and r.stdout.strip() == str(depth)
assert rec('plain-thread', 100000, 27)                                          # the thread idiom works on both
if PYPY:
    assert rec('plain', 10000) and not rec('plain', 100000)                      # PyPy: the main thread overflows its stack
    assert not rec('plain-thread', 1000000, 28) and rec('plain-thread', 1000000, 29)   # depth 1e6 needs a 512 MB stack
    assert rec('lru-thread', 100000, 27)                                         # lru_cache is fine in a big thread
else:
    assert rec('plain', 1000000)                                                 # CPython 3.11+: the limit is enough
    if sys.version_info >= (3, 12):
        assert not rec('lru', 10000) and not rec('lru-thread', 10000, 28)        # but recursion through lru_cache stops near depth 3300
        assert rec('lru', 3000)
print("Python note: every claim reproduced on", platform.python_implementation(), sys.version.split()[0])
