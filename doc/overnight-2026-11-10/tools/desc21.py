# Item 21: proposed descriptions at three levels.
#   G (gentle): readable, one short "what it does" plus everything needed to use it.
#   L (lean):   the team's rule: only what someone who knows the topic needs (conventions,
#               indexing, preconditions, interface); non-trivial topics keep a few words of
#               what the function does. Some facts move into trailing code comments (C).
#   M (minimal): shortest that still lets you use the file; more moved to comments; the two
#               text-only files are folded into neighbours (see FOLD).
# Missing level -> same as the previous one. '' = no description.
# U / T: Usage / Time overrides per level (missing = keep; '' = drop).
# C: (old line, new line) code-comment moves, applied in L and M (comments do not change hashes).

D = {}

# ---------------- data structures ----------------
D['data-structures/OrderStatisticTree.h'] = dict(
    G=r"Set (not multiset) with \texttt{find\_by\_order} and \texttt{order\_of\_key}. For a map, change \texttt{null\_type}.",
    L=r"Not a multiset. Map: change \texttt{null\_type}.")
D['data-structures/HashMap.h'] = dict(
    G=r"\texttt{unordered\_map} API, about 3x faster, 1.5x memory. Initial capacity must be a power of 2.",
    L=r"\texttt{unordered\_map} API, 3x faster. Capacity: a power of 2.",
    M=r"Capacity: a power of 2.")
D['data-structures/SegmentTree.h'] = dict(
    G=r"0-indexed, point update, query $[b, e)$. Max by default: change \texttt{T}, \texttt{f}, \texttt{unit}.",
    L=r"Change \texttt{T}, \texttt{f}, \texttt{unit}.", M='',
    C=[("struct Tree {", "struct Tree { // 0-indexed")])
D['data-structures/LazySegTreeBlock.h'] = dict(
    G=r"""The part of \texttt{LazySeg} you edit. Default: range chmin and add; sum / max / count of max (beats).
Tag $x \mapsto \min(x, c) + a$: chmin $v$ = \texttt{\{v, 0\}}, add $v$ = \texttt{\{INF, v\}}; \texttt{S()} is a leaf with value 0.
\texttt{comp} must keep tags closed, \texttt{app} must act on the aggregate as the tag acts on each element;
\texttt{ok(s, x)}: can $x$ be applied to all of $s$ at once (else it recurses).
\textbf{Add only:} \texttt{ok} = 1, drop \texttt{se, cnt}.
\textbf{Min query:} add \texttt{mn}, \texttt{op} takes min, \texttt{app}: \texttt{mn = min(mn, x.c) + x.a}.
\textbf{Chmax:} store $-a_i$, negate updates and answers.
\textbf{Set, add, mul:} \texttt{L} = $(a, b)$: $x \mapsto ax + b$, \texttt{id} = \texttt{\{1, 0\}}, set $v$ = \texttt{\{0, v\}}, add = \texttt{\{1, v\}}, mul = \texttt{\{v, 0\}},
\texttt{app}: \texttt{a*s + b*len} (sum) or \texttt{a*s + b} (max, $a \ge 0$), \texttt{comp(x, y)} = \texttt{\{x.a*y.a, x.a*y.b + x.b\}}, \texttt{ok} = 1.
\textbf{Chmin, chmax, add, set; max / min only:} \texttt{L} = $(a, lo, hi)$: $x \mapsto \min(\max(x + a, lo), hi)$, set $v$ = \texttt{\{0, v, v\}},
\texttt{comp(x, y)}: $a$ = \texttt{x.a + y.a}, \texttt{lo, hi} = \texttt{y.lo, y.hi} plus \texttt{x.a}, clamped to \texttt{[x.lo, x.hi]}.""",
    L=r"""Default: chmin + add, sum / max / count of max (beats). Tag $x \mapsto \min(x, c) + a$: chmin \texttt{\{v, 0\}}, add \texttt{\{INF, v\}}.
\texttt{app} acts on the aggregate as the tag on each element; \texttt{ok(s, x)}: apply without recursing?
\textbf{Add only:} \texttt{ok} = 1, drop \texttt{se, cnt}. \textbf{Min query:} add \texttt{mn}, \texttt{app}: \texttt{mn = min(mn, x.c) + x.a}.
\textbf{Chmax:} store $-a_i$. \textbf{Set, add, mul:} \texttt{L} = $(a, b)$: $ax + b$, \texttt{id \{1, 0\}}, set \texttt{\{0, v\}}, add \texttt{\{1, v\}}, mul \texttt{\{v, 0\}},
\texttt{app}: \texttt{a*s + b*len} (sum), \texttt{a*s + b} (max, $a \ge 0$), \texttt{comp}: \texttt{\{x.a*y.a, x.a*y.b + x.b\}}, \texttt{ok} = 1.
\textbf{Chmin, chmax, add, set (max / min only):} \texttt{L} = $(a, lo, hi)$: $\min(\max(x + a, lo), hi)$, set \texttt{\{0, v, v\}},
\texttt{comp}: \texttt{x.a + y.a}, and \texttt{y.lo, y.hi} plus \texttt{x.a}, clamped to \texttt{[x.lo, x.hi]}.""",
    M=r"""Default: chmin + add, sum / max / count of max (beats); tag $\min(x, c) + a$. \texttt{ok(s, x)}: apply without recursing?
\textbf{Add:} \texttt{ok} = 1, drop \texttt{se, cnt}. \textbf{Min:} \texttt{mn = min(mn, x.c) + x.a}. \textbf{Chmax:} store $-a_i$.
\textbf{Set, add, mul:} $(a, b)$: $ax + b$, set \texttt{\{0, v\}}; \texttt{app} \texttt{a*s + b*len}; \texttt{comp} \texttt{\{x.a*y.a, x.a*y.b + x.b\}}.
\textbf{Clamp (max / min only):} $(a, lo, hi)$: $\min(\max(x + a, lo), hi)$; \texttt{comp}: shift \texttt{y.lo, y.hi} by \texttt{x.a}, clamp to \texttt{[x.lo, x.hi]}.""")
D['data-structures/LazySegTree.h'] = dict(
    G=r"""Lazy segment tree; edit only \texttt{LazySegTreeBlock.h}. \texttt{app(s, x, len)} applies tag $x$ to a segment of length \texttt{len};
\texttt{comp(x, y)} = $y$ first, then $x$. Ranges $[l, r)$. \texttt{maxRight(l, f)}: largest $r$ with \texttt{f(query(l, r))}, for monotone $f$ with \texttt{f(e())} true.""",
    L=r"""Edit only the block. Ranges $[l, r)$; \texttt{comp(x, y)}: $y$ first, then $x$.
\texttt{maxRight(l, f)}: largest $r$ with \texttt{f(query(l, r))} ($f$ monotone, \texttt{f(e())} true).""",
    M=r"""Ranges $[l, r)$. \texttt{maxRight(l, f)}: largest $r$ with \texttt{f(query(l, r))}, $f$ monotone.""",
    T=dict(L=r"O(\log N), beats with add $O(\log^2 N)$ amortized"))
