"""Checks the formulas of the Number theory notes: Garner, generalized Euler, lifting the exponent, linear Diophantine equations.
Run: python3 doc/note-checks/check_numbertheory.py"""
import random, math
from math import gcd, log2, ceil

random.seed(2)

# ---- Garner
def garner(a, m):
    k = len(m); x = [0] * k
    for i in range(k):
        t = a[i] % m[i]
        for j in range(i):
            t = (t - x[j]) * pow(m[j], -1, m[i]) % m[i]
        x[i] = t
    return x
def eval_mod(x, m, M):      # Horner from the top: x[0] + m[0] (x[1] + m[1] (x[2] + ...))
    r = x[-1]
    for i in range(len(x) - 2, -1, -1): r = (r * m[i] + x[i]) % M
    return r % M
primes = [p for p in range(2, 200) if all(p % q for q in range(2, int(p ** .5) + 1))]
for it in range(2000):
    k = random.randint(1, 5)
    m = []
    while len(m) < k:                      # pairwise coprime, not necessarily prime
        c = random.randint(2, 300)
        if all(gcd(c, d) == 1 for d in m): m.append(c)
    prod = math.prod(m); X = random.randrange(prod)
    a = [X % mi for mi in m]
    x = garner(a, m)
    assert all(0 <= x[i] < m[i] for i in range(k))
    assert sum(x[i] * math.prod(m[:i]) for i in range(k)) == X
    M = random.randint(2, 10 ** 9)
    assert eval_mod(x, m, M) == X % M
print("Garner: mixed radix digits, the O(k^2) loop and Horner evaluation mod M: ok")

# ---- generalized Euler: a^b = a^(b mod phi + phi) (mod m) for b >= log2 m
def phi(n):
    r, p, x = n, 2, n
    while p * p <= x:
        if x % p == 0:
            while x % p == 0: x //= p
            r -= r // p
        p += 1
    if x > 1: r -= r // x
    return r
bad = 0
for m in range(1, 400):
    ph = phi(m)
    for a in range(0, 60):
        for b in range(ceil(log2(m)) if m > 1 else 0, 70):
            if pow(a, b, m) != pow(a, b % ph + ph, m): bad += 1
assert bad == 0, bad
# and show that the condition is needed: a smaller b can fail
fails = [(a, b, m) for m in range(2, 60) for a in range(m) for b in range(0, ceil(log2(m)))
         if pow(a, b, m) != pow(a, b % phi(m) + phi(m), m)]
assert fails
print("generalized Euler a^b = a^(b mod phi(m) + phi(m)) mod m for b >= log2 m: ok (fails below it, e.g. %s)" % (fails[0],))

# ---- lifting the exponent
def v(p, n):
    n = abs(n); c = 0
    while n % p == 0: n //= p; c += 1
    return c
for it in range(20000):
    p = random.choice([3, 5, 7, 11, 13]); n = random.randint(1, 30)
    y = random.randint(1, 60); x = y + p * random.randint(1, 20)      # p | x - y
    if x % p == 0 or y % p == 0 or x == y: continue
    assert v(p, x ** n - y ** n) == v(p, x - y) + v(p, n)
    if n % 2:                                                          # odd n, p | x + y
        y2 = p * random.randint(1, 20) - x
        if y2 > 0 and y2 % p and x % p: assert v(p, x ** n + y2 ** n) == v(p, x + y2) + v(p, n)
for it in range(20000):
    x = random.randrange(1, 200, 2); y = random.randrange(1, 200, 2); n = random.randint(1, 20)
    if x == y: continue
    if n % 2: assert v(2, x ** n - y ** n) == v(2, x - y)
    else: assert v(2, x ** n - y ** n) == v(2, x - y) + v(2, x + y) + v(2, n) - 1
    if (x - y) % 4 == 0: assert v(2, x ** n - y ** n) == v(2, x - y) + v(2, n)
print("lifting the exponent (odd p, minus and plus; p = 2 odd/even n, 4 | x - y): ok")

# ---- linear Diophantine ax + by = c
def egcd(a, b):
    if b == 0: return (a, 1, 0)
    g, x, y = egcd(b, a % b); return (g, y, x - (a // b) * y)
def cdiv(a, b): return -((-a) // b)            # ceil for b > 0
def solve(a, b, c, L, R, L2, R2):
    """number of solutions with L <= x <= R and L2 <= y <= R2 (a, b != 0), and the t giving min x + y"""
    g, xg, yg = egcd(abs(a), abs(b))
    if c % g: return 0, None
    x0 = xg * (c // g) * (1 if a > 0 else -1); y0 = yg * (c // g) * (1 if b > 0 else -1)
    assert a * x0 + b * y0 == c
    sx, sy = b // g, a // g                    # x = x0 + sx t, y = y0 - sy t
    lo, hi = -10 ** 18, 10 ** 18
    for (s, base, l, r, sign) in ((sx, x0, L, R, 1), (sy, y0, L2, R2, -1)):
        s *= sign                              # coordinate = base + s t
        if s > 0: lo = max(lo, cdiv(l - base, s)); hi = min(hi, (r - base) // s)
        else: lo = max(lo, cdiv(r - base, s)); hi = min(hi, (l - base) // s)   # dividing by s < 0 flips
    cnt = max(0, hi - lo + 1)
    best = None
    if cnt:
        slope = sx - sy * (-1) * (-1)          # (x + y) = x0 + y0 + (sx - sy) t
        slope = sx - sy
        best = lo if slope >= 0 else hi
    return cnt, best
def brute(a, b, c, L, R, L2, R2):
    sols = [(x, y) for x in range(L, R + 1) for y in range(L2, R2 + 1) if a * x + b * y == c]
    return len(sols), (min(x + y for x, y in sols) if sols else None)
for it in range(6000):
    a = random.choice([i for i in range(-9, 10) if i]); b = random.choice([i for i in range(-9, 10) if i])
    c = random.randint(-30, 30); L = random.randint(-15, 5); R = L + random.randint(0, 25); L2 = random.randint(-15, 5); R2 = L2 + random.randint(0, 25)
    cnt, t = solve(a, b, c, L, R, L2, R2); bc, bm = brute(a, b, c, L, R, L2, R2)
    assert cnt == bc, (a, b, c, L, R, L2, R2, cnt, bc)
    if cnt:
        g = gcd(abs(a), abs(b)); gg, xg, yg = egcd(abs(a), abs(b))
        x0 = xg * (c // g) * (1 if a > 0 else -1); y0 = yg * (c // g) * (1 if b > 0 else -1)
        assert x0 + (b // g) * t + y0 - (a // g) * t == bm, (a, b, c, t, bm)
print("linear Diophantine: solvability, x = x0 + (b/g) t, counting in a range with floor/ceil, min x + y at an end of the t range: ok")
