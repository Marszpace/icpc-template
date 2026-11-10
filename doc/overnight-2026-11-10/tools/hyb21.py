# Level H ("hybrid", team 2026-11-10): the content and hints of G, but facts that belong to one
# function move into a trailing comment on its signature line (<= 63 columns, so no line is added
# and the hash does not change). Indexing and other conventions stay in the description.
# Files not listed here are exactly G.
#   H[file] = dict(desc=..., C=[(start of the code line, comment)], U=..., T=...)
H = {}

# ---------------- data structures ----------------
H['data-structures/SegmentTree.h'] = dict(
    desc=r"0-indexed point update. Max by default: change \texttt{T}, \texttt{f}, \texttt{unit}.")
H['data-structures/LazySegTreeBlock.h'] = dict(
    desc=r"""The part of \texttt{LazySeg} you edit. Default: range chmin and add; sum / max / count of max (beats).
chmin $v$ = \texttt{\{v, 0\}}, add $v$ = \texttt{\{INF, v\}}; \texttt{S()} is a leaf with value 0.
\texttt{comp} must keep tags closed, \texttt{app} must act on the aggregate as the tag acts on each element.
\textbf{Add only:} \texttt{ok} = 1, drop \texttt{se, cnt}.
\textbf{Min query:} add \texttt{mn}, \texttt{op} takes min, \texttt{app}: \texttt{mn = min(mn, x.c) + x.a}.
\textbf{Chmax:} store $-a_i$, negate updates and answers.
\textbf{Set, add, mul:} \texttt{L} = $(a, b)$: $x \mapsto ax + b$, \texttt{id} = \texttt{\{1, 0\}}, set $v$ = \texttt{\{0, v\}}, add = \texttt{\{1, v\}}, mul = \texttt{\{v, 0\}},
\texttt{app}: \texttt{a*s + b*len} (sum) or \texttt{a*s + b} (max, $a \ge 0$), \texttt{comp(x, y)} = \texttt{\{x.a*y.a, x.a*y.b + x.b\}}, \texttt{ok} = 1.
\textbf{Chmin, chmax, add, set; max / min only:} \texttt{L} = $(a, lo, hi)$: $x \mapsto \min(\max(x + a, lo), hi)$, set $v$ = \texttt{\{0, v, v\}},
\texttt{comp(x, y)}: $a$ = \texttt{x.a + y.a}, \texttt{lo, hi} = \texttt{y.lo, y.hi} plus \texttt{x.a}, clamped to \texttt{[x.lo, x.hi]}.""",
    C=[("struct L {", "tag x -> min(x, c) + a"), ("bool ok(S s, L x)", "x on all of s?")])
H['data-structures/PersistentSegmentTree.h'] = dict(
    desc=r"""Sums over positions $[0, n)$. \texttt{upd} adds $x$ at $p$ and returns the new root;
\texttt{query(v, l, r)} sums $[l, r)$.""",
    C=[("struct PST {", "version = root, 0 = empty"), ("int kth(int a, int b, ll k)", "k-th (0-idx) in b - a")])
H['data-structures/UnionFindRollback.h'] = dict(
    desc=r"""DSU with undo (\texttt{rollback(time())}); skip \texttt{st}, \texttt{time}, \texttt{rollback} if not needed.
If \texttt{join} returns false and $\texttt{par(a)} \oplus \texttt{par(b)} \ne w$, the demand is contradictory.""",
    C=[("bool join(int a, int b, int w = 0)", "par(a)^par(b) = w")])
H['data-structures/DynCon.h'] = dict(
    desc=r"""Offline dynamic connectivity. \texttt{add(l, r, a, b)}: edge $a$--$b$ during times $[l, r)$. \texttt{run(f)} calls \texttt{f(t)} for $t = 0..T-1$
with \texttt{uf} = the graph at time $t$. Toggles: map of start times.""",
    C=[("struct DynCon {", "bad: odd-cycle edges, 0 = bipartite")])
H['data-structures/LiChao.h'] = dict(
    desc=r"""Minimum of lines $kx + m$ at integer $x \in [0, n)$; \texttt{addSeg} only on $x \in [a, b)$. Max: negate $k$, $m$ and the answer.""",
    C=[("ll query(int x)", "INF if no line covers x")])
H['data-structures/FenwickTree.h'] = dict(
    desc=r"0-indexed. \texttt{lower\_bound} needs non-negative values.")
H['data-structures/FenwickTree2d.h'] = dict(
    desc=r"0-indexed. Points to update must be known: \texttt{fakeUpdate} each, then \texttt{init()}.",
    C=[("ll query(int x, int y)", "sum over [0, x) x [0, y)")])
H['data-structures/RMQ.h'] = dict(
    desc=r"Sparse table (min).",
    C=[("T query(int a, int b)", "min of V[a..b), O(1)")])