D['data-structures/PersistentSegmentTree.h'] = dict(
    G=r"""Sums over positions $[0, n)$; a version is its root, version 0 is empty. \texttt{upd} adds $x$ at $p$ and returns the new root;
\texttt{query(v, l, r)} sums $[l, r)$; \texttt{kth(a, b, k)}: $k$-th smallest (0-indexed) position of the multiset \texttt{b} $-$ \texttt{a}.""",
    L=r"""\texttt{upd} returns the new root. \texttt{kth(a, b, k)}: $k$-th smallest (0-indexed) position in version \texttt{b} minus \texttt{a}.""",
    M=r"",
    C=[("struct PST {", "struct PST { // version = root, 0 = empty; ranges [l, r)"),
       ("\tint kth(int a, int b, ll k) {", "\tint kth(int a, int b, ll k) { // k-th (0-idx) pos of b - a")])
D['data-structures/UnionFindRollback.h'] = dict(
    G=r"""DSU with undo: \texttt{rollback(t)} to an earlier \texttt{time()}; skip \texttt{st}, \texttt{time}, \texttt{rollback} if not needed.
With parity, \texttt{join(a, b, w)} also demands $\texttt{par(a)} \oplus \texttt{par(b)} = w$; if it returns false with a different parity, the demand is contradictory.""",
    L=r"""Undo: \texttt{rollback(time())}. If \texttt{join} returns false (already joined), check $\texttt{par(a)} \oplus \texttt{par(b)} = w$ yourself.""",
    M=r"",
    C=[("\tbool join(int a, int b, int w = 0) {", "\tbool join(int a, int b, int w = 0) { // par(a)^par(b) = w")])
D['data-structures/DynCon.h'] = dict(
    G=r"""Offline dynamic connectivity. \texttt{add(l, r, a, b)}: edge $a$--$b$ during times $[l, r)$. \texttt{run(f)} calls \texttt{f(t)} for $t = 0..T-1$
with \texttt{uf} = the graph at time $t$; \texttt{bad} = number of edges closing an odd cycle (bipartite iff 0). Toggles: map of start times.""",
    L=r"""Offline. Edge $a$--$b$ alive in $[l, r)$; in \texttt{f(t)}, \texttt{uf} is the graph at time $t$, bipartite iff \texttt{bad == 0}.""",
    M=r"""Edge alive in $[l, r)$; \texttt{f(t)} sees \texttt{uf} at time $t$; bipartite iff \texttt{bad == 0}.""")
D['data-structures/Matrix.h'] = dict(G=r"Square matrices with \texttt{*} and power \texttt{\textasciicircum}.", L='',
    U=dict(M=r"Matrix<int, 3> A; A.d = {{{{1,2,3}}, {{4,5,6}}, {{7,8,9}}}};" + "\n" + r"vec = (A^N) * vec; // vec: array<int, 3>"))
D['data-structures/LineContainer.h'] = dict(
    G=r"Add lines $kx + m$, query the maximum at $x$ (convex hull trick).",
    L=r"Lines $kx + m$, query the max at $x$.", M='',
    C=[("\tll query(ll x) {", "\tll query(ll x) { // max of kx + m")])
D['data-structures/LiChao.h'] = dict(
    G=r"""Minimum of lines $kx + m$ at integer $x \in [0, n)$; \texttt{addSeg} only on $x \in [a, b)$. Max: negate $k$, $m$ and the answer.
\texttt{query} returns \texttt{INF} if no line covers $x$.""",
    L=r"Min at integer $x \in [0, n)$; \texttt{addSeg} on $[a, b)$. Max: negate. \texttt{INF} if no line.",
    M='',
    C=[("struct LiChao {", "struct LiChao { // min at integer x in [0, n); max: negate"),
       ("\tll query(int x) {", "\tll query(int x) { // INF if no line covers x")])
D['data-structures/Treap.h'] = dict(
    G=r"""Implicit treap (a sequence, split / merge by position) keeping subtree sums with lazy range add and reverse.
\texttt{go(t, l, r, f)} runs \texttt{f} on the node holding positions $[l, r)$.""",
    L=r"Implicit treap (by position) with sums, lazy add and reverse.",
    M=r"Implicit treap, sums, lazy add and reverse.")
D['data-structures/FenwickTree.h'] = dict(
    G=r"0-indexed; \texttt{query(pos)} sums $[0, pos)$; \texttt{lower\_bound} needs non-negative values.",
    L=r"\texttt{lower\_bound} needs non-negative values.", M='',
    C=[("struct FT {", "struct FT { // 0-indexed")],
    T=dict(L=r"O(\log N)"))
D['data-structures/FenwickTree2d.h'] = dict(
    G=r"0-indexed; \texttt{query(x, y)} sums $[0, x) \times [0, y)$. Points to update must be known: \texttt{fakeUpdate} each, then \texttt{init()}.",
    L=r"Points to update must be known in advance.", M='',
    C=[("struct FT2 {", "struct FT2 { // 0-idx; fakeUpdate() all points, then init()"),
       ("\tll query(int x, int y) {", "\tll query(int x, int y) { // sum over [0, x) x [0, y)")],
    T=dict(L=r"O(\log^2 N)"))
