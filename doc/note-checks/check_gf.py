"""Checks the formulas of the Generating functions section (exact Fraction power series, brute-force counting).
Run: python3 doc/note-checks/check_gf.py"""
import itertools, random
from fractions import Fraction as Fr
from math import comb, factorial

N = 14                                      # series length (coefficients 0 .. N-1)
def S(c): return [Fr(x) for x in (list(c) + [0] * N)[:N]]
def add(a, b): return [x + y for x, y in zip(a, b)]
def sub(a, b): return [x - y for x, y in zip(a, b)]
def scal(a, c): return [x * c for x in a]
def mono(k): return [Fr(1) if i == k else Fr(0) for i in range(N)]            # x^k
def mul(a, b):
    r = [Fr(0)] * N
    for i, x in enumerate(a):
        if x:
            for j in range(N - i): r[i + j] += x * b[j]
    return r
def inv(a):
    b = [Fr(0)] * N; b[0] = 1 / a[0]
    for n in range(1, N): b[n] = -sum(a[k] * b[n - k] for k in range(1, n + 1)) / a[0]
    return b
def deriv(a): return [a[i + 1] * (i + 1) for i in range(N - 1)] + [Fr(0)]
def integ(a): return [Fr(0)] + [a[i] / (i + 1) for i in range(N - 1)]
def exp_(f):                                # f[0] = 0:  n b_n = sum_k k f_k b_{n-k}
    assert f[0] == 0
    b = [Fr(0)] * N; b[0] = Fr(1)
    for n in range(1, N): b[n] = sum(k * f[k] * b[n - k] for k in range(1, n + 1)) / n
    return b
def log_(f): assert f[0] == 1; return integ(mul(deriv(f), inv(f)))
def power(a, k):
    r = S([1])
    for _ in range(k): r = mul(r, a)
    return r
def compose(a, b):                          # a(b(x)), b[0] = 0
    r = [Fr(0)] * N; pw = S([1])
    for i in range(N): r = add(r, scal(pw, a[i])); pw = mul(pw, b)
    return r