H['data-structures/MoQueries.h'] = dict(
    desc=r"""Mo's algorithm on intervals (\texttt{mo}) or tree paths (\texttt{moTree}); fill in \texttt{add}, \texttt{del}, \texttt{calc}.
Values on tree edges: \texttt{step} toggles the edge $(a, c)$ and the initial \texttt{add} goes (keep \texttt{in}).""",
    C=[("vi mo(vector<pii> Q)", "queries [l, r)")])

# ---------------- numerical ----------------
H['numerical/PolyInterpolate.h'] = dict(
    desc=r"Coefficients $a$ of the degree $n-1$ polynomial through $(x_i, y_i)$. Precision: pick $x_k = c\cos(k\pi/(n-1))$.",
    C=[("vd interpolate(vd x, vd y, int n)", "p(x) = sum a_i x^i")])
H['numerical/LinearRecurrence.h'] = dict(
    desc=r"$S[i] = \sum_j S[i-j-1]\,tr[j]$, given $S[0..n-1]$ and $tr[0..n-1]$, mod \texttt{mod}.",
    C=[("ll linearRec(Poly S, Poly tr, ll k)", "k-th term, 0-indexed")])
H['numerical/XorBasis.h'] = dict(
    desc=r"Basis of the span under xor. \texttt{insert} returns whether $x$ was independent; \texttt{has(x)}: $x$ in the span.",
    C=[("ull best(ull x = 0)", "max x ^ s over the span"), ("ull kth(ull k)", "k-th smallest, 0-idx, k < 2^rk")])
H['numerical/FastFourierTransform.h'] = dict(
    desc=r"""Convolution with doubles. Exact while $(\sum a_i^2 + \sum b_i^2)\log_2 N < 9\cdot10^{14}$
(in practice $10^{16}$), else NTT / FFTMod. By hand: FFT, multiply, divide by $n$, reverse(start+1, end), FFT back.""",
    C=[("vd conv(const vd& a, const vd& b)", "c[x] = sum a[i]b[x-i]")])
H['numerical/NumberTheoreticTransform.h'] = dict(
    desc=r"""Convolution mod a prime $2^a b + 1$ with result size $\le 2^a$ (default 998244353; any modulus: FFTMod). Inputs in $[0, mod)$.
By hand: NTT, multiply, divide by $n$, reverse(start+1, end), NTT back.""",
    C=[("vl conv(const vl &a, const vl &b)", "c[x] = sum a[i]b[x-i]")])
H['numerical/PolyOps.h'] = dict(
    desc=r"""Power series mod $x^n$ and \texttt{mod} (NTT prime); results have exactly $n$ terms.
\texttt{polyPow(a, k, n)}: any $a$, $k \le 10^{18}$. \texttt{polyDivMod(a, b)} returns $(q, r)$.""",
    C=[("vl polyInv(vl a, int n)", "a[0] != 0"), ("vl polyLog(vl a, int n)", "a[0] = 1"),
       ("vl polyExp(vl a, int n)", "a[0] = 0"), ("pair<vl, vl> polyDivMod(vl a, vl b)", "b.back() != 0")])

# ---------------- number theory ----------------
H['number-theory/ModularArithmetic.h'] = dict(
    desc=r"\texttt{mint<mod>}: arithmetic, comparisons, I/O, \texttt{fpow(a, p)}, \texttt{inverse(a)}; \texttt{(int)a} is the value.",
    C=[("template<int mod> struct mint {", "prime mod < 2^30")])
H['number-theory/ModLog.h'] = dict(
    desc=r"$a^x \equiv b \pmod m$ for any $m$. \texttt{modLog(a, 1, m)} is the order of $a$.",
    C=[("ll modLog(ll a, ll b, ll m)", "min x > 0, or -1")])
H['number-theory/ModSum.h'] = dict(
    desc=r"\texttt{modsum(to, c, k, m)}: sum over $i < to$; \texttt{divsum}: the same with $\lfloor (ki + c)/m \rfloor$.",
    C=[("ll modsum(ull to, ll c, ll k, ll m)", "sum of (ki+c) % m")])
H['number-theory/ModMulLL.h'] = dict(
    desc=r"$ab \bmod c$ and $a^b \bmod c$.",
    C=[("ull modmul(ull a, ull b, ull M)", "a, b <= M <= 7.2e18")])
H['number-theory/ModSqrt.h'] = dict(
    desc=r"Tonelli-Shanks for prime $p$; $-x$ is the other root.",
    C=[("ll sqrt(ll a, ll p)", "x^2 = a (p); asserts if none")])
H['number-theory/PrimitiveRoot.h'] = dict(
    desc=r"Smallest primitive root. 998244353: 3, $10^9 + 7$: 5.",
    C=[("ull primitiveRoot(ull p)", "prime p <~ 1e12; else Factor")])