D['data-structures/RMQ.h'] = dict(G=r"Sparse table; \texttt{query(a, b)} is the min of $V[a..b)$ in $O(1)$.", L='')
D['data-structures/MoQueries.h'] = dict(
    G=r"""Mo's algorithm on intervals $[l, r)$ (\texttt{mo}) or tree paths (\texttt{moTree}); fill in \texttt{add}, \texttt{del}, \texttt{calc}.
Values on tree edges: \texttt{step} toggles the edge $(a, c)$ and the initial \texttt{add} goes (keep \texttt{in}).""",
    L=r"Queries $[l, r)$. Values on tree edges: \texttt{step} toggles the edge $(a, c)$, no initial \texttt{add} (keep \texttt{in}).",
    M=r"Values on tree edges: \texttt{step} toggles edge $(a, c)$, no initial \texttt{add}.")

# ---------------- numerical ----------------
D['numerical/Polynomial.h'] = dict(G='')
D['numerical/PolyInterpolate.h'] = dict(
    G=r"Coefficients of the degree $n-1$ polynomial through $(x_i, y_i)$: $p(x) = \sum a_i x^i$. Precision: pick $x_k = c\cos(k\pi/(n-1))$.",
    L=r"Returns $a$ with $p(x) = \sum a_i x^i$. Precision: $x_k = c\cos(k\pi/(n-1))$.",
    M=r"Returns $a$, $p(x) = \sum a_i x^i$.")
D['numerical/LagrangeInterpolation.h'] = dict(
    G=r"""$f(x) \bmod p$ from $y_i = f(i)$, $i < n$, $\deg f < n$, $p$ prime $> n$.
Sums of powers: $\sum_{i \le x} i^k$ has degree $k+1$, so give it $k+2$ prefix sums.""",
    L=r"Input $f(0), \dots, f(n-1)$, $\deg f < n$, mod prime $> n$. $\sum_{i \le x} i^k$: give $k+2$ values.",
    M=r"Input $f(0), \dots, f(n-1)$, $\deg f < n$.")
D['numerical/BerlekampMassey.h'] = dict(
    G=r"Shortest linear recurrence (in \texttt{linearRec}'s format) of a sequence mod prime, from its first $2n$ terms. For guessing recurrences.",
    L=r"Needs the first $2n$ terms (mod prime); output fits \texttt{linearRec}.",
    M=r"Needs $2n$ terms; output fits \texttt{linearRec}.")
D['numerical/LinearRecurrence.h'] = dict(
    G=r"$k$-th term (0-indexed) of $S[i] = \sum_j S[i-j-1]\,tr[j]$, given $S[0..n-1]$ and $tr[0..n-1]$, mod \texttt{mod}.",
    L=r"$S[i] = \sum_j S[i-j-1]\,tr[j]$; $k$-th term, 0-indexed.")
D['numerical/BostanMori.h'] = dict(
    G=r"""Same as \texttt{linearRec} mod 998244353 (values in $[0, mod)$), $O(n \log n \log k)$:
halves $k$ via $P(x)Q(-x) / Q(x)Q(-x)$.""",
    L=r"Same interface as \texttt{linearRec}, mod 998244353.")
D['numerical/HillClimbing.h'] = dict(G=r"Minimizes $f$ over the plane from \texttt{start}; fine for unimodal $f$.", L=r"Minimizes $f$ (unimodal).")
D['numerical/Integrate.h'] = dict(
    G=r"Simpson's rule with $2n$ intervals; error $\propto h^4$, check that the result is stable when $n$ changes.",
    L=r"Simpson, error $O(h^4)$.", M=r"Simpson.")
D['numerical/Determinant.h'] = dict(G=r"Doubles. Destroys the matrix.", L=r"Destroys the matrix.")
D['numerical/IntDeterminant.h'] = dict(
    G=r"Determinant mod any \texttt{mod} (also composite) by Euclid row steps. Remove the \texttt{\% mod} for exact integers.",
    L=r"Any \texttt{mod}, also composite. Drop the mods for exact integers.",
    M=r"Any \texttt{mod}, also composite.")
D['numerical/SolveLinear.h'] = dict(
    G=r"Solves $Ax = b$. Returns rank, or $-1$ if no solution (an arbitrary one if rank $< m$). Destroys $A$, $b$.",
    L=r"Returns rank, or $-1$ if none. Destroys $A$, $b$.")
D['numerical/SolveLinear2.h'] = dict(G=r"Changes to SolveLinear to get back all uniquely determined values of $x$:")
D['numerical/SolveLinearBinary.h'] = dict(G=r"Over $\mathbb F_2$. Returns rank, or $-1$ if none. Destroys $A$, $b$.")
D['numerical/SolveLinearMod.h'] = dict(
    G=r"Mod prime, entries in $[0, mod)$. Returns rank, or $-1$ if none; free variables are 0. Destroys $A$, $b$.",
    M=r"Mod prime, entries in $[0, mod)$. Rank or $-1$; free variables 0.")
D['numerical/XorBasis.h'] = dict(
    G=r"""\texttt{insert} returns whether $x$ was independent, \texttt{has(x)}: $x$ in the span, \texttt{best(x)}: max $x \oplus s$ over the span,
\texttt{kth(k)}: $k$-th smallest of the span (0-indexed, $k < 2^{rk}$).""",
    L=r"", M=r"",
    C=[("\tull best(ull x = 0) {", "\tull best(ull x = 0) { // max x ^ s over the span"),
       ("\tull kth(ull k) {", "\tull kth(ull k) { // k-th smallest, 0-indexed, k < 2^rk")])
D['numerical/MatrixInverse.h'] = dict(
    G=r"""Returns rank; $A^{-1}$ is stored in $A$ if rank $= n$. Mod $p^k$: start from the inverse mod $p$ and repeat
$A^{-1} \gets A^{-1}(2I - AA^{-1})$, doubling $k$ each time.""",
    L=r"Returns rank; result in $A$ if rank $= n$. Mod $p^k$: from $X = A^{-1} \bmod p$ repeat $X \gets X(2I - AX)$.",
    M=r"Returns rank; result in $A$ if rank $= n$.")
D['numerical/FastFourierTransform.h'] = dict(
    G=r"""Convolution with doubles: \texttt{conv(a, b)}$[x] = \sum a[i]b[x-i]$. Exact while $(\sum a_i^2 + \sum b_i^2)\log_2 N < 9\cdot10^{14}$
(in practice $10^{16}$), else NTT / FFTMod. By hand: FFT, multiply, divide by $n$, reverse(start+1, end), FFT back.""",
    L=r"""Convolution (doubles), exact while $(\sum a_i^2 + \sum b_i^2)\log_2 N < 9\cdot10^{14}$.
By hand: FFT, multiply, divide by $n$, reverse(start+1, end), FFT.""",
    M=r"Convolution; exact while $(\sum a_i^2 + \sum b_i^2)\log_2 N < 9\cdot10^{14}$.")