def egf(c): return [Fr(c[n], factorial(n)) for n in range(N)]                 # sequence -> EGF coefficients
def seq(a): return [a[n] * factorial(n) for n in range(N)]                     # EGF -> sequence
def ints(a): assert all(x.denominator == 1 for x in a), a; return [int(x) for x in a]
def euler_log(F, sign):                     # sum_{j >= 1} sign^(j+1) F(x^j) / j
    return [sum(Fr(sign ** (j + 1), j) * (F[n // j] if n % j == 0 else 0) for j in range(1, n + 1)) for n in range(N)]
X, ONE = mono(1), mono(0)
GEOM = inv(sub(ONE, X))                      # 1 / (1 - x)

# ---- dictionary
rng = random.Random(1)
a = [rng.randint(-5, 5) for _ in range(N)]; b = [rng.randint(-5, 5) for _ in range(N)]
A, B = S(a), S(b)
assert ints(mul(A, B)) == [sum(a[i] * b[n - i] for i in range(n + 1)) for n in range(N)]                       # OGF product = convolution
assert seq(mul(egf(a), egf(b))) == [sum(comb(n, i) * a[i] * b[n - i] for i in range(n + 1)) for n in range(N)]  # EGF product = binomial convolution
assert ints(mul(A, GEOM)) == [sum(a[:n + 1]) for n in range(N)]                                               # prefix sums: A / (1 - x)
assert ints(mul(X, A))[1:] == a[:N - 1]                                                                         # a_{n-1}: x A
assert ints(A[1:] + [Fr(0)])[:N - 1] == a[1:]                                                                   # a_{n+1}: (A - a_0) / x
assert ints(mul(X, deriv(A))) == [n * a[n] for n in range(N)]                                                   # n a_n: x A'
Ah = egf(a)
assert seq(deriv(Ah))[:N - 1] == a[1:]                                                                          # EGF: a_{n+1} is A'
assert seq(integ(Ah))[1:] == a[:N - 1]                                                                          # EGF: a_{n-1} is the integral
assert seq(mul(X, deriv(Ah))) == [n * a[n] for n in range(N)]                                                   # EGF: n a_n is x A'
print("dictionary (products, binomial convolution, shifts, n a_n, prefix sums): ok")

# ---- common series
for k in range(1, 6): assert ints(power(GEOM, k)) == [comb(n + k - 1, k - 1) for n in range(N)]
fib = [0, 1]
while len(fib) < N: fib.append(fib[-1] + fib[-2])
assert ints(mul(X, inv(S([1, -1, -1])))) == fib
C = S([comb(2 * n, n) // (n + 1) for n in range(N)])
assert C == add(ONE, mul(X, mul(C, C)))                                                                         # C = 1 + x C^2
central = S([comb(2 * n, n) for n in range(N)])
assert mul(central, central) == inv(S([1, -4]))                                                                 # (1/sqrt(1-4x))^2 = 1/(1-4x)
assert mul(sub(ONE, scal(mul(X, C), 2)), central) == ONE                                                        # sqrt(1-4x) = 1 - 2xC, so C = (1 - sqrt(1-4x)) / (2x)
P = ONE
for k in range(1, N): P = mul(P, inv(sub(ONE, mono(k))))
assert ints(P) == [1, 1, 2, 3, 5, 7, 11, 15, 22, 30, 42, 56, 77, 101]                                           # partitions
print("1/(1-x)^k, Fibonacci, Catalan, 1/sqrt(1-4x), partitions: ok")

# ---- EGFs
assert ints(seq(GEOM)) == [factorial(n) for n in range(N)]                                                      # permutations
D = mul(exp_(scal(X, -1)), GEOM)
der_brute = [sum(1 for p in itertools.permutations(range(n)) if all(p[i] != i for i in range(n))) for n in range(8)]
assert ints(seq(D))[:8] == der_brute and ints(seq(D))[:8] == [1, 0, 1, 2, 9, 44, 265, 1854]                     # derangements e^-x / (1-x)
ex1 = sub(exp_(X), ONE)
def bell_brute(n):                          # restricted growth strings
    def go(i, m): return 1 if i == n else sum(go(i + 1, max(m, v + 1)) for v in range(m + 1))
    return go(0, 0)
bell = ints(seq(exp_(ex1)))
assert bell[:9] == [bell_brute(n) for n in range(9)] and bell[:8] == [1, 1, 2, 5, 15, 52, 203, 877]              # Bell: e^(e^x - 1)
st2 = [[0] * (N + 1) for _ in range(N + 1)]; c1 = [[0] * (N + 1) for _ in range(N + 1)]; st2[0][0] = c1[0][0] = 1
for n in range(1, N):
    for k in range(1, n + 1):
        st2[n][k] = st2[n - 1][k - 1] + k * st2[n - 1][k]; c1[n][k] = c1[n - 1][k - 1] + (n - 1) * c1[n - 1][k]
for k in range(0, 6):
    assert ints(seq(scal(power(ex1, k), Fr(1, factorial(k)))))[:N] == [st2[n][k] for n in range(N)]             # (e^x - 1)^k / k!
    assert ints(seq(scal(power(log_(GEOM), k), Fr(1, factorial(k)))))[:N] == [c1[n][k] for n in range(N)]       # (-ln(1-x))^k / k!
inv_gf = ints(seq(exp_(add(X, scal(mul(X, X), Fr(1, 2))))))
invol_brute = [sum(1 for p in itertools.permutations(range(n)) if all(p[p[i]] == i for i in range(n))) for n in range(9)]
assert inv_gf[:9] == invol_brute and inv_gf[:8] == [1, 1, 2, 4, 10, 26, 76, 232]                                 # involutions: e^(x + x^2/2)
bern = seq(inv(ex1[1:] + [Fr(0)]))                                                                              # x / (e^x - 1)
assert bern[:7] == [1, Fr(-1, 2), Fr(1, 6), 0, Fr(-1, 30), 0, Fr(1, 42)]
print("EGFs: permutations, derangements, Bell, Stirling 2nd and 1st kind, involutions, Bernoulli: ok")

# ---- symbolic method
T = S([0])                                   # rooted labeled trees: T = x e^T
for _ in range(N): T = mul(X, exp_(T))
assert ints(seq(T))[1:10] == [n ** (n - 1) for n in range(1, 10)]
def cycle_lengths_ok(p, lens):
    seen = [False] * len(p)
    for i in range(len(p)):
        if not seen[i]:
            l, j = 0, i
            while not seen[j]: seen[j] = True; j = p[j]; l += 1
            if l not in lens: return False
    return True
lens = {1, 3, 4}                             # all cycle lengths in a set: exp(sum_{k in S} x^k / k)
g = ints(seq(exp_([Fr(1, n) if n in lens else Fr(0) for n in range(N)])))
assert g[:8] == [sum(1 for p in itertools.permutations(range(n)) if cycle_lengths_ok(p, lens)) for n in range(8)]
assert ints(seq(log_(GEOM)))[1:9] == [factorial(n - 1) for n in range(1, 9)]                                     # a cycle: ln 1/(1-x) = (n-1)! labelings
f = [0] + [rng.randint(0, 3) for _ in range(N - 1)]                                                              # f_k objects of size k
F_ = S(f)
multiset = ONE
for k in range(1, N): multiset = mul(multiset, power(inv(sub(ONE, mono(k))), f[k]))
assert multiset == exp_(euler_log(F_, 1))                                                                        # Euler transform: prod (1-x^k)^(-f_k) = exp sum F(x^j)/j
subsets = ONE
for k in range(1, N): subsets = mul(subsets, power(add(ONE, mono(k)), f[k]))
assert subsets == exp_(euler_log(F_, -1))                                                                        # sets: prod (1+x^k)^(f_k)
Tt = S([0])                                  # unlabeled rooted trees: T = x exp(sum_j T(x^j) / j)
for _ in range(N): Tt = mul(X, exp_(euler_log(Tt, 1)))
def trees(n, memo={}):                       # brute force: canonical forms of rooted trees with n vertices
    if n in memo: return memo[n]
    if n == 1: memo[n] = {()}; return memo[n]
    out = set()
    def parts(rem, maxsz, cur):
        if rem == 0: out.add(tuple(sorted(cur))); return
        for s in range(min(rem, maxsz), 0, -1):
            for t in trees(s): parts(rem - s, s, cur + [t])
    parts(n - 1, n - 1, [])
    memo[n] = out
    return out
assert ints(Tt)[1:9] == [len(trees(n)) for n in range(1, 9)] == [1, 1, 2, 4, 9, 20, 48, 115]
print("symbolic method: labeled trees n^(n-1), cycle lengths in S, ln 1/(1-F), Euler transform (multisets, sets), unlabeled rooted trees: ok")

# ---- computing
c = [3, -2, 5]; seqv = [1, 2, 3]            # a_n = 3 a_{n-1} - 2 a_{n-2} + 5 a_{n-3}  <->  Q = 1 - 3x + 2x^2 - 5x^3
for n in range(3, N): seqv.append(sum(c[i] * seqv[n - 1 - i] for i in range(3)))
Q = S([1] + [-ci for ci in c]); Pn = mul(S(seqv), Q)
assert all(Pn[i] == 0 for i in range(3, N)) and ints(mul(Pn, inv(Q))) == seqv
for phi_coef in ([1, 1], [1, 1, 1], [1, 2, 0, 1], [1, 0, 3, 1]):                # Lagrange inversion for f = x phi(f)
    phi = S(phi_coef); f_ = S([0])
    for _ in range(N): f_ = mul(X, compose(phi, f_))
    for k in range(1, 5):
        fk = power(f_, k)
        for n in range(k, N - 1): assert fk[n] == Fr(k, n) * power(phi, n)[n - k], (phi_coef, k, n)
    H = S([0, 1, 2, 5, -1, 3]); Hf = compose(H, f_)
    for n in range(1, N - 1): assert Hf[n] == Fr(1, n) * mul(deriv(H), power(phi, n))[n - 1]
F2 = S([0] + [rng.randint(-3, 3) for _ in range(N - 1)]); b2 = exp_(F2)                                        # b = e^F: n b_n = sum k f_k b_{n-k}
assert all(n * b2[n] == sum(k * F2[k] * b2[n - k] for k in range(1, n + 1)) for n in range(1, N))
print("rational GF <-> recurrence, Lagrange inversion ([x^n] f^k and [x^n] H(f)), n b_n = sum k f_k b_{n-k}: ok")