H['number-theory/euclid.h'] = dict(
    desc=r"Returns $\gcd(a, b)$; if coprime, $x = a^{-1} \bmod b$.",
    C=[("ll euclid(ll a, ll b, ll &x, ll &y)", "ax + by = gcd")])
H['number-theory/CRT.h'] = dict(
    desc=r"$0 \le x < \mathrm{lcm}$ if $|a| < m$, $|b| < n$; asserts if none. Needs $mn < 2^{62}$.",
    C=[("ll crt(ll a, ll m, ll b, ll n)", "x = a (m), x = b (n)")])
H['combinatorial/IntPerm.h'] = dict(
    desc=r"Exact for $n \le 20$. Unknown size: \texttt{radixToPerm}.")
H['combinatorial/multinomial.h'] = dict(
    desc=r"Exact while it fits in \texttt{ll}.",
    C=[("ll multinomial(vi& v)", "(sum k)! / prod k!")])

# ---------------- graph ----------------
H['graph/HopcroftKarp.h'] = dict(
    desc=r"$g$: neighbours of each left vertex; $r$: all $-1$, size of the right side; $r[i]$ = match of right vertex $i$ or $-1$.",
    C=[("int hopcroftKarp(vector<vi>& g, vi& r)", "matching size")])
H['graph/MinimumVertexCover.h'] = dict(
    desc=r"Bipartite. Size = max matching; complement = max independent set.",
    C=[("vi cover(vector<vi>& g, int n, int m)", "right j -> n+j")])
H['graph/GlobalMinCut.h'] = dict(
    desc=r"Stoer-Wagner on an adjacency matrix.",
    C=[("pair<int, vi> globalMinCut(vector<vi> mat)", "(weight, side)")])
H['graph/HLD.h'] = dict(
    desc=r"""Performs HLD over a \texttt{LazySeg} (edit its block): updates take \texttt{L}, queries return \texttt{S}, values start as \texttt{S()}.
Full adjacency list, root 0.""",
    C=[("template <bool VALS_EDGES> struct HLD {", "VALS_EDGES: on edges")])
H['graph/CentroidDecomposition.h'] = dict(
    desc=r"\texttt{run(f)} calls \texttt{f(c)} per centroid $c$; a DFS from $c$ skipping \texttt{dead} then visits exactly its component.",
    C=[("struct Centroid {", "cpar: centroid tree, root -1")])

# ---------------- geometry ----------------
H['geometry/lineDistance.h'] = dict(
    desc=r"Signed distance from p to the line through a and b; a==b gives nan.",
    C=[("double lineDist(P a, P b, P p)", "> 0: left of a -> b")])
H['geometry/PolygonArea.h'] = dict(
    desc=r"Twice the signed area.",
    C=[("T polygonArea2(vector<Point<T>>& v)", "2x area, cw < 0")])

# ---------------- strings ----------------
H['strings/KMP.h'] = dict(
    desc=r"\texttt{pi}: prefix function; \texttt{match}: start positions of \texttt{pat} in \texttt{s}.",
    C=[("vi pi(const string& s)", "abacaba -> 0010123")])
H['strings/Zfunc.h'] = dict(
    desc=r"$z[i]$ = lcp of $s[i..]$ and $s$, $z[0] = 0$.",
    C=[("vi Z(const string& S)", "abacaba -> 0010301")])
H['strings/AhoCorasick.h'] = dict(
    desc=r"""Patterns non-empty (duplicates allowed); alphabet: \texttt{alpha}, \texttt{first}.
\texttt{findAll(pat, word)}: all patterns starting at each position, shortest first.""",
    C=[("vi find(string word)", "longest ending at i, -1")])
H['strings/SuffixAutomaton.h'] = dict(
    desc=r"""State $v$: substrings with the same end positions, lengths $(\texttt{len[link[v]]}, \texttt{len[v]}]$.
Distinct substrings: $\sum_{v \ne 0} \texttt{len[v]} - \texttt{len[link[v]]}$.""",
    C=[("void count() {", "cnt[v] = occurrences")])
H['strings/PalindromicTree.h'] = dict(
    desc=r"""Eertree: the other nodes are the distinct palindromic substrings; \texttt{link}: longest proper palindromic suffix;
\texttt{last}: longest palindromic suffix of the prefix. \texttt{cnt[v]} after \texttt{count()}.""",
    C=[("struct PalTree {", "node 0: len -1, node 1: empty")])

# ---------------- various ----------------
H['various/TernarySearch.h'] = dict(
    desc=r"""$f$ strictly increasing, then non-increasing. Strict on the other side: \texttt{<=} at (A) and reverse (B).
For the minimum, \texttt{>} at (A) and (B).""",
    C=[("int ternSearch(int a, int b, F f)", "smallest argmax")])