D['numerical/FastFourierTransformMod.h'] = dict(
    G=r"Convolution modulo any \texttt{M}, inputs in $[0, M)$, while $N\log_2 N \cdot M < 8.6\cdot10^{14}$ (in practice $10^{16}$).",
    L=r"Convolution mod any $M$, inputs in $[0, M)$; needs $N \log_2 N \cdot M < 8.6\cdot10^{14}$.")
D['numerical/NumberTheoreticTransform.h'] = dict(
    G=r"""Convolution mod a prime $2^a b + 1$ with result size $\le 2^a$ (default 998244353; any modulus: FFTMod). Inputs in $[0, mod)$.
By hand: NTT, multiply, divide by $n$, reverse(start+1, end), NTT back.""",
    L=r"Convolution mod 998244353 (or a prime $2^a b + 1$, result size $\le 2^a$). Inputs in $[0, mod)$.",
    M=r"Convolution mod \texttt{mod}. Inputs in $[0, mod)$.")
D['numerical/FastSubsetTransform.h'] = dict(
    G=r"AND / OR / XOR convolution $c[z] = \sum_{x \oplus y = z} a[x]b[y]$ (choose the line in \texttt{FST}); size a power of 2.",
    L=r"AND / OR / XOR convolution (choose in \texttt{FST}); size a power of 2.")
D['numerical/PolyOps.h'] = dict(
    G=r"""Power series mod $x^n$ and \texttt{mod} (NTT prime); results have exactly $n$ terms. \texttt{polyInv}: $a_0 \ne 0$;
\texttt{polyLog}, \texttt{polySqrt}: $a_0 = 1$; \texttt{polyExp}: $a_0 = 0$; \texttt{polyPow(a, k, n)}: any $a$, $k \le 10^{18}$.
\texttt{polyDivMod(a, b)} returns $(q, r)$, needs \texttt{b.back()} $\ne 0$.""",
    L=r"""Mod $x^n$, $n$ terms out. Inv: $a_0 \ne 0$; Log, Sqrt: $a_0 = 1$; Exp: $a_0 = 0$; Pow: any $a$.
\texttt{polyDivMod}: \texttt{b.back()} $\ne 0$.""")

# ---------------- number theory ----------------
D['number-theory/ModularArithmetic.h'] = dict(
    G=r"\texttt{mint<mod>} for a prime $mod < 2^{30}$: arithmetic, comparisons, I/O, \texttt{fpow(a, p)}, \texttt{inverse(a)}; \texttt{(int)a} is the value.",
    L=r"Prime $mod < 2^{30}$. \texttt{fpow(a, p)}, \texttt{inverse(a)}, \texttt{(int)a}.",
    M=r"Prime $mod < 2^{30}$.")
D['number-theory/ModInverse.h'] = dict(G=r"Inverses of $1..LIM-1$; LIM $\le$ mod, mod prime.", M=r"LIM $\le$ mod, mod prime.")
D['number-theory/ModPow.h'] = dict(G='')
D['number-theory/ModLog.h'] = dict(
    G=r"Smallest $x > 0$ with $a^x \equiv b \pmod m$ (any $m$), or $-1$. \texttt{modLog(a, 1, m)} is the order of $a$.",
    L=r"Smallest $x > 0$, or $-1$. \texttt{modLog(a, 1, m)}: order of $a$.")
D['number-theory/ModSum.h'] = dict(
    G=r"\texttt{modsum(to, c, k, m)} $= \sum_{i=0}^{to-1} (ki + c) \bmod m$; \texttt{divsum}: the same with $\lfloor (ki + c)/m \rfloor$.")
D['number-theory/ModMulLL.h'] = dict(
    G=r"$ab \bmod c$ and $a^b \bmod c$ for $0 \le a, b \le c \le 7.2\cdot10^{18}$.",
    M=r"$a, b \le c \le 7.2\cdot10^{18}$.")
D['number-theory/ModSqrt.h'] = dict(
    G=r"$x$ with $x^2 \equiv a \pmod p$, $p$ prime (Tonelli-Shanks); $-x$ is the other root; asserts if there is none.",
    L=r"$x^2 \equiv a \pmod p$, $p$ prime; $-x$ is the other root; asserts if none.",
    M=r"Prime $p$; asserts if no root.")
D['number-theory/PrimitiveRoot.h'] = dict(
    G=r"""Smallest primitive root of a prime $p$; $p - 1$ is factored by trial division, so $p \lesssim 10^{12}$ (else use \texttt{Factor}).
998244353: 3, $10^9 + 7$: 5.""",
    L=r"Prime $p \lesssim 10^{12}$ (trial division; else \texttt{Factor}). 998244353: 3, $10^9 + 7$: 5.")
D['number-theory/FastEratosthenes.h'] = dict(G=r"Primes below LIM; also fills \texttt{isPrime}.", L=r"Primes below LIM.")
D['number-theory/MillerRabin.h'] = dict(G=r"Deterministic for $n < 7\cdot10^{18}$.")
D['number-theory/Factor.h'] = dict(G=r"Prime factors with multiplicity, in any order (Pollard rho).", L=r"Prime factors with multiplicity, unsorted.")
D['number-theory/euclid.h'] = dict(
    G=r"Returns $\gcd(a, b)$ and sets $ax + by = \gcd$; if coprime, $x = a^{-1} \bmod b$.",
    L=r"$ax + by = \gcd(a, b)$ (returned).", M='',
    C=[("ll euclid(ll a, ll b, ll &x, ll &y) {", "ll euclid(ll a, ll b, ll &x, ll &y) { // ax + by = gcd")])
D['number-theory/CRT.h'] = dict(
    G=r"$x \equiv a \pmod m$, $x \equiv b \pmod n$, $0 \le x < \mathrm{lcm}$ if $|a| < m$, $|b| < n$; asserts if none. Needs $mn < 2^{62}$.",
    L=r"$0 \le x < \mathrm{lcm}(m, n)$ if $|a| < m$, $|b| < n$; asserts if none. $mn < 2^{62}$.")
D['number-theory/ExLucas.h'] = dict(
    G=r"""$\binom{n}{k} \bmod m$ for any $m < 2^{31}$ and $n \le mx$ (extended Lucas: per prime power, $n!$ without the factors $p$, then CRT).""",
    L=r"$\binom{n}{k} \bmod m$, any $m < 2^{31}$, $n \le mx$.")
D['number-theory/phiFunction.h'] = dict(
    G=r"""Sieve of Euler's $\phi$ below LIM. $\phi(n) = n \prod_{p \mid n} (1 - 1/p)$, $\sum_{d \mid n} \phi(d) = n$,
$\sum_{k \le n, \gcd(k, n) = 1} k = n\phi(n)/2$ ($n > 1$). Euler: $a^{\phi(n)} \equiv 1 \pmod n$ if $\gcd(a, n) = 1$.""",
    L=r"Sieve of $\phi$ below LIM. $\sum_{d \mid n} \phi(d) = n$; $\sum_{k \le n, \gcd(k, n) = 1} k = n\phi(n)/2$ ($n > 1$).",
    M=r"Sieve of $\phi$ below LIM.")
D['number-theory/Lucy.h'] = dict(
    G=r"""$\sum_{p \le v} f(p)$ over primes, for all $v = \lfloor n/i \rfloor$; $f$ completely multiplicative (\texttt{1}: count, \texttt{p}: sum),
\texttt{g(v)} $= f(2) + \dots + f(v)$ in closed form. The result type is \texttt{g}'s (\texttt{ull}: mod $2^{64}$).""",
    L=r"""$\sum_{p \le v} f(p)$, $v = \lfloor n/i \rfloor$; $f$ completely multiplicative, \texttt{g(v)} $= f(2) + \dots + f(v)$. Result type: \texttt{g}'s.""",
    M=r"""\texttt{g(v)} $= f(2) + \dots + f(v)$, $f$ completely multiplicative; type from \texttt{g}.""")
D['number-theory/DuSieve.h'] = dict(
    G=r"""Prefix sums $\Phi$ (128-bit) and $M$ of $\phi$ and $\mu$ at any $v = \lfloor n/i \rfloor$ or $v \le n^{2/3}$.
Any $f$ with $f * g = h$ and known prefix sums $G$, $H$: $S_f(v) = (H(v) - \sum_{d \ge 2} g(d) S_f(\lfloor v/d \rfloor))/g(1)$.""",
    L=r"""$\Phi$ (128-bit) and $M$ at $v = \lfloor n/i \rfloor$ or $v \le n^{2/3}$.
Other $f$, $f * g = h$: $S_f(v) = (H(v) - \sum_{d \ge 2} g(d) S_f(\lfloor v/d \rfloor))/g(1)$.""",
    M=r"""At $v = \lfloor n/i \rfloor$ or $v \le n^{2/3}$; $\Phi$ is 128-bit.""")

# ---------------- combinatorial ----------------
D['combinatorial/IntPerm.h'] = dict(
    G=r"Rank of a permutation of $0..n-1$ in lexicographic order, and back (\texttt{intToPerm(r, n)}); $n \le 20$. Unknown size: \texttt{radixToPerm}.",
    L=r"$n \le 20$. Unknown size: \texttt{radixToPerm}.", M=r"$n \le 20$.")
D['combinatorial/multinomial.h'] = dict(G=r"$(\sum k_i)! / \prod k_i!$, exact while it fits in \texttt{ll}.", L=r"$(\sum k_i)! / \prod k_i!$.")
D['combinatorial/RadixConversion.h'] = dict(
    G=r"""Bijective base conversion, most significant first: the $k$-th sequence (by length, then lexicographic) over $[0, a)$
goes to the $k$-th over $[0, b)$, $2 \le a, b < 2^{31}$: no length or leading zeros to store, about $|x| \log_b a$ digits.
\texttt{radixToPerm} / \texttt{permToRadix}: the same onto permutations (size from the data). Fixed size $n$:
\texttt{radixToPerm} of the base $2^{31}-1$ digits of $r + 0! + \dots + (n-1)!$.""",
    L=r"""$k$-th sequence (by length, then lex) over $[0, a)$ $\to$ $k$-th over $[0, b)$, most significant first.
\texttt{radixToPerm} / \texttt{permToRadix}: the same with permutations (size from the data).""",
    M=r"""$k$-th (length, then lex) $\to$ $k$-th; \texttt{radixToPerm}: onto permutations.""")

# ---------------- graph ----------------
D['graph/PushRelabel.h'] = dict(G=r"Max flow, fast in practice. Flow on an edge: its positive \texttt{f}.", L=r"Flow on an edge: its positive \texttt{f}.")
D['graph/MinCostMaxFlow.h'] = dict(
    G=r"Negative costs: call \texttt{setpi} first (no negative cycles). Flow on an edge: its positive \texttt{flow}.",
    M=r"Negative costs: \texttt{setpi} first.")
D['graph/Dinic.h'] = dict(G=r"Max flow.", L='',
    T=dict(G=r"O(VE\log U) with $U = \max|cap|$; $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt V E)$ for matching"),
    FOLDM=r"Min cut: \texttt{leftOfMinCut} (reachable from $s$ in the residual graph).")
D['graph/MinCut.h'] = dict(
    G=r"After max flow, the $s$ side of a min cut = vertices reachable from $s$ through edges with positive residual capacity.",
    L=r"$s$ side of a min cut: reachable from $s$ in the residual graph.")
D['graph/GlobalMinCut.h'] = dict(G=r"Stoer-Wagner on an adjacency matrix; returns (weight, one side).", L=r"Adjacency matrix; returns (weight, one side).")
D['graph/GomoryHu.h'] = dict(
    G=r"Gomory-Hu tree of an undirected graph: max flow $u$--$v$ = min edge on the tree path.",
    L=r"Max flow $u$--$v$ = min edge on the tree path.")
D['graph/HopcroftKarp.h'] = dict(
    G=r"$g$: neighbours of each left vertex; $r$: all $-1$, size of the right side. Returns the matching size; $r[i]$ = match of right vertex $i$ or $-1$.",
    L=r"$g$: left adjacency; $r$: all $-1$, size of the right side, gets the match of each right vertex.",
    M=r"$r$: all $-1$, size of the right side; gets the matches.")
D['graph/MinimumVertexCover.h'] = dict(
    G=r"Bipartite; in the output left vertex $i$ is $i$, right vertex $j$ is $n + j$. Size = max matching; complement = max independent set.",
    L=r"Complement: max independent set.", M='',
    C=[("vi cover(vector<vi>& g, int n, int m) {", "vi cover(vector<vi>& g, int n, int m) { // right j -> n+j")])
D['graph/WeightedMatching.h'] = dict(
    G=r"Min-cost bipartite matching using every left node, $N \le M$; returns (cost, match), L[i] $\to$ R[match[i]]. Max: negate the costs.",
    L=r"Min cost, every left node matched, $N \le M$. Max: negate.",
    M=r"Min cost, $N \le M$.")
D['graph/GeneralMatching.h'] = dict(G=r"Maximum matching (randomized, fails with probability $N/mod$).", L=r"Randomized, fails with probability $N/mod$.")
D['graph/SCC.h'] = dict(G=r"Tarjan.", L='',
    U=dict(L=r"""scc(g, [\&](vi\& v) { ... }) visits the components
in reverse topological order. comp[i]: component of i
(edges only go to lower indices); ncomps: their number.""",
           M=r"""scc(g, [\&](vi\& v) {...}); // reverse topological order
comp[i]: component (edges go to lower comp), ncomps."""))
D['graph/BiconnectedComponents.h'] = dict(
    G=r"Calls \texttt{f} with the edge ids of each biconnected component; an edge in none is a bridge.",
    L=r"Edge ids per component; an edge in none is a bridge.",
    U=dict(M=r"""int eid = 0; ed.resize(N); // per edge (a, b):
ed[a].emplace_back(b, eid); ed[b].emplace_back(a, eid++);
bicomps([\&](const vi\& edgelist) {...});"""))
D['graph/BlockCutTree.h'] = dict(
    G=r"""Nodes $0..n-1$ are the vertices, then one node per biconnected component (a bridge is one with 2 vertices), adjacent to its vertices;
a forest. Cut vertex iff tree degree $> 1$; $w$ separates $u$, $v$ iff it is a cut vertex on their tree path.""",
    L=r"Vertices $0..n-1$, then one node per block (bridges too). Cut vertex iff tree degree $> 1$.")
D['graph/2sat.h'] = dict(G=r"Negation: \texttt{\textasciitilde x}.", L='',
    T=dict(L=r"O(N + E)"),
    U=dict(M=r"""TwoSat ts(n); ts.either(0, \tilde3); // 0 or not 3
ts.setValue(2); ts.atMostOne({0, \tilde1, 2});
ts.solve(); // true iff solvable; values in ts.values"""))
D['graph/EulerWalk.h'] = dict(
    G=r"""Euler path / cycle from \texttt{src}, undirected or directed. Lists of (dest, edge id); an undirected edge has one id both ways.
Returns the nodes (src at both ends for a cycle), empty if none. Edge ids: also push \texttt{.second}.""",
    L=r"Lists of (dest, edge id), one id for both directions. Returns the node list, empty if impossible.")
D['graph/MaximalCliques.h'] = dict(G=r"Calls \texttt{f} with every maximal clique. Symmetric bitset matrix, no self-edges.", L=r"Symmetric bitset matrix, no self-edges.")
D['graph/MaximumClique.h'] = dict(
    G=r"Symmetric bitset matrix, no self-edges. Max independent set: a max clique of the complement.",
    L=r"Symmetric bitset matrix, no self-edges.",
    T=dict(L=r"About 1 s for $n = 155$, $p = .9$; faster when sparse"),
    FOLDM=r"Max independent set: clique of the complement (bipartite: \texttt{MinimumVertexCover}).")
D['graph/MaximumIndependentSet.h'] = dict(
    G=r"Max clique of the complement. Bipartite: complement of \texttt{MinimumVertexCover}.")
D['graph/BinaryLifting.h'] = dict(G=r"Jump tables for $k$-th ancestors and LCA; the root's parent must be itself.", L=r"The root's parent must be itself.")
D['graph/LCA.h'] = dict(G=r"Euler tour + RMQ; root 0, adjacency list (directed or undirected).", L=r"Root 0; adjacency list, directed or undirected.")
D['graph/CompressTree.h'] = dict(
    G=r"Virtual tree of a subset: the subset plus pairwise LCAs. Returns (parent index, original node); the root is first and is its own parent.",
    L=r"Virtual tree; returns (parent index, original node), root first (own parent).")
D['graph/HLD.h'] = dict(
    G=r"""Performs HLD over a \texttt{LazySeg} (edit its block): updates take \texttt{L}, queries return \texttt{S}, values start as \texttt{S()}.
Full adjacency list, root 0. \texttt{VALS\_EDGES}: values on the edges.""",
    L=r"Performs HLD. Full adjacency list, root 0; ops use \texttt{LazySeg}'s \texttt{L} / \texttt{S}. \texttt{VALS\_EDGES}: values on edges.",
    M=r"Root 0; \texttt{LazySeg}'s \texttt{L} / \texttt{S}. \texttt{VALS\_EDGES}: values on edges.")
D['graph/CentroidDecomposition.h'] = dict(
    G=r"""\texttt{run(f)} calls \texttt{f(c)} per centroid $c$; a DFS from $c$ skipping \texttt{dead} then visits exactly its component.
\texttt{cpar}: the centroid tree (root $-1$).""",
    L=r"In \texttt{f(c)}, a DFS from $c$ skipping \texttt{dead} visits its component. \texttt{cpar}: centroid tree.")
D['graph/DsuOnTree.h'] = dict(
    G=r"""Small to large: \texttt{add(v)} / \texttt{rem(v)} put one vertex into / out of a global structure;
\texttt{query(v)} runs when it holds exactly the subtree of $v$.""",
    L=r"\texttt{query(v)} runs when exactly the subtree of $v$ is \texttt{add}ed (\texttt{add}, \texttt{rem}: one vertex).")
D['graph/LinkCutTree.h'] = dict(G=r"Forest with \texttt{link}, \texttt{cut} (must stay a forest) and \texttt{connected}.", L=r"Must stay a forest.")
D['graph/DirectedMST.h'] = dict(
    G=r"Minimum arborescence rooted at $r$: (cost, parents), cost $-1$ if none.",
    L=r"Root $r$; returns (cost, par), $-1$ if none.")

# ---------------- geometry ----------------
D['geometry/Point.h'] = dict(G=r"\texttt{T}: double or long long (avoid int).")
D['geometry/lineDistance.h'] = dict(
    G=r"Signed distance from p to the line through a and b, positive on the left of $a \to b$; a==b gives nan.",
    L=r"Signed, positive left of $a \to b$.")
D['geometry/SegmentDistance.h'] = dict(G=r"Distance from p to the segment se.", L=r"",
    U=dict(M=r"bool onSegment = segDist(a,b,p) < 1e-10;"))
D['geometry/SegmentIntersection.h'] = dict(
    G=r"One point, none, or the two endpoints of the common part. With Point<ll> the point is wrong if not integral. Products of 3 coordinates.",
    L=r"One point, none, or the ends of the overlap. Point<ll>: only integral points.",
    U=dict(M=r"vector<P> inter = segInter(s1,e1,s2,e2);"))
D['geometry/lineIntersection.h'] = dict(
    G=r"\{1, p\} if unique, \{0, (0,0)\} if parallel, \{-1, (0,0)\} if the same line. With Point<ll> only integral points. Products of 3 coordinates.",
    L=r"\{1, p\}; \{0, \_\} parallel; \{-1, \_\} same line. Point<ll>: only integral points.",
    U=dict(M=r"auto [k, p] = lineInter(s1,e1,s2,e2); // k = 1: unique"))
D['geometry/sideOf.h'] = dict(
    G=r"1 / 0 / $-1$: $p$ left of / on / right of $s \to e$; with \texttt{eps}, within distance \texttt{eps} counts as on.",
    L=r"1 / 0 / $-1$: left / on / right of $s \to e$ (on: within \texttt{eps}).",
    U=dict(M=''))
D['geometry/OnSegment.h'] = dict(G=r"Doubles: use \texttt{segDist(s,e,p) <= eps} instead.")
D['geometry/linearTransformation.h'] = dict(G=r"Maps $r$ by the similarity taking $p_0 \to q_0$, $p_1 \to q_1$.")
D['geometry/LineProjectionReflection.h'] = dict(
    G=r"Projection of $p$ on line $ab$ (reflection if \texttt{refl}). Point<ll>: only integral results; products of 3 coordinates.",
    L=r"Reflection if \texttt{refl}. Point<ll>: only integral results.")
D['geometry/Angle.h'] = dict(
    G=r"Angles as int points plus full turns \texttt{t}, totally ordered; for rotational sweeps.",
    L=r"Int point plus full turns \texttt{t}; totally ordered.",
    U=dict(M=r"""vector<Angle> v = {w[0], w[0].t360() ...}; // sorted
int j = 0; rep(i,0,n) { while (v[j] < v[i].t180()) ++j; }"""))
D['geometry/CircleIntersection.h'] = dict(G=r"False if none, else the two points in \texttt{out}.")
D['geometry/CircleTangents.h'] = dict(
    G=r"""External tangents (internal: negate r2; from a point: r2 = 0) as (point on c1, point on c2): none if one circle
contains the other (internal: also if they overlap), 1 if they touch (\texttt{.first = .second}), else 2.""",
    L=r"Internal: negate r2; from a point: r2 = 0. Pairs (point on c1, point on c2); 1 if touching, 0 if nested.",
    M=r"Internal: r2 $< 0$; point: r2 = 0. Pairs (on c1, on c2).")
D['geometry/CircleLine.h'] = dict(G=r"0, 1 or 2 points.", L='')
D['geometry/CirclePolygonIntersection.h'] = dict(G=r"Area of circle $\cap$ ccw polygon.")
D['geometry/circumcircle.h'] = dict(G=r"Radius and center of the circle through A, B and C.")
D['geometry/MinimumEnclosingCircle.h'] = dict(G=r"Smallest enclosing circle (center, radius).", L=r"Returns (center, radius).")
D['geometry/InsidePolygon.h'] = dict(G=r"\texttt{strict}: the boundary is outside. Products of coordinates (overflow).",
    U=dict(M=r"bool in = inPolygon(v, P{3, 3}, false);"))
D['geometry/PolygonArea.h'] = dict(G=r"Twice the signed area (clockwise is negative).", M='',
    C=[("T polygonArea2(vector<Point<T>>& v) {", "T polygonArea2(vector<Point<T>>& v) { // 2x, cw < 0")])
D['geometry/PolygonCenter.h'] = dict(G=r"Center of mass.", L='')
D['geometry/PolygonCut.h'] = dict(G=r"Keeps the part to the right of $s \to e$.",
    U=dict(M=r"p = polygonCut(p, P(0,0), P(1,0));"))
D['geometry/HalfPlane.h'] = dict(
    G=r"""Half-plane $(s, e)$ = left of $s \to e$. Returns the intersection in ccw order, empty if empty (or degenerate).
Use doubles; add a big bounding box if it may be unbounded.""",
    L=r"$(s, e)$ = left of $s \to e$; ccw result. Doubles; add a big box if unbounded.")
D['geometry/ConvexHull.h'] = dict(G=r"Counter-clockwise; collinear points are dropped.", L=r"ccw, no collinear points.")
D['geometry/HullDiameter.h'] = dict(G=r"Farthest pair of a ccw hull without collinear points.", L=r"ccw hull, no collinear points.")
D['geometry/PointInsideHull.h'] = dict(G=r"ccw hull without collinear points; \texttt{strict}: the boundary is outside.", U=dict(G=''))
D['geometry/LineHullIntersection.h'] = dict(
    G=r"""Line $ab$ vs a ccw convex polygon without collinear points: $(-1, -1)$ none, $(i, -1)$ touches corner $i$,
$(i, i)$ along side $(i, i+1)$, $(i, j)$ crosses sides $(i, i+1)$ and $(j, j+1)$, in hit order. \texttt{extrVertex}: max projection.""",
    L=r"""ccw, no collinear. $(-1,-1)$ none, $(i,-1)$ corner $i$, $(i,i)$ along side $i$, $(i,j)$ crosses sides $i$, $j$
(side $i$ = $(i, i+1)$). \texttt{extrVertex}: max projection.""")
D['geometry/MinkowskiSum.h'] = dict(
    G=r"""Of two ccw convex polygons ($\ge 3$ vertices, no 3 collinear), ccw. $A$ and $B$ intersect iff $0 \in A + (-B)$;
their distance is the distance from 0 to it.""",
    L=r"ccw, $\ge 3$ vertices, no 3 collinear. $A \cap B \ne \emptyset$ iff $0 \in A + (-B)$.")
D['geometry/ClosestPair.h'] = dict(G=r"Closest pair of $\ge 2$ points.", L=r"At least 2 points.")
D['geometry/ManhattanMST.h'] = dict(
    G=r"$\le 4N$ edges (distance, i, j) that contain a Manhattan MST; run Kruskal on them.",
    L=r"$\le 4N$ edges (dist, i, j) containing an MST; run Kruskal.")
D['geometry/RectangleUnion.h'] = dict(G=r"Area of the union; \{x1, y1, x2, y2\} is $[x_1, x_2) \times [y_1, y_2)$.", L=r"\{x1, y1, x2, y2\}, half-open.")
D['geometry/kdTree.h'] = dict(G=r"2D nearest neighbour: \texttt{nearest(p)} = (squared distance, point).", L=r"\texttt{nearest(p)}: (squared distance, point).")

# ---------------- strings ----------------
D['strings/KMP.h'] = dict(G=r"\texttt{pi}: prefix function (abacaba $\to$ 0010123); \texttt{match}: start positions of \texttt{pat} in \texttt{s}.",
    L=r"\texttt{match}: start positions of \texttt{pat} in \texttt{s}.")
D['strings/Zfunc.h'] = dict(G=r"$z[i]$ = lcp of $s[i..]$ and $s$, $z[0] = 0$ (abacaba $\to$ 0010301).", L=r"$z[0] = 0$.")
D['strings/Manacher.h'] = dict(
    G=r"\texttt{p[1][i]}: half length (rounded down) of the longest odd palindrome centered at $i$; \texttt{p[0][i]}: of the even one centered before $i$.",
    L=r"\texttt{p[1][i]}: odd palindrome at $i$, half length rounded down; \texttt{p[0][i]}: even, centered before $i$.")
D['strings/PalindromicTree.h'] = dict(
    G=r"""Eertree. Node 0 has length $-1$, node 1 is the empty palindrome, the rest are the distinct palindromic substrings;
\texttt{link}: longest proper palindromic suffix; \texttt{last}: longest palindromic suffix of the prefix. \texttt{cnt[v]} after \texttt{count()}.""",
    L=r"Node 0: length $-1$, node 1: empty, the rest: distinct palindromes. \texttt{cnt[v]}: occurrences, after \texttt{count()}.",
    M=r"Node 0: length $-1$, 1: empty. \texttt{cnt} after \texttt{count()}.")
D['strings/MinRotation.h'] = dict(G=r"Start of the lexicographically smallest rotation.", L='')
D['strings/SuffixArray.h'] = dict(
    G=r"\texttt{sa} has size $n+1$ (\texttt{sa[0] = n}); \texttt{lcp[i] = lcp(sa[i], sa[i-1])}. No nul chars in the input.",
    M=r"\texttt{sa[0] = n}; \texttt{lcp[i] = lcp(sa[i], sa[i-1])}. No nul chars.")
D['strings/SuffixAutomaton.h'] = dict(
    G=r"""State $v$: substrings with the same end positions, lengths $(\texttt{len[link[v]]}, \texttt{len[v]}]$.
Distinct substrings: $\sum_{v \ne 0} \texttt{len[v]} - \texttt{len[link[v]]}$. \texttt{cnt[v]} (occurrences) after \texttt{count()}.""",
    L=r"State $v$: lengths $(\texttt{len[link[v]]}, \texttt{len[v]}]$. \texttt{cnt[v]}: occurrences, after \texttt{count()}.")
D['strings/Hashing.h'] = dict(G=r"Hashing mod $2^{64} - 1$; \texttt{hashInterval(a, b)} hashes $[a, b)$.", L='')
D['strings/AhoCorasick.h'] = dict(
    G=r"""Patterns non-empty (duplicates allowed); alphabet: \texttt{alpha}, \texttt{first}. \texttt{find(word)}: longest pattern ending at each position
($-1$ if none); \texttt{findAll(pat, word)}: all patterns starting at each position, shortest first.""",
    L=r"""Non-empty patterns; set \texttt{alpha}, \texttt{first}. \texttt{find}: longest pattern ending at each position, $-1$ if none;
\texttt{findAll}: all starting at each position.""",
    T=dict(L=r"O(26N) build ($N$ = total pattern length); find $O(|word|)$; findAll $O(NM)$"))

# ---------------- various ----------------
D['various/IntervalMap.h'] = dict(
    G=r"""Partition of $[lo, hi)$ into intervals with values; \texttt{assign} merges equal neighbours; \texttt{each} visits the pieces of $[l, r)$
by reference. A set of disjoint intervals: \texttt{T = bool}.""",
    L=r"\texttt{each}: \texttt{f(a, b, val\&)} on the pieces of $[l, r)$. Set of intervals: \texttt{T = bool}.")
D['various/IntervalCover.h'] = dict(
    G=r"Fewest intervals covering $G$. Half-open (closed: add \texttt{|| R.empty()} at (A)). Empty on failure.",
    L=r"Half-open (closed: add \texttt{|| R.empty()} at (A)); empty if impossible.")
D['various/TernarySearch.h'] = dict(
    G=r"""Smallest argmax on $[a, b]$ of $f$ strictly increasing, then non-increasing. Strict on the other side: \texttt{<=} at (A) and reverse (B).
For the minimum, \texttt{>} at (A) and (B).""",
    L=r"$f$ strictly increasing, then non-increasing; smallest argmax. Other side strict: \texttt{<=} at (A), reverse (B). Min: \texttt{>}.",
    M=r"$f$ strictly up, then non-increasing. Min: \texttt{>} at (A), (B).")
D['various/DivideAndConquerDP.h'] = dict(
    G=r"$a[i] = \min_{lo(i) \le k < hi(i)} f(i, k)$ for $i \in [L, R)$, when the smallest optimal $k$ is non-decreasing in $i$.",
    M=r"Smallest optimal $k$ non-decreasing in $i$.")

# M only: fold the two text-only files into their neighbours (their import is commented out).
FOLD = {'graph/MinCut.h': 'graph/Dinic.h', 'graph/MaximumIndependentSet.h': 'graph/MaximumClique.h'}
