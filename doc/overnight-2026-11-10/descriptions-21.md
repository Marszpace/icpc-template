# Item 21: description proposals (three levels)

Raw LaTeX as it goes into the headers. **G** = gentle (readable, a few words of what it does), **L** = lean (only what you need to use it; the team rule), **M** = minimal. "= G" means the same as the level before. Code-comment moves (L and M) add a trailing comment to an existing code line, so no line is added and the hash does not change.


## data-structures

### `OrderStatisticTree.h`

- **Now:** A set (not multiset!) with support for finding the n'th element, and finding the index of an element. To get a map, change \texttt{null\_type}.
- **G:** Set (not multiset) with \texttt{find\_by\_order} and \texttt{order\_of\_key}. For a map, change \texttt{null\_type}.
- **L:** Not a multiset. Map: change \texttt{null\_type}.
- **M:** = L

### `HashMap.h`

- **Now:** Hash map with mostly the same API as unordered\_map, but \tilde 3x faster. Uses 1.5x memory. Initial capacity must be a power of 2 (if provided).
- **G:** \texttt{unordered\_map} API, about 3x faster, 1.5x memory. Initial capacity must be a power of 2.
- **L:** \texttt{unordered\_map} API, 3x faster. Capacity: a power of 2.
- **M:** Capacity: a power of 2.

### `SegmentTree.h`

- **Now:** Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right. Can be changed by modifying T, f and unit.
- **G:** 0-indexed, point update, query $[b, e)$. Max by default: change \texttt{T}, \texttt{f}, \texttt{unit}.
- **L:** Change \texttt{T}, \texttt{f}, \texttt{unit}.
- **M:** *(none)*
- Code comment (L, M): `struct Tree {` → `struct Tree { // 0-indexed`

### `LazySegTreeBlock.h`

- **Now:** The part of \texttt{LazySeg} you edit. Range chmin and range add, queries sum / max / count of max (segment tree beats). A tag is $x \mapsto \min(x, c) + a$: chmin $v$ is \texttt{\{v, 0\}}, add $v$ is \texttt{\{INF, v\}}. \texttt{S()} is a leaf with value 0. To change it, \texttt{L} must stay closed under \texttt{comp}, and \texttt{app} must act on the aggregate like the tag acts on every element. \texttt{ok(s, x)} says whether $x$ can be applied to the whole segment $s$ without looking inside (else it recurses). \textbf{Add only:} \texttt{ok} returns 1, drop \texttt{se, cnt}. \textbf{Min query:} add \texttt{mn}, \texttt{op} takes min, \texttt{app}: \texttt{mn = min(mn, x.c) + x.a}. \textbf{Chmax instead of chmin:} store $-a_i$ (chmax $v$ = chmin $-v$, add $v$ = add $-v$), negate the answers. \textbf{Set, add, mul:} \texttt{L} = $(a, b)$, $x \mapsto ax + b$, \texttt{id} = \texttt{\{1, 0\}}, set $v$ = \texttt{\{0, v\}}, add = \texttt{\{1, v\}}, mul = \texttt{\{v, 0\}}, \texttt{app} = \texttt{a * s + b * len} (sum) or \texttt{a * s + b} (max, $a \ge 0$), \texttt{comp(x, y)} = \texttt{\{x.a * y.a, x.a * y.b + x.b\}}, \texttt{ok} returns 1. \textbf{Chmin, chmax, add, set with only max / min queries:} \texttt{L} = $(a, lo, hi)$, $x \mapsto \min(\max(x + a, lo), hi)$, set $v$ = \texttt{\{0, v, v\}}, \texttt{comp(x, y)}: $a$ = \texttt{x.a + y.a}, and \texttt{lo, hi} = \texttt{y.lo, y.hi} each shifted by \texttt{x.a}, then clamped to \texttt{[x.lo, x.hi]}.
- **G:** The part of \texttt{LazySeg} you edit. Default: range chmin and add; sum / max / count of max (beats). Tag $x \mapsto \min(x, c) + a$: chmin $v$ = \texttt{\{v, 0\}}, add $v$ = \texttt{\{INF, v\}}; \texttt{S()} is a leaf with value 0. \texttt{comp} must keep tags closed, \texttt{app} must act on the aggregate as the tag acts on each element; \texttt{ok(s, x)}: can $x$ be applied to all of $s$ at once (else it recurses). \textbf{Add only:} \texttt{ok} = 1, drop \texttt{se, cnt}. \textbf{Min query:} add \texttt{mn}, \texttt{op} takes min, \texttt{app}: \texttt{mn = min(mn, x.c) + x.a}. \textbf{Chmax:} store $-a_i$, negate updates and answers. \textbf{Set, add, mul:} \texttt{L} = $(a, b)$: $x \mapsto ax + b$, \texttt{id} = \texttt{\{1, 0\}}, set $v$ = \texttt{\{0, v\}}, add = \texttt{\{1, v\}}, mul = \texttt{\{v, 0\}}, \texttt{app}: \texttt{a*s + b*len} (sum) or \texttt{a*s + b} (max, $a \ge 0$), \texttt{comp(x, y)} = \texttt{\{x.a*y.a, x.a*y.b + x.b\}}, \texttt{ok} = 1. \textbf{Chmin, chmax, add, set; max / min only:} \texttt{L} = $(a, lo, hi)$: $x \mapsto \min(\max(x + a, lo), hi)$, set $v$ = \texttt{\{0, v, v\}}, \texttt{comp(x, y)}: $a$ = \texttt{x.a + y.a}, \texttt{lo, hi} = \texttt{y.lo, y.hi} plus \texttt{x.a}, clamped to \texttt{[x.lo, x.hi]}.
- **L:** Default: chmin + add, sum / max / count of max (beats). Tag $x \mapsto \min(x, c) + a$: chmin \texttt{\{v, 0\}}, add \texttt{\{INF, v\}}. \texttt{app} acts on the aggregate as the tag on each element; \texttt{ok(s, x)}: apply without recursing? \textbf{Add only:} \texttt{ok} = 1, drop \texttt{se, cnt}. \textbf{Min query:} add \texttt{mn}, \texttt{app}: \texttt{mn = min(mn, x.c) + x.a}. \textbf{Chmax:} store $-a_i$. \textbf{Set, add, mul:} \texttt{L} = $(a, b)$: $ax + b$, \texttt{id \{1, 0\}}, set \texttt{\{0, v\}}, add \texttt{\{1, v\}}, mul \texttt{\{v, 0\}}, \texttt{app}: \texttt{a*s + b*len} (sum), \texttt{a*s + b} (max, $a \ge 0$), \texttt{comp}: \texttt{\{x.a*y.a, x.a*y.b + x.b\}}, \texttt{ok} = 1. \textbf{Chmin, chmax, add, set (max / min only):} \texttt{L} = $(a, lo, hi)$: $\min(\max(x + a, lo), hi)$, set \texttt{\{0, v, v\}}, \texttt{comp}: \texttt{x.a + y.a}, and \texttt{y.lo, y.hi} plus \texttt{x.a}, clamped to \texttt{[x.lo, x.hi]}.
- **M:** Default: chmin + add, sum / max / count of max (beats); tag $\min(x, c) + a$. \texttt{ok(s, x)}: apply without recursing? \textbf{Add:} \texttt{ok} = 1, drop \texttt{se, cnt}. \textbf{Min:} \texttt{mn = min(mn, x.c) + x.a}. \textbf{Chmax:} store $-a_i$. \textbf{Set, add, mul:} $(a, b)$: $ax + b$, set \texttt{\{0, v\}}; \texttt{app} \texttt{a*s + b*len}; \texttt{comp} \texttt{\{x.a*y.a, x.a*y.b + x.b\}}. \textbf{Clamp (max / min only):} $(a, lo, hi)$: $\min(\max(x + a, lo), hi)$; \texttt{comp}: shift \texttt{y.lo, y.hi} by \texttt{x.a}, clamp to \texttt{[x.lo, x.hi]}.

### `LazySegTree.h`

- **Now:** Lazy segment tree over any monoid with lazy tags. Never edit this part, only the block before it (\texttt{LazySegTreeBlock.h}), which defines \texttt{S}, \texttt{L}, \texttt{e}, \texttt{id}, \texttt{op}, \texttt{ok}, \texttt{app}, \texttt{comp}. \texttt{app(s, x, len)} applies tag $x$ to the value $s$ of a segment of length \texttt{len}, \texttt{comp(x, y)} is the tag "$y$ first, then $x$". Ranges are $[l, r)$. Beats with add is $O(\log^2 N)$ amortized. \texttt{maxRight(l, f)} is the largest $r$ with \texttt{f(query(l, r))} true, for monotone $f$ with \texttt{f(e())} true (descent in $O(\log N)$).
- **G:** Lazy segment tree; edit only \texttt{LazySegTreeBlock.h}. \texttt{app(s, x, len)} applies tag $x$ to a segment of length \texttt{len}; \texttt{comp(x, y)} = $y$ first, then $x$. Ranges $[l, r)$. \texttt{maxRight(l, f)}: largest $r$ with \texttt{f(query(l, r))}, for monotone $f$ with \texttt{f(e())} true.
- **L:** Edit only the block. Ranges $[l, r)$; \texttt{comp(x, y)}: $y$ first, then $x$. \texttt{maxRight(l, f)}: largest $r$ with \texttt{f(query(l, r))} ($f$ monotone, \texttt{f(e())} true).
- **M:** Ranges $[l, r)$. \texttt{maxRight(l, f)}: largest $r$ with \texttt{f(query(l, r))}, $f$ monotone.
- Time (L and later): `O(\log N)` → `O(\log N), beats with add $O(\log^2 N)$ amortized`

### `PersistentSegmentTree.h`

- **Now:** Persistent segment tree over positions $[0, n)$ holding sums. A version is identified by its root; version 0 is empty. \texttt{upd} adds $x$ at position $p$ and returns the new root. \texttt{query(v, l, r)} sums $[l, r)$ in version $v$. \texttt{kth(a, b, k)} is the $k$-th smallest (0-indexed) position in the multiset \texttt{b} $-$ \texttt{a} (all counts $\ge 0$), e.g. range $k$-th element with $a_i$ added at position rank($a_i$) per version.
- **G:** Sums over positions $[0, n)$; a version is its root, version 0 is empty. \texttt{upd} adds $x$ at $p$ and returns the new root; \texttt{query(v, l, r)} sums $[l, r)$; \texttt{kth(a, b, k)}: $k$-th smallest (0-indexed) position of the multiset \texttt{b} $-$ \texttt{a}.
- **L:** \texttt{upd} returns the new root. \texttt{kth(a, b, k)}: $k$-th smallest (0-indexed) position in version \texttt{b} minus \texttt{a}.
- **M:** *(none)*
- Code comment (L, M): `struct PST {` → `struct PST { // version = root, 0 = empty; ranges [l, r)`
- Code comment (L, M): `int kth(int a, int b, ll k) {` → `int kth(int a, int b, ll k) { // k-th (0-idx) pos of b - a`

### `UnionFindRollback.h`

- **Now:** Disjoint-set data structure with undo. If undo is not needed, skip st, time() and rollback(). Optional parity: \texttt{join(a, b, w)} also demands that the parity $\texttt{par(a)} \oplus \texttt{par(b)}$ (distance mod 2 to the root) is $w$. If \texttt{join} returns false and $\texttt{par(a)} \oplus \texttt{par(b)} \ne w$, the demand is contradictory.
- **G:** DSU with undo: \texttt{rollback(t)} to an earlier \texttt{time()}; skip \texttt{st}, \texttt{time}, \texttt{rollback} if not needed. With parity, \texttt{join(a, b, w)} also demands $\texttt{par(a)} \oplus \texttt{par(b)} = w$; if it returns false with a different parity, the demand is contradictory.
- **L:** Undo: \texttt{rollback(time())}. If \texttt{join} returns false (already joined), check $\texttt{par(a)} \oplus \texttt{par(b)} = w$ yourself.
- **M:** *(none)*
- Code comment (L, M): `bool join(int a, int b, int w = 0) {` → `bool join(int a, int b, int w = 0) { // par(a)^par(b) = w`

### `DynCon.h`

- **Now:** Offline dynamic connectivity. \texttt{add(l, r, a, b)} makes edge $a$--$b$ present during times $[l, r)$. \texttt{run(f)} calls \texttt{f(t)} for $t = 0, \dots, T-1$ in order; during the call \texttt{uf} describes the graph at time $t$ (components, sizes), and \texttt{bad} is the number of edges closing an odd cycle (the graph is bipartite iff \texttt{bad == 0}). For toggle queries, keep a \texttt{map<pii,int>} of start times and close open edges at $T$.
- **G:** Offline dynamic connectivity. \texttt{add(l, r, a, b)}: edge $a$--$b$ during times $[l, r)$. \texttt{run(f)} calls \texttt{f(t)} for $t = 0..T-1$ with \texttt{uf} = the graph at time $t$; \texttt{bad} = number of edges closing an odd cycle (bipartite iff 0). Toggles: map of start times.
- **L:** Offline. Edge $a$--$b$ alive in $[l, r)$; in \texttt{f(t)}, \texttt{uf} is the graph at time $t$, bipartite iff \texttt{bad == 0}.
- **M:** Edge alive in $[l, r)$; \texttt{f(t)} sees \texttt{uf} at time $t$; bipartite iff \texttt{bad == 0}.

### `Matrix.h`

- **Now:** Basic operations on square matrices.
- **G:** Square matrices with \texttt{*} and power \texttt{\textasciicircum}.
- **L:** *(none)*
- **M:** = L
- Usage (M and later): `Matrix<int, 3> A; A.d = {{{{1,2,3}}, {{4,5,6}}, {{7,8,9}}}}; array<int, 3> vec = {1,2,3}; vec = (A^N) * vec;` → `Matrix<int, 3> A; A.d = {{{{1,2,3}}, {{4,5,6}}, {{7,8,9}}}}; vec = (A^N) * vec; // vec: array<int, 3>`

### `LineContainer.h`

- **Now:** Container where you can add lines of the form kx+m, and query maximum values at points x. Useful for dynamic programming (``convex hull trick'').
- **G:** Add lines $kx + m$, query the maximum at $x$ (convex hull trick).
- **L:** Lines $kx + m$, query the max at $x$.
- **M:** *(none)*
- Code comment (L, M): `ll query(ll x) {` → `ll query(ll x) { // max of kx + m`

### `LiChao.h`

- **Now:** Li Chao tree: minimum of lines $kx + m$ at integer points $x \in [0, n)$. \texttt{add} inserts a line everywhere, \texttt{addSeg} only for $x \in [a, b)$, in any order. For maximum, negate $k$, $m$ and the answer. \texttt{query} returns \texttt{INF} if no line covers $x$.
- **G:** Minimum of lines $kx + m$ at integer $x \in [0, n)$; \texttt{addSeg} only on $x \in [a, b)$. Max: negate $k$, $m$ and the answer. \texttt{query} returns \texttt{INF} if no line covers $x$.
- **L:** Min at integer $x \in [0, n)$; \texttt{addSeg} on $[a, b)$. Max: negate. \texttt{INF} if no line.
- **M:** *(none)*
- Code comment (L, M): `struct LiChao {` → `struct LiChao { // min at integer x in [0, n); max: negate`
- Code comment (L, M): `ll query(int x) {` → `ll query(int x) { // INF if no line covers x`

### `Treap.h`

- **Now:** A short self-balancing tree. It acts as a sequential container with log-time splits/joins, and is easy to augment with additional data. Here each node keeps the sum of its subtree, with lazy range add and range reverse: \texttt{go(t, l, r, f)} runs \texttt{f} on the subtree holding positions $[l, r)$ (see the comment above it).
- **G:** Implicit treap (a sequence, split / merge by position) keeping subtree sums with lazy range add and reverse. \texttt{go(t, l, r, f)} runs \texttt{f} on the node holding positions $[l, r)$.
- **L:** Implicit treap (by position) with sums, lazy add and reverse.
- **M:** Implicit treap, sums, lazy add and reverse.

### `FenwickTree.h`

- **Now:** Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i], taking the difference between the old and new value.
- **G:** 0-indexed; \texttt{query(pos)} sums $[0, pos)$; \texttt{lower\_bound} needs non-negative values.
- **L:** \texttt{lower\_bound} needs non-negative values.
- **M:** *(none)*
- Time (L and later): `Both operations are $O(\log N)$.` → `O(\log N)`
- Code comment (L, M): `struct FT {` → `struct FT { // 0-indexed`

### `FenwickTree2d.h`

- **Now:** Computes sums a[i,j] for all i<I, j<J, and increases single elements a[i,j]. Requires that the elements to be updated are known in advance (call fakeUpdate() before init()).
- **G:** 0-indexed; \texttt{query(x, y)} sums $[0, x) \times [0, y)$. Points to update must be known: \texttt{fakeUpdate} each, then \texttt{init()}.
- **L:** Points to update must be known in advance.
- **M:** *(none)*
- Time (L and later): `$O(\log^2 N)$. (Use persistent segment trees for $O(\log N)$.)` → `O(\log^2 N)`
- Code comment (L, M): `struct FT2 {` → `struct FT2 { // 0-idx; fakeUpdate() all points, then init()`
- Code comment (L, M): `ll query(int x, int y) {` → `ll query(int x, int y) { // sum over [0, x) x [0, y)`

### `RMQ.h`

- **Now:** Range Minimum Queries on an array. Returns min(V[a], V[a + 1], ... V[b - 1]) in constant time.
- **G:** Sparse table; \texttt{query(a, b)} is the min of $V[a..b)$ in $O(1)$.
- **L:** *(none)*
- **M:** = L

### `MoQueries.h`

- **Now:** Interval or tree path queries: visit the queries along an approximate TSP, adding/removing points at the ends. Values on tree edges: \texttt{step} adds/removes the edge $(a, c)$ and the initial \texttt{add} goes (keep \texttt{in}).
- **G:** Mo's algorithm on intervals $[l, r)$ (\texttt{mo}) or tree paths (\texttt{moTree}); fill in \texttt{add}, \texttt{del}, \texttt{calc}. Values on tree edges: \texttt{step} toggles the edge $(a, c)$ and the initial \texttt{add} goes (keep \texttt{in}).
- **L:** Queries $[l, r)$. Values on tree edges: \texttt{step} toggles the edge $(a, c)$, no initial \texttt{add} (keep \texttt{in}).
- **M:** Values on tree edges: \texttt{step} toggles edge $(a, c)$, no initial \texttt{add}.


## numerical

### `Polynomial.h`

- **Now:** *(none)*
- **G:** *(none)*
- **L:** = G
- **M:** = L

### `PolyInterpolate.h`

- **Now:** Given $n$ points (x[i], y[i]), computes an n-1-degree polynomial $p$ that passes through them: $p(x) = a[0]*x^0 + ... + a[n-1]*x^{n-1}$. For numerical precision, pick $x[k] = c*\cos(k/(n-1)*\pi), k=0 \dots n-1$.
- **G:** Coefficients of the degree $n-1$ polynomial through $(x_i, y_i)$: $p(x) = \sum a_i x^i$. Precision: pick $x_k = c\cos(k\pi/(n-1))$.
- **L:** Returns $a$ with $p(x) = \sum a_i x^i$. Precision: $x_k = c\cos(k\pi/(n-1))$.
- **M:** Returns $a$, $p(x) = \sum a_i x^i$.

### `LagrangeInterpolation.h`

- **Now:** Given $y_i = f(i)$ for $i = 0, \dots, n-1$, where $f$ is a polynomial of degree $< n$, returns $f(x) \bmod p$ for any integer $x$ ($mod$ prime $> n$). Use for sums of powers: $\sum_{i \le x} i^k$ has degree $k+1$, so feed it $k+2$ prefix sums.
- **G:** $f(x) \bmod p$ from $y_i = f(i)$, $i < n$, $\deg f < n$, $p$ prime $> n$. Sums of powers: $\sum_{i \le x} i^k$ has degree $k+1$, so give it $k+2$ prefix sums.
- **L:** Input $f(0), \dots, f(n-1)$, $\deg f < n$, mod prime $> n$. $\sum_{i \le x} i^k$: give $k+2$ values.
- **M:** Input $f(0), \dots, f(n-1)$, $\deg f < n$.

### `BerlekampMassey.h`

- **Now:** Recovers any $n$-order linear recurrence relation from the first $2n$ terms of the recurrence. Useful for guessing linear recurrences after brute-forcing the first terms. Should work on any field, but numerical stability for floats is not guaranteed. Output will have size $\le n$.
- **G:** Shortest linear recurrence (in \texttt{linearRec}'s format) of a sequence mod prime, from its first $2n$ terms. For guessing recurrences.
- **L:** Needs the first $2n$ terms (mod prime); output fits \texttt{linearRec}.
- **M:** Needs $2n$ terms; output fits \texttt{linearRec}.

### `LinearRecurrence.h`

- **Now:** Generates the $k$'th term of an $n$-order linear recurrence $S[i] = \sum_j S[i-j-1]tr[j]$, given $S[0 \ldots \ge n-1]$ and $tr[0 \ldots n-1]$. Faster than matrix multiplication. Useful together with Berlekamp--Massey.
- **G:** $k$-th term (0-indexed) of $S[i] = \sum_j S[i-j-1]\,tr[j]$, given $S[0..n-1]$ and $tr[0..n-1]$, mod \texttt{mod}.
- **L:** $S[i] = \sum_j S[i-j-1]\,tr[j]$; $k$-th term, 0-indexed.
- **M:** = L

### `BostanMori.h`

- **Now:** Generates the $k$'th term of an $n$-order linear recurrence $S[i] = \sum_j S[i-j-1]tr[j]$, given $S[0 \ldots \ge n-1]$ and $tr[0 \ldots n-1]$, modulo 998244353 (values in $[0, mod)$). Same interface as \texttt{linearRec}, much faster for large $n$. With $Q = 1 - \sum_j tr[j] x^{j+1}$ and $P = S \cdot Q \bmod x^n$ we want $[x^k] P/Q$; multiplying both by $Q(-x)$ makes the denominator even, so $k$ halves.
- **G:** Same as \texttt{linearRec} mod 998244353 (values in $[0, mod)$), $O(n \log n \log k)$: halves $k$ via $P(x)Q(-x) / Q(x)Q(-x)$.
- **L:** Same interface as \texttt{linearRec}, mod 998244353.
- **M:** = L

### `HillClimbing.h`

- **Now:** Poor man's optimization for unimodal functions.
- **G:** Minimizes $f$ over the plane from \texttt{start}; fine for unimodal $f$.
- **L:** Minimizes $f$ (unimodal).
- **M:** = L

### `Integrate.h`

- **Now:** Simple integration of a function over an interval using Simpson's rule. The error should be proportional to $h^4$, although in practice you will want to verify that the result is stable to desired precision when epsilon changes.
- **G:** Simpson's rule with $2n$ intervals; error $\propto h^4$, check that the result is stable when $n$ changes.
- **L:** Simpson, error $O(h^4)$.
- **M:** Simpson.

### `Determinant.h`

- **Now:** Calculates determinant of a matrix. Destroys the matrix.
- **G:** Doubles. Destroys the matrix.
- **L:** Destroys the matrix.
- **M:** = L

### `IntDeterminant.h`

- **Now:** Calculates determinant using modular arithmetics. Modulos can also be removed to get a pure-integer version.
- **G:** Determinant mod any \texttt{mod} (also composite) by Euclid row steps. Remove the \texttt{\% mod} for exact integers.
- **L:** Any \texttt{mod}, also composite. Drop the mods for exact integers.
- **M:** Any \texttt{mod}, also composite.

### `SolveLinear.h`

- **Now:** Solves $A * x = b$. If there are multiple solutions, an arbitrary one is returned. Returns rank, or -1 if no solutions. Data in $A$ and $b$ is lost.
- **G:** Solves $Ax = b$. Returns rank, or $-1$ if no solution (an arbitrary one if rank $< m$). Destroys $A$, $b$.
- **L:** Returns rank, or $-1$ if none. Destroys $A$, $b$.
- **M:** = L

### `SolveLinear2.h`

- **Now:** To get all uniquely determined values of $x$ back from SolveLinear, make the following changes:
- **G:** Changes to SolveLinear to get back all uniquely determined values of $x$:
- **L:** = G
- **M:** = L

### `SolveLinearBinary.h`

- **Now:** Solves $Ax = b$ over $\mathbb F_2$. If there are multiple solutions, one is returned arbitrarily. Returns rank, or -1 if no solutions. Destroys $A$ and $b$.
- **G:** Over $\mathbb F_2$. Returns rank, or $-1$ if none. Destroys $A$, $b$.
- **L:** = G
- **M:** = L

### `SolveLinearMod.h`

- **Now:** Solves $A x = b$ over the field $\mathbb Z_{mod}$ ($mod$ prime). Returns the rank, or $-1$ if there is no solution. Free variables are set to 0. Data in $A$ and $b$ is lost. Entries must be in $[0, mod)$.
- **G:** Mod prime, entries in $[0, mod)$. Returns rank, or $-1$ if none; free variables are 0. Destroys $A$, $b$.
- **L:** = G
- **M:** Mod prime, entries in $[0, mod)$. Rank or $-1$; free variables 0.

### `XorBasis.h`

- **Now:** Basis of the span of the inserted 64-bit numbers under xor. \texttt{insert} returns whether $x$ was independent. \texttt{has(x)} tests $x \in$ span. \texttt{best(x)} is the maximum of $x \oplus s$ over the span ($x = 0$: maximum element). \texttt{kth(k)} is the $k$-th smallest element of the span (0-indexed, $k < 2^{\texttt{rk}}$); it makes the basis reduced, which is harmless.
- **G:** \texttt{insert} returns whether $x$ was independent, \texttt{has(x)}: $x$ in the span, \texttt{best(x)}: max $x \oplus s$ over the span, \texttt{kth(k)}: $k$-th smallest of the span (0-indexed, $k < 2^{rk}$).
- **L:** *(none)*
- **M:** = L
- Code comment (L, M): `ull best(ull x = 0) {` → `ull best(ull x = 0) { // max x ^ s over the span`
- Code comment (L, M): `ull kth(ull k) {` → `ull kth(ull k) { // k-th smallest, 0-indexed, k < 2^rk`

### `MatrixInverse.h`

- **Now:** Invert matrix $A$. Returns rank; result is stored in $A$ unless singular (rank < n). Can easily be extended to prime moduli; for prime powers, repeatedly set $A^{-1} = A^{-1} (2I - AA^{-1})\ (\text{mod }p^k)$ where $A^{-1}$ starts as the inverse of A mod p, and k is doubled in each step.
- **G:** Returns rank; $A^{-1}$ is stored in $A$ if rank $= n$. Mod $p^k$: start from the inverse mod $p$ and repeat $A^{-1} \gets A^{-1}(2I - AA^{-1})$, doubling $k$ each time.
- **L:** Returns rank; result in $A$ if rank $= n$. Mod $p^k$: from $X = A^{-1} \bmod p$ repeat $X \gets X(2I - AX)$.
- **M:** Returns rank; result in $A$ if rank $= n$.

### `FastFourierTransform.h`

- **Now:** \texttt{fft(a)} computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for all $k$, $N$ a power of 2. \texttt{conv(a, b) = c} with $c[x] = \sum a[i]b[x-i]$. Complex or more than two vectors: FFT, multiply pointwise, divide by n, reverse(start+1, end), FFT back. Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$ (in practice $10^{16}$, more if random); else NTT/FFTMod.
- **G:** Convolution with doubles: \texttt{conv(a, b)}$[x] = \sum a[i]b[x-i]$. Exact while $(\sum a_i^2 + \sum b_i^2)\log_2 N < 9\cdot10^{14}$ (in practice $10^{16}$), else NTT / FFTMod. By hand: FFT, multiply, divide by $n$, reverse(start+1, end), FFT back.
- **L:** Convolution (doubles), exact while $(\sum a_i^2 + \sum b_i^2)\log_2 N < 9\cdot10^{14}$. By hand: FFT, multiply, divide by $n$, reverse(start+1, end), FFT.
- **M:** Convolution; exact while $(\sum a_i^2 + \sum b_i^2)\log_2 N < 9\cdot10^{14}$.

### `FastFourierTransformMod.h`

- **Now:** Higher precision FFT, can be used for convolutions modulo arbitrary integers as long as $N\log_2N\cdot \text{mod} < 8.6 \cdot 10^{14}$ (in practice $10^{16}$ or higher). Inputs must be in $[0, \text{mod})$.
- **G:** Convolution modulo any \texttt{M}, inputs in $[0, M)$, while $N\log_2 N \cdot M < 8.6\cdot10^{14}$ (in practice $10^{16}$).
- **L:** Convolution mod any $M$, inputs in $[0, M)$; needs $N \log_2 N \cdot M < 8.6\cdot10^{14}$.
- **M:** = L

### `NumberTheoreticTransform.h`

- **Now:** \texttt{ntt(a)} computes $\hat f(k) = \sum_x a[x] g^{xk}$ for all $k$, $g=\text{root}^{(mod-1)/N}$, $N$ a power of 2. \texttt{conv(a, b) = c} with $c[x] = \sum a[i]b[x-i]$, modulo primes $2^a b+1$ with result size at most $2^a$ (any modulus: FFTMod). By hand: NTT the inputs, multiply pointwise, divide by n, reverse(start+1, end), NTT back. Inputs in [0, mod).
- **G:** Convolution mod a prime $2^a b + 1$ with result size $\le 2^a$ (default 998244353; any modulus: FFTMod). Inputs in $[0, mod)$. By hand: NTT, multiply, divide by $n$, reverse(start+1, end), NTT back.
- **L:** Convolution mod 998244353 (or a prime $2^a b + 1$, result size $\le 2^a$). Inputs in $[0, mod)$.
- **M:** Convolution mod \texttt{mod}. Inputs in $[0, mod)$.

### `FastSubsetTransform.h`

- **Now:** Transform to a basis with fast convolutions of the form $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$, where $\oplus$ is one of AND, OR, XOR. The size of $a$ must be a power of two.
- **G:** AND / OR / XOR convolution $c[z] = \sum_{x \oplus y = z} a[x]b[y]$ (choose the line in \texttt{FST}); size a power of 2.
- **L:** AND / OR / XOR convolution (choose in \texttt{FST}); size a power of 2.
- **M:** = L

### `PolyOps.h`

- **Now:** Power series modulo $x^n$ (coefficients in $[0, mod)$, NTT prime). \texttt{polyInv} needs $a_0 \ne 0$, \texttt{polyLog} needs $a_0 = 1$, \texttt{polyExp} needs $a_0 = 0$. All results have exactly $n$ coefficients. \texttt{polyPow(a, k, n)} is $a^k \bmod x^n$ for any $a$ (also with leading zeros) and $k$ up to $10^{18}$; \texttt{polySqrt} needs $a_0 = 1$; \texttt{polyDivMod(a, b)} returns $(q, r)$ with $a = qb + r$, $\deg r < \deg b$, and needs \texttt{b.back() != 0}.
- **G:** Power series mod $x^n$ and \texttt{mod} (NTT prime); results have exactly $n$ terms. \texttt{polyInv}: $a_0 \ne 0$; \texttt{polyLog}, \texttt{polySqrt}: $a_0 = 1$; \texttt{polyExp}: $a_0 = 0$; \texttt{polyPow(a, k, n)}: any $a$, $k \le 10^{18}$. \texttt{polyDivMod(a, b)} returns $(q, r)$, needs \texttt{b.back()} $\ne 0$.
- **L:** Mod $x^n$, $n$ terms out. Inv: $a_0 \ne 0$; Log, Sqrt: $a_0 = 1$; Exp: $a_0 = 0$; Pow: any $a$. \texttt{polyDivMod}: \texttt{b.back()} $\ne 0$.
- **M:** = L


## number-theory

### `ModularArithmetic.h`

- **Now:** Modular integers, \texttt{mint<mod>}: $+ - * /$, the compound forms, \texttt{++}, \texttt{--}, unary minus, comparisons, input and output, \texttt{fpow(a, p)} and \texttt{inverse(a)} (Fermat: needs a prime $mod$). $mod < 2^{30}$ (e.g. $10^9 + 7$ or $998244353$) so that the sum of two values fits an \texttt{int}; \texttt{(int)a} is the value in $[0, mod)$.
- **G:** \texttt{mint<mod>} for a prime $mod < 2^{30}$: arithmetic, comparisons, I/O, \texttt{fpow(a, p)}, \texttt{inverse(a)}; \texttt{(int)a} is the value.
- **L:** Prime $mod < 2^{30}$. \texttt{fpow(a, p)}, \texttt{inverse(a)}, \texttt{(int)a}.
- **M:** Prime $mod < 2^{30}$.

### `ModInverse.h`

- **Now:** Pre-computation of modular inverses. Assumes LIM $\le$ mod and that mod is a prime.
- **G:** Inverses of $1..LIM-1$; LIM $\le$ mod, mod prime.
- **L:** = G
- **M:** LIM $\le$ mod, mod prime.

### `ModPow.h`

- **Now:** *(none)*
- **G:** *(none)*
- **L:** = G
- **M:** = L

### `ModLog.h`

- **Now:** Returns the smallest $x > 0$ s.t. $a^x = b \pmod m$, or $-1$ if no such $x$ exists. modLog(a,1,m) can be used to calculate the order of $a$.
- **G:** Smallest $x > 0$ with $a^x \equiv b \pmod m$ (any $m$), or $-1$. \texttt{modLog(a, 1, m)} is the order of $a$.
- **L:** Smallest $x > 0$, or $-1$. \texttt{modLog(a, 1, m)}: order of $a$.
- **M:** = L

### `ModSum.h`

- **Now:** Sums of mod'ed arithmetic progressions. \texttt{modsum(to, c, k, m)} = $\sum_{i=0}^{\mathrm{to}-1}{(ki+c) \% m}$. \texttt{divsum} is similar but for floored division.
- **G:** \texttt{modsum(to, c, k, m)} $= \sum_{i=0}^{to-1} (ki + c) \bmod m$; \texttt{divsum}: the same with $\lfloor (ki + c)/m \rfloor$.
- **L:** = G
- **M:** = L

### `ModMulLL.h`

- **Now:** Calculate $a\cdot b\bmod c$ (or $a^b \bmod c$) for $0 \le a, b \le c \le 7.2\cdot 10^{18}$.
- **G:** $ab \bmod c$ and $a^b \bmod c$ for $0 \le a, b \le c \le 7.2\cdot10^{18}$.
- **L:** = G
- **M:** $a, b \le c \le 7.2\cdot10^{18}$.

### `ModSqrt.h`

- **Now:** Tonelli-Shanks algorithm for modular square roots. Finds $x$ s.t. $x^2 = a \pmod p$ ($-x$ gives the other solution).
- **G:** $x$ with $x^2 \equiv a \pmod p$, $p$ prime (Tonelli-Shanks); $-x$ is the other root; asserts if there is none.
- **L:** $x^2 \equiv a \pmod p$, $p$ prime; $-x$ is the other root; asserts if none.
- **M:** Prime $p$; asserts if no root.

### `PrimitiveRoot.h`

- **Now:** Smallest primitive root of the prime $p$ ($p \le 7 \cdot 10^{18}$, but $p - 1$ is factored by trial division, so $p \lesssim 10^{12}$; use \texttt{Factor} beyond). A primitive root $g$ has order $p - 1$; e.g. 998244353 has $g = 3$, $10^9 + 7$ has $g = 5$.
- **G:** Smallest primitive root of a prime $p$; $p - 1$ is factored by trial division, so $p \lesssim 10^{12}$ (else use \texttt{Factor}). 998244353: 3, $10^9 + 7$: 5.
- **L:** Prime $p \lesssim 10^{12}$ (trial division; else \texttt{Factor}). 998244353: 3, $10^9 + 7$: 5.
- **M:** = L

### `FastEratosthenes.h`

- **Now:** Prime sieve for generating all primes smaller than LIM.
- **G:** Primes below LIM; also fills \texttt{isPrime}.
- **L:** Primes below LIM.
- **M:** = L

### `MillerRabin.h`

- **Now:** Deterministic Miller-Rabin primality test. Guaranteed to work for numbers up to $7 \cdot 10^{18}$; for larger numbers, use Python and extend A randomly.
- **G:** Deterministic for $n < 7\cdot10^{18}$.
- **L:** = G
- **M:** = L

### `Factor.h`

- **Now:** Pollard-rho randomized factorization algorithm. Returns prime factors of a number, in arbitrary order (e.g. 2299 -> \{11, 19, 11\}).
- **G:** Prime factors with multiplicity, in any order (Pollard rho).
- **L:** Prime factors with multiplicity, unsorted.
- **M:** = L

### `euclid.h`

- **Now:** Finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$. If you just need gcd, use the built in \texttt{\_\_gcd} instead. If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
- **G:** Returns $\gcd(a, b)$ and sets $ax + by = \gcd$; if coprime, $x = a^{-1} \bmod b$.
- **L:** $ax + by = \gcd(a, b)$ (returned).
- **M:** *(none)*
- Code comment (L, M): `ll euclid(ll a, ll b, ll &x, ll &y) {` → `ll euclid(ll a, ll b, ll &x, ll &y) { // ax + by = gcd`

### `CRT.h`

- **Now:** Chinese Remainder Theorem. \texttt{crt(a, m, b, n)} computes $x$ such that $x\equiv a \pmod m$, $x\equiv b \pmod n$. If $|a| < m$ and $|b| < n$, $x$ will obey $0 \le x < \text{lcm}(m, n)$. Assumes $mn < 2^{62}$.
- **G:** $x \equiv a \pmod m$, $x \equiv b \pmod n$, $0 \le x < \mathrm{lcm}$ if $|a| < m$, $|b| < n$; asserts if none. Needs $mn < 2^{62}$.
- **L:** $0 \le x < \mathrm{lcm}(m, n)$ if $|a| < m$, $|b| < n$; asserts if none. $mn < 2^{62}$.
- **M:** = L

### `ExLucas.h`

- **Now:** Binomial $\binom{n}{k} \bmod m$ for any $m < 2^{31}$ (extended Lucas). Per prime power $q = p^a$: $n!$ with factors $p$ removed (product of units mod $q$ is $-1$, or $+1$ if $p=2, a\ge3$) and $v_p(n!)$ by Legendre; then CRT with $c \equiv [q]$. Requires $n \le mx$; tables have size $\min(q, mx+1)$.
- **G:** $\binom{n}{k} \bmod m$ for any $m < 2^{31}$ and $n \le mx$ (extended Lucas: per prime power, $n!$ without the factors $p$, then CRT).
- **L:** $\binom{n}{k} \bmod m$, any $m < 2^{31}$, $n \le mx$.
- **M:** = L

### `phiFunction.h`

- **Now:** \emph{Euler's $\phi$} function is defined as $\phi(n):=\#$ of positive integers $\leq n$ that are coprime with $n$. $\phi(1)=1$, $p$ prime $\Rightarrow \phi(p^k)=(p-1)p^{k-1}$, $m,n$ coprime $\Rightarrow \phi(mn)=\phi(m)\phi(n)$. If $n=p_1^{k_1}p_2^{k_2} ... p_r^{k_r}$ then $\phi(n) = (p_1-1)p_1^{k_1-1}...(p_r-1)p_r^{k_r-1}$. $\phi(n)=n \cdot \prod_{p|n}(1-1/p)$. $\sum_{d|n} \phi(d) = n$, $\sum_{1\leq k \leq n, \gcd(k,n)=1} k = n \phi(n)/2, n>1$ \textbf{Euler's thm}: $a,n$ coprime $\Rightarrow a^{\phi(n)} \equiv 1 \pmod{n}$. \textbf{Fermat's little thm}: $p$ prime $\Rightarrow a^{p-1} \equiv 1 \pmod{p}$ $\forall a$.
- **G:** Sieve of Euler's $\phi$ below LIM. $\phi(n) = n \prod_{p \mid n} (1 - 1/p)$, $\sum_{d \mid n} \phi(d) = n$, $\sum_{k \le n, \gcd(k, n) = 1} k = n\phi(n)/2$ ($n > 1$). Euler: $a^{\phi(n)} \equiv 1 \pmod n$ if $\gcd(a, n) = 1$.
- **L:** Sieve of $\phi$ below LIM. $\sum_{d \mid n} \phi(d) = n$; $\sum_{k \le n, \gcd(k, n) = 1} k = n\phi(n)/2$ ($n > 1$).
- **M:** Sieve of $\phi$ below LIM.

### `Lucy.h`

- **Now:** Prime counting and prime sums for all $v = \lfloor n/i \rfloor$ and all $v \le \sqrt n$. \texttt{f(p)} is a completely multiplicative function at a prime (\texttt{1} counts, \texttt{p} sums, $p^k$ power sums) and \texttt{g(v)} $= f(2) + \dots + f(v)$ in closed form; the type of \texttt{g(v)} is the type of the result (use \texttt{ull} to sum modulo $2^{64}$). \texttt{L(v)} is then $\sum_{p \le v} f(p)$ for such a $v$.
- **G:** $\sum_{p \le v} f(p)$ over primes, for all $v = \lfloor n/i \rfloor$; $f$ completely multiplicative (\texttt{1}: count, \texttt{p}: sum), \texttt{g(v)} $= f(2) + \dots + f(v)$ in closed form. The result type is \texttt{g}'s (\texttt{ull}: mod $2^{64}$).
- **L:** $\sum_{p \le v} f(p)$, $v = \lfloor n/i \rfloor$; $f$ completely multiplicative, \texttt{g(v)} $= f(2) + \dots + f(v)$. Result type: \texttt{g}'s.
- **M:** \texttt{g(v)} $= f(2) + \dots + f(v)$, $f$ completely multiplicative; type from \texttt{g}.

### `DuSieve.h`

- **Now:** Prefix sums of $\phi$ (128 bit: $\Phi(10^{10}) \approx 3 \cdot 10^{19}$) and $\mu$ for all $v = \lfloor n/i \rfloor$ and all $v \le B = n^{2/3}$, from a sieve up to $B$ and $S_f(v) = H(v) - \sum_{d \ge 2} S_f(\lfloor v/d \rfloor)$ for $f * 1 = h$ ($H$ the prefix sums of $h$: $v(v+1)/2$ for $\phi$, $1$ for $\mu$). The same recurrence $S_f(v) = (H(v) - \sum_{d \ge 2} g(d) S_f(\lfloor v/d \rfloor))/g(1)$ handles any $f * g = h$ with known prefix sums of $g$ and $h$. Memory is also $O(n^{2/3})$.
- **G:** Prefix sums $\Phi$ (128-bit) and $M$ of $\phi$ and $\mu$ at any $v = \lfloor n/i \rfloor$ or $v \le n^{2/3}$. Any $f$ with $f * g = h$ and known prefix sums $G$, $H$: $S_f(v) = (H(v) - \sum_{d \ge 2} g(d) S_f(\lfloor v/d \rfloor))/g(1)$.
- **L:** $\Phi$ (128-bit) and $M$ at $v = \lfloor n/i \rfloor$ or $v \le n^{2/3}$. Other $f$, $f * g = h$: $S_f(v) = (H(v) - \sum_{d \ge 2} g(d) S_f(\lfloor v/d \rfloor))/g(1)$.
- **M:** At $v = \lfloor n/i \rfloor$ or $v \le n^{2/3}$; $\Phi$ is 128-bit.


## combinatorial

### `IntPerm.h`

- **Now:** Permutation of $0, \ldots, n-1$ $\leftrightarrow$ integer in $[0, n!)$: \texttt{permToInt} is the rank of the permutation in lexicographic order and \texttt{intToPerm(r, n)} is the \texttt{r}'th permutation (0-indexed), its exact inverse. Order preserving. Exact for $n \le 20$. For a permutation whose size is not fixed, see \texttt{radixToPerm}.
- **G:** Rank of a permutation of $0..n-1$ in lexicographic order, and back (\texttt{intToPerm(r, n)}); $n \le 20$. Unknown size: \texttt{radixToPerm}.
- **L:** $n \le 20$. Unknown size: \texttt{radixToPerm}.
- **M:** $n \le 20$.

### `multinomial.h`

- **Now:** Computes $\displaystyle \binom{k_1 + \dots + k_n}{k_1, k_2, \dots, k_n} = \frac{(\sum k_i)!}{k_1!k_2!...k_n!}$.
- **G:** $(\sum k_i)! / \prod k_i!$, exact while it fits in \texttt{ll}.
- **L:** $(\sum k_i)! / \prod k_i!$.
- **M:** = L

### `RadixConversion.h`

- **Now:** Bijective base conversion: digits in $[0, a)$ to digits in $[0, b)$ ($2 \le a, b < 2^{31}$), most significant first. The $k$-th sequence in (length, lexicographic) order in base $a$ maps to the $k$-th in base $b$ (empty to empty), so \texttt{radixconv(radixconv(x, a, b), b, a) == x} with no length or leading zeros to store; the result has about $|x| \log_b a$ digits. \texttt{radixToPerm(x, a)} does the same onto all permutations of $0, \ldots, n-1$ ($n$ comes from the data: 2000 bits give 296 elements), in (size, lexicographic) order; \texttt{permToRadix(p, a)} is its inverse ($O(|y|^2)$, $y$ the result). Fixed size: \texttt{intToPerm}, or \texttt{radixToPerm} on the base $2^{31}-1$ digits of $r + 0! + \dots + (n-1)!$ (one digit for $n \le 12$, two up to 20).
- **G:** Bijective base conversion, most significant first: the $k$-th sequence (by length, then lexicographic) over $[0, a)$ goes to the $k$-th over $[0, b)$, $2 \le a, b < 2^{31}$: no length or leading zeros to store, about $|x| \log_b a$ digits. \texttt{radixToPerm} / \texttt{permToRadix}: the same onto permutations (size from the data). Fixed size $n$: \texttt{radixToPerm} of the base $2^{31}-1$ digits of $r + 0! + \dots + (n-1)!$.
- **L:** $k$-th sequence (by length, then lex) over $[0, a)$ $\to$ $k$-th over $[0, b)$, most significant first. \texttt{radixToPerm} / \texttt{permToRadix}: the same with permutations (size from the data).
- **M:** $k$-th (length, then lex) $\to$ $k$-th; \texttt{radixToPerm}: onto permutations.


## graph

### `PushRelabel.h`

- **Now:** Push-relabel using the highest label selection rule and the gap heuristic. Quite fast in practice. To obtain the actual flow, look at positive values only.
- **G:** Max flow, fast in practice. Flow on an edge: its positive \texttt{f}.
- **L:** Flow on an edge: its positive \texttt{f}.
- **M:** = L

### `MinCostMaxFlow.h`

- **Now:** Min-cost max-flow. If costs can be negative, call setpi before maxflow, but note that negative cost cycles are not supported. To obtain the actual flow, look at positive values only.
- **G:** Negative costs: call \texttt{setpi} first (no negative cycles). Flow on an edge: its positive \texttt{flow}.
- **L:** = G
- **M:** Negative costs: \texttt{setpi} first.

### `Dinic.h`

- **Now:** Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$. $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
- **G:** Max flow.
- **L:** *(none)*
- **M:** Min cut: \texttt{leftOfMinCut} (reachable from $s$ in the residual graph).
- Time (G and later): *(none)* → `O(VE\log U) with $U = \max|cap|$; $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt V E)$ for matching`

### `MinCut.h`

- **Now:** After running max-flow, the left side of a min-cut from $s$ to $t$ is given by all vertices reachable from $s$, only traversing edges with positive residual capacity.
- **G:** After max flow, the $s$ side of a min cut = vertices reachable from $s$ through edges with positive residual capacity.
- **L:** $s$ side of a min cut: reachable from $s$ in the residual graph.
- **M:** = L
- M: this file is no longer printed; its note moves into `Dinic.h`.

### `GlobalMinCut.h`

- **Now:** Find a global minimum cut in an undirected graph, as represented by an adjacency matrix.
- **G:** Stoer-Wagner on an adjacency matrix; returns (weight, one side).
- **L:** Adjacency matrix; returns (weight, one side).
- **M:** = L

### `GomoryHu.h`

- **Now:** Given a list of edges representing an undirected flow graph, returns edges of the Gomory-Hu tree. The max flow between any pair of vertices is given by minimum edge weight along the Gomory-Hu tree path.
- **G:** Gomory-Hu tree of an undirected graph: max flow $u$--$v$ = min edge on the tree path.
- **L:** Max flow $u$--$v$ = min edge on the tree path.
- **M:** = L

### `HopcroftKarp.h`

- **Now:** Bipartite matching. $g$: neighbours of each left vertex; $r$: all $-1$, size of the right side. Returns the matching size; $r[i]$ is the match of right vertex $i$, or $-1$.
- **G:** $g$: neighbours of each left vertex; $r$: all $-1$, size of the right side. Returns the matching size; $r[i]$ = match of right vertex $i$ or $-1$.
- **L:** $g$: left adjacency; $r$: all $-1$, size of the right side, gets the match of each right vertex.
- **M:** $r$: all $-1$, size of the right side; gets the matches.

### `MinimumVertexCover.h`

- **Now:** Finds a minimum vertex cover in a bipartite graph. The size is the same as the size of a maximum matching, and the complement is a maximum independent set.
- **G:** Bipartite; in the output left vertex $i$ is $i$, right vertex $j$ is $n + j$. Size = max matching; complement = max independent set.
- **L:** Complement: max independent set.
- **M:** *(none)*
- Code comment (L, M): `vi cover(vector<vi>& g, int n, int m) {` → `vi cover(vector<vi>& g, int n, int m) { // right j -> n+j`

### `WeightedMatching.h`

- **Now:** Min-cost bipartite matching that matches every left node, $N \le M$. Takes cost[N][M] (cost[i][j]: L[i] with R[j]), returns (min cost, match) with L[i] matched to R[match[i]]. Negate costs for max cost.
- **G:** Min-cost bipartite matching using every left node, $N \le M$; returns (cost, match), L[i] $\to$ R[match[i]]. Max: negate the costs.
- **L:** Min cost, every left node matched, $N \le M$. Max: negate.
- **M:** Min cost, $N \le M$.

### `GeneralMatching.h`

- **Now:** Matching for general graphs. Fails with probability $N / mod$.
- **G:** Maximum matching (randomized, fails with probability $N/mod$).
- **L:** Randomized, fails with probability $N/mod$.
- **M:** = L

### `SCC.h`

- **Now:** Finds strongly connected components in a directed graph. If vertices $u, v$ belong to the same component, we can reach $u$ from $v$ and vice versa.
- **G:** Tarjan.
- **L:** *(none)*
- **M:** = L
- Usage (L and later): `scc(graph, [\&](vi\& v) { ... }) visits all components in reverse topological order. comp[i] holds the component index of a node (a component only has edges to components with lower index). ncomps will contain the number of components.` → `scc(g, [\&](vi\& v) { ... }) visits the components in reverse topological order. comp[i]: component of i (edges only go to lower indices); ncomps: their number.`
- Usage (M and later): `scc(graph, [\&](vi\& v) { ... }) visits all components in reverse topological order. comp[i] holds the component index of a node (a component only has edges to components with lower index). ncomps will contain the number of components.` → `scc(g, [\&](vi\& v) {...}); // reverse topological order comp[i]: component (edges go to lower comp), ncomps.`

### `BiconnectedComponents.h`

- **Now:** Runs the callback on the edges of each biconnected component (any two of its nodes lie on a common cycle). A node can be in several components; an edge in none is a bridge.
- **G:** Calls \texttt{f} with the edge ids of each biconnected component; an edge in none is a bridge.
- **L:** Edge ids per component; an edge in none is a bridge.
- **M:** = L
- Usage (M and later): `int eid = 0; ed.resize(N); for each edge (a,b) { ed[a].emplace_back(b, eid); ed[b].emplace_back(a, eid++); } bicomps([\&](const vi\& edgelist) {...});` → `int eid = 0; ed.resize(N); // per edge (a, b): ed[a].emplace_back(b, eid); ed[b].emplace_back(a, eid++); bicomps([\&](const vi\& edgelist) {...});`

### `BlockCutTree.h`

- **Now:** Block-cut tree of an undirected graph (a forest if it is not connected). Nodes $0..n-1$ are the vertices; every biconnected component (a bridge is a component with 2 vertices) gets one more node, adjacent to its vertices. A vertex is a cut vertex iff it has more than one neighbour in the tree. Vertex $w$ separates $u$ and $v$ iff it is a cut vertex on the tree path $u \dots v$.
- **G:** Nodes $0..n-1$ are the vertices, then one node per biconnected component (a bridge is one with 2 vertices), adjacent to its vertices; a forest. Cut vertex iff tree degree $> 1$; $w$ separates $u$, $v$ iff it is a cut vertex on their tree path.
- **L:** Vertices $0..n-1$, then one node per block (bridges too). Cut vertex iff tree degree $> 1$.
- **M:** = L

### `2sat.h`

- **Now:** Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem, so that an expression of the type $(a||b)\&\&(!a||c)\&\&(d||!b)\&\&...$ becomes true, or reports that it is unsatisfiable. Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
- **G:** Negation: \texttt{\textasciitilde x}.
- **L:** *(none)*
- **M:** = L
- Usage (M and later): `TwoSat ts(number of boolean variables); ts.either(0, \tilde3); // Var 0 is true or var 3 is false ts.setValue(2); // Var 2 is true ts.atMostOne({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2 are true ts.solve(); // Returns true iff it is solvable ts.values[0..N-1] holds the assigned values to the vars` → `TwoSat ts(n); ts.either(0, \tilde3); // 0 or not 3 ts.setValue(2); ts.atMostOne({0, \tilde1, 2}); ts.solve(); // true iff solvable; values in ts.values`
- Time (L and later): `O(N+E), where N is the number of boolean variables, and E is the number of clauses.` → `O(N + E)`

### `EulerWalk.h`

- **Now:** Euler path/cycle, undirected or directed. Input: lists of (dest, global edge index); both directions of an undirected edge share the index. Returns the nodes of the walk (src at both ends for a cycle), or empty if there is none. Edge indices: add .second to s and ret.
- **G:** Euler path / cycle from \texttt{src}, undirected or directed. Lists of (dest, edge id); an undirected edge has one id both ways. Returns the nodes (src at both ends for a cycle), empty if none. Edge ids: also push \texttt{.second}.
- **L:** Lists of (dest, edge id), one id for both directions. Returns the node list, empty if impossible.
- **M:** = L

### `MaximalCliques.h`

- **Now:** Runs a callback for all maximal cliques in a graph (given as a symmetric bitset matrix; self-edges not allowed). Callback is given a bitset representing the maximal clique.
- **G:** Calls \texttt{f} with every maximal clique. Symmetric bitset matrix, no self-edges.
- **L:** Symmetric bitset matrix, no self-edges.
- **M:** = L

### `MaximumClique.h`

- **Now:** Quickly finds a maximum clique of a graph (given as symmetric bitset matrix; self-edges not allowed). Can be used to find a maximum independent set by finding a clique of the complement graph.
- **G:** Symmetric bitset matrix, no self-edges. Max independent set: a max clique of the complement.
- **L:** Symmetric bitset matrix, no self-edges.
- **M:** Symmetric bitset matrix, no self-edges. Max independent set: clique of the complement (bipartite: \texttt{MinimumVertexCover}).
- Time (L and later): `Runs in about 1s for n=155 and worst case random graphs (p=.90). Runs faster for sparse graphs.` → `About 1 s for $n = 155$, $p = .9$; faster when sparse`

### `MaximumIndependentSet.h`

- **Now:** To obtain a maximum independent set of a graph, find a max clique of the complement. If the graph is bipartite, see MinimumVertexCover.
- **G:** Max clique of the complement. Bipartite: complement of \texttt{MinimumVertexCover}.
- **L:** = G
- **M:** = L
- M: this file is no longer printed; its note moves into `MaximumClique.h`.

### `BinaryLifting.h`

- **Now:** Calculate power of two jumps in a tree, to support fast upward jumps and LCAs. Assumes the root node points to itself.
- **G:** Jump tables for $k$-th ancestors and LCA; the root's parent must be itself.
- **L:** The root's parent must be itself.
- **M:** = L

### `LCA.h`

- **Now:** Data structure for computing lowest common ancestors in a tree (with 0 as root). C should be an adjacency list of the tree, either directed or undirected.
- **G:** Euler tour + RMQ; root 0, adjacency list (directed or undirected).
- **L:** Root 0; adjacency list, directed or undirected.
- **M:** = L

### `CompressTree.h`

- **Now:** Given a rooted tree and a subset S of nodes, compute the minimal subtree that contains all the nodes by adding all (at most $|S|-1$) pairwise LCA's and compressing edges. Returns a list of (par, orig\_index) representing a tree rooted at 0. The root points to itself.
- **G:** Virtual tree of a subset: the subset plus pairwise LCAs. Returns (parent index, original node); the root is first and is its own parent.
- **L:** Virtual tree; returns (parent index, original node), root first (own parent).
- **M:** = L

### `HLD.h`

- **Now:** Heavy-light decomposition: every path to the root has $O(\log n)$ light edges. Path and subtree updates and queries go to a \texttt{LazySeg} (edit its block for other operations): updates take its tag \texttt{L}, queries return its value \texttt{S}, all values start as \texttt{S()}. Takes the full adjacency list, root 0. \texttt{VALS\_EDGES}: values on the edges instead of the nodes.
- **G:** Performs HLD over a \texttt{LazySeg} (edit its block): updates take \texttt{L}, queries return \texttt{S}, values start as \texttt{S()}. Full adjacency list, root 0. \texttt{VALS\_EDGES}: values on the edges.
- **L:** Performs HLD. Full adjacency list, root 0; ops use \texttt{LazySeg}'s \texttt{L} / \texttt{S}. \texttt{VALS\_EDGES}: values on edges.
- **M:** Root 0; \texttt{LazySeg}'s \texttt{L} / \texttt{S}. \texttt{VALS\_EDGES}: values on edges.

### `CentroidDecomposition.h`

- **Now:** Centroid decomposition. \texttt{run(f)} calls \texttt{f(c)} once per centroid $c$; at that moment a DFS from $c$ that skips \texttt{dead} vertices visits exactly the component of $c$ (centroids of earlier calls are \texttt{dead}). \texttt{cpar} is the centroid tree (root has $-1$). Each vertex is in $O(\log N)$ components.
- **G:** \texttt{run(f)} calls \texttt{f(c)} per centroid $c$; a DFS from $c$ skipping \texttt{dead} then visits exactly its component. \texttt{cpar}: the centroid tree (root $-1$).
- **L:** In \texttt{f(c)}, a DFS from $c$ skipping \texttt{dead} visits its component. \texttt{cpar}: centroid tree.
- **M:** = L

### `DsuOnTree.h`

- **Now:** Answers a question about every subtree using one global structure. \texttt{add(v)} / \texttt{rem(v)} insert / remove vertex $v$ (and only $v$) from it; \texttt{query(v)} is called when the structure holds exactly the vertices of the subtree of $v$.
- **G:** Small to large: \texttt{add(v)} / \texttt{rem(v)} put one vertex into / out of a global structure; \texttt{query(v)} runs when it holds exactly the subtree of $v$.
- **L:** \texttt{query(v)} runs when exactly the subtree of $v$ is \texttt{add}ed (\texttt{add}, \texttt{rem}: one vertex).
- **M:** = L

### `LinkCutTree.h`

- **Now:** Represents a forest of unrooted trees. You can add and remove edges (as long as the result is still a forest), and check whether two nodes are in the same tree.
- **G:** Forest with \texttt{link}, \texttt{cut} (must stay a forest) and \texttt{connected}.
- **L:** Must stay a forest.
- **M:** = L

### `DirectedMST.h`

- **Now:** Finds a minimum spanning tree/arborescence of a directed graph, given a root node. If no MST exists, returns -1.
- **G:** Minimum arborescence rooted at $r$: (cost, parents), cost $-1$ if none.
- **L:** Root $r$; returns (cost, par), $-1$ if none.
- **M:** = L


## geometry

### `Point.h`

- **Now:** Class to handle points in the plane. T can be e.g. double or long long. (Avoid int.)
- **G:** \texttt{T}: double or long long (avoid int).
- **L:** = G
- **M:** = L

### `lineDistance.h`

- **Now:** Signed distance from p to the line through a and b, positive on the left as seen from a towards b; a==b gives nan. T is double or long long; uses products of two coordinates (overflow).
- **G:** Signed distance from p to the line through a and b, positive on the left of $a \to b$; a==b gives nan.
- **L:** Signed, positive left of $a \to b$.
- **M:** = L

### `SegmentDistance.h`

- **Now:** Returns the shortest distance between point p and the line segment from point s to e.
- **G:** Distance from p to the segment se.
- **L:** *(none)*
- **M:** = L
- Usage (M and later): `Point<double> a, b(2,2), p(1,1); bool onSegment = segDist(a,b,p) < 1e-10;` → `bool onSegment = segDist(a,b,p) < 1e-10;`

### `SegmentIntersection.h`

- **Now:** Intersection of segments s1-e1 and s2-e2: one point, none (empty vector), or the two endpoints of the common segment if there are infinitely many. With Point<ll> the point is wrong if it is not integral. Uses products of three coordinates (overflow).
- **G:** One point, none, or the two endpoints of the common part. With Point<ll> the point is wrong if not integral. Products of 3 coordinates.
- **L:** One point, none, or the ends of the overlap. Point<ll>: only integral points.
- **M:** = L
- Usage (M and later): `vector<P> inter = segInter(s1,e1,s2,e2); if (sz(inter)==1) cout << "segments intersect at " << inter[0] << endl;` → `vector<P> inter = segInter(s1,e1,s2,e2);`

### `lineIntersection.h`

- **Now:** Intersection of the lines through s1,e1 and s2,e2: \{1, point\} if unique, \{0, (0,0)\} if parallel, \{-1, (0,0)\} if they are the same line. With Point<ll> the point is wrong if it is not integral. Uses products of three coordinates (overflow).
- **G:** \{1, p\} if unique, \{0, (0,0)\} if parallel, \{-1, (0,0)\} if the same line. With Point<ll> only integral points. Products of 3 coordinates.
- **L:** \{1, p\}; \{0, \_\} parallel; \{-1, \_\} same line. Point<ll>: only integral points.
- **M:** = L
- Usage (M and later): `auto res = lineInter(s1,e1,s2,e2); if (res.first == 1) cout << "intersection point at " << res.second << endl;` → `auto [k, p] = lineInter(s1,e1,s2,e2); // k = 1: unique`

### `sideOf.h`

- **Now:** 1/0/-1 if $p$ is left of/on/right of the line from $s$ towards $e$. With $eps$, 0 if $p$ is within distance $eps$ of the line. Uses products of coordinates (overflow).
- **G:** 1 / 0 / $-1$: $p$ left of / on / right of $s \to e$; with \texttt{eps}, within distance \texttt{eps} counts as on.
- **L:** 1 / 0 / $-1$: left / on / right of $s \to e$ (on: within \texttt{eps}).
- **M:** = L
- Usage (M and later): `bool left = sideOf(p1,p2,q)==1;` → *(dropped)*

### `OnSegment.h`

- **Now:** Returns true iff p lies on the line segment from s to e. Use \texttt{(segDist(s,e,p)<=epsilon)} instead when using Point<double>.
- **G:** Doubles: use \texttt{segDist(s,e,p) <= eps} instead.
- **L:** = G
- **M:** = L

### `linearTransformation.h`

- **Now:** Apply the linear transformation (translation, rotation and scaling) which takes line p0-p1 to line q0-q1 to point r.
- **G:** Maps $r$ by the similarity taking $p_0 \to q_0$, $p_1 \to q_1$.
- **L:** = G
- **M:** = L

### `LineProjectionReflection.h`

- **Now:** Projects point p onto line ab. Set refl=true to get reflection of point p across line ab instead. The wrong point will be returned if P is an integer point and the desired point doesn't have integer coordinates. Products of three coordinates are used in intermediate steps so watch out for overflow.
- **G:** Projection of $p$ on line $ab$ (reflection if \texttt{refl}). Point<ll>: only integral results; products of 3 coordinates.
- **L:** Reflection if \texttt{refl}. Point<ll>: only integral results.
- **M:** = L

### `Angle.h`

- **Now:** A class for ordering angles (as represented by int points and a number of rotations around the origin). Useful for rotational sweeping. Sometimes also represents points or vectors.
- **G:** Angles as int points plus full turns \texttt{t}, totally ordered; for rotational sweeps.
- **L:** Int point plus full turns \texttt{t}; totally ordered.
- **M:** = L
- Usage (M and later): `vector<Angle> v = {w[0], w[0].t360() ...}; // sorted int j = 0; rep(i,0,n) { while (v[j] < v[i].t180()) ++j; } // sweeps j such that (j-i) represents the number of positively oriented triangles with vertices at 0 and i` → `vector<Angle> v = {w[0], w[0].t360() ...}; // sorted int j = 0; rep(i,0,n) { while (v[j] < v[i].t180()) ++j; }`

### `CircleIntersection.h`

- **Now:** Computes the pair of points at which two circles intersect. Returns false in case of no intersection.
- **G:** False if none, else the two points in \texttt{out}.
- **L:** = G
- **M:** = L

### `CircleTangents.h`

- **Now:** External tangents of two circles (internal ones if r2 is negated). Returns 0 tangents if one circle contains the other (internal case: also if they overlap; also if equal), 1 if they touch (.first = .second, perpendicular to the center line), else 2. .first and .second are the tangency points on circle 1 and 2. Tangents from a point: r2 = 0.
- **G:** External tangents (internal: negate r2; from a point: r2 = 0) as (point on c1, point on c2): none if one circle contains the other (internal: also if they overlap), 1 if they touch (\texttt{.first = .second}), else 2.
- **L:** Internal: negate r2; from a point: r2 = 0. Pairs (point on c1, point on c2); 1 if touching, 0 if nested.
- **M:** Internal: r2 $< 0$; point: r2 = 0. Pairs (on c1, on c2).

### `CircleLine.h`

- **Now:** Finds the intersection between a circle and a line. Returns a vector of either 0, 1, or 2 intersection points. P is intended to be Point<double>.
- **G:** 0, 1 or 2 points.
- **L:** *(none)*
- **M:** = L

### `CirclePolygonIntersection.h`

- **Now:** Returns the area of the intersection of a circle with a ccw polygon.
- **G:** Area of circle $\cap$ ccw polygon.
- **L:** = G
- **M:** = L

### `circumcircle.h`

- **Now:** The circumcirle of a triangle is the circle intersecting all three vertices. ccRadius returns the radius of the circle going through points A, B and C and ccCenter returns the center of the same circle.
- **G:** Radius and center of the circle through A, B and C.
- **L:** = G
- **M:** = L

### `MinimumEnclosingCircle.h`

- **Now:** Computes the minimum circle that encloses a set of points.
- **G:** Smallest enclosing circle (center, radius).
- **L:** Returns (center, radius).
- **M:** = L

### `InsidePolygon.h`

- **Now:** Returns true if p lies within the polygon. If strict is true, it returns false for points on the boundary. The algorithm uses products in intermediate steps so watch out for overflow.
- **G:** \texttt{strict}: the boundary is outside. Products of coordinates (overflow).
- **L:** = G
- **M:** = L
- Usage (M and later): `vector<P> v = {P{4,4}, P{1,2}, P{2,1}}; bool in = inPolygon(v, P{3, 3}, false);` → `bool in = inPolygon(v, P{3, 3}, false);`

### `PolygonArea.h`

- **Now:** Returns twice the signed area of a polygon. Clockwise enumeration gives negative area. Watch out for overflow if using int as T!
- **G:** Twice the signed area (clockwise is negative).
- **L:** = G
- **M:** *(none)*
- Code comment (L, M): `T polygonArea2(vector<Point<T>>& v) {` → `T polygonArea2(vector<Point<T>>& v) { // 2x, cw < 0`

### `PolygonCenter.h`

- **Now:** Returns the center of mass for a polygon.
- **G:** Center of mass.
- **L:** *(none)*
- **M:** = L

### `PolygonCut.h`

- **Now:** Returns a vector with the vertices of a polygon with everything to the left of the line going from s to e cut away.
- **G:** Keeps the part to the right of $s \to e$.
- **L:** = G
- **M:** = L
- Usage (M and later): `vector<P> p = ...; p = polygonCut(p, P(0,0), P(1,0));` → `p = polygonCut(p, P(0,0), P(1,0));`

### `HalfPlane.h`

- **Now:** Intersection of half-planes. Each half-plane is a pair $(s, e)$: the points on the left of the directed line $s \to e$. Returns the vertices of the intersection in ccw order, or an empty vector if it is empty. Use \texttt{Point<double>}, and add a large bounding box (4 half-planes) if the intersection may be unbounded. Touching or degenerate results may come back either empty or with (almost) zero area.
- **G:** Half-plane $(s, e)$ = left of $s \to e$. Returns the intersection in ccw order, empty if empty (or degenerate). Use doubles; add a big bounding box if it may be unbounded.
- **L:** $(s, e)$ = left of $s \to e$; ccw result. Doubles; add a big box if unbounded.
- **M:** = L

### `ConvexHull.h`

- **Now:** Returns a vector of the points of the convex hull in counter-clockwise order. Points on the edge of the hull between two other points are not considered part of the hull.
- **G:** Counter-clockwise; collinear points are dropped.
- **L:** ccw, no collinear points.
- **M:** = L

### `HullDiameter.h`

- **Now:** Returns the two points with max distance on a convex hull (ccw, no duplicate/collinear points).
- **G:** Farthest pair of a ccw hull without collinear points.
- **L:** ccw hull, no collinear points.
- **M:** = L

### `PointInsideHull.h`

- **Now:** Determine whether a point t lies inside a convex hull (CCW order, with no collinear points). Returns true if point lies within the hull. If strict is true, points on the boundary aren't included.
- **G:** ccw hull without collinear points; \texttt{strict}: the boundary is outside.
- **L:** = G
- **M:** = L
- Usage (G and later): *(none)* → *(dropped)*

### `LineHullIntersection.h`

- **Now:** Line vs convex polygon (ccw, no collinear points). \texttt{lineHull(line, poly)} returns $(-1, -1)$ if no collision, $(i, -1)$ if touching corner $i$, $(i, i)$ if along side $(i, i+1)$, $(i, j)$ if crossing sides $(i, i+1)$ and $(j, j+1)$ (a crossed corner $i$ counts as side $(i, i+1)$), in the order the line hits them. \texttt{extrVertex} returns the hull point with the max projection onto a line.
- **G:** Line $ab$ vs a ccw convex polygon without collinear points: $(-1, -1)$ none, $(i, -1)$ touches corner $i$, $(i, i)$ along side $(i, i+1)$, $(i, j)$ crosses sides $(i, i+1)$ and $(j, j+1)$, in hit order. \texttt{extrVertex}: max projection.
- **L:** ccw, no collinear. $(-1,-1)$ none, $(i,-1)$ corner $i$, $(i,i)$ along side $i$, $(i,j)$ crosses sides $i$, $j$ (side $i$ = $(i, i+1)$). \texttt{extrVertex}: max projection.
- **M:** = L

### `MinkowskiSum.h`

- **Now:** Minkowski sum $\{p + q\}$ of two convex polygons given in ccw order (at least 3 vertices, no three collinear). Returns a convex polygon in ccw order. Two convex polygons $A, B$ intersect iff the origin is in $A + (-B)$, and their distance is the distance from the origin to it. With integer points, cross products must fit in 64 bits.
- **G:** Of two ccw convex polygons ($\ge 3$ vertices, no 3 collinear), ccw. $A$ and $B$ intersect iff $0 \in A + (-B)$; their distance is the distance from 0 to it.
- **L:** ccw, $\ge 3$ vertices, no 3 collinear. $A \cap B \ne \emptyset$ iff $0 \in A + (-B)$.
- **M:** = L

### `ClosestPair.h`

- **Now:** Finds the closest pair of points.
- **G:** Closest pair of $\ge 2$ points.
- **L:** At least 2 points.
- **M:** = L

### `ManhattanMST.h`

- **Now:** Given N points, returns up to 4*N edges, which are guaranteed to contain a minimum spanning tree for the graph with edge weights w(p, q) = |p.x - q.x| + |p.y - q.y|. Edges are in the form (distance, src, dst). Use a standard MST algorithm on the result to find the final MST.
- **G:** $\le 4N$ edges (distance, i, j) that contain a Manhattan MST; run Kruskal on them.
- **L:** $\le 4N$ edges (dist, i, j) containing an MST; run Kruskal.
- **M:** = L

### `RectangleUnion.h`

- **Now:** Area of the union of axis-aligned rectangles. A rectangle is $\{x_1, y_1, x_2, y_2\}$ and covers $[x_1, x_2) \times [y_1, y_2)$.
- **G:** Area of the union; \{x1, y1, x2, y2\} is $[x_1, x_2) \times [y_1, y_2)$.
- **L:** \{x1, y1, x2, y2\}, half-open.
- **M:** = L

### `kdTree.h`

- **Now:** KD-tree (2d, can be extended to 3d)
- **G:** 2D nearest neighbour: \texttt{nearest(p)} = (squared distance, point).
- **L:** \texttt{nearest(p)}: (squared distance, point).
- **M:** = L


## strings

### `KMP.h`

- **Now:** pi[x] computes the length of the longest prefix of s that ends at x, other than s[0...x] itself (abacaba -> 0010123). Can be used to find all occurrences of a string.
- **G:** \texttt{pi}: prefix function (abacaba $\to$ 0010123); \texttt{match}: start positions of \texttt{pat} in \texttt{s}.
- **L:** \texttt{match}: start positions of \texttt{pat} in \texttt{s}.
- **M:** = L

### `Zfunc.h`

- **Now:** z[i] computes the length of the longest common prefix of s[i:] and s, except z[0] = 0. (abacaba -> 0010301)
- **G:** $z[i]$ = lcp of $s[i..]$ and $s$, $z[0] = 0$ (abacaba $\to$ 0010301).
- **L:** $z[0] = 0$.
- **M:** = L

### `Manacher.h`

- **Now:** For each position in a string, computes p[0][i] = half length of longest even palindrome around pos i, p[1][i] = longest odd (half rounded down).
- **G:** \texttt{p[1][i]}: half length (rounded down) of the longest odd palindrome centered at $i$; \texttt{p[0][i]}: of the even one centered before $i$.
- **L:** \texttt{p[1][i]}: odd palindrome at $i$, half length rounded down; \texttt{p[0][i]}: even, centered before $i$.
- **M:** = L

### `PalindromicTree.h`

- **Now:** Palindromic tree (eertree). Node 0 has length $-1$, node 1 is the empty palindrome, every other node is a distinct palindromic substring of the string (so there are \texttt{sz(t) - 2} of them). \texttt{link} is the longest proper palindromic suffix, \texttt{last} the node of the longest palindromic suffix of the current prefix. After \texttt{count()}, \texttt{cnt[v]} is the number of occurrences of palindrome $v$.
- **G:** Eertree. Node 0 has length $-1$, node 1 is the empty palindrome, the rest are the distinct palindromic substrings; \texttt{link}: longest proper palindromic suffix; \texttt{last}: longest palindromic suffix of the prefix. \texttt{cnt[v]} after \texttt{count()}.
- **L:** Node 0: length $-1$, node 1: empty, the rest: distinct palindromes. \texttt{cnt[v]}: occurrences, after \texttt{count()}.
- **M:** Node 0: length $-1$, 1: empty. \texttt{cnt} after \texttt{count()}.

### `MinRotation.h`

- **Now:** Finds the lexicographically smallest rotation of a string.
- **G:** Start of the lexicographically smallest rotation.
- **L:** *(none)*
- **M:** = L

### `SuffixArray.h`

- **Now:** \texttt{sa[i]} is the start of the $i$'th smallest suffix; size $n+1$, \texttt{sa[0] = n}. \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}. The input must not contain nul chars.
- **G:** \texttt{sa} has size $n+1$ (\texttt{sa[0] = n}); \texttt{lcp[i] = lcp(sa[i], sa[i-1])}. No nul chars in the input.
- **L:** = G
- **M:** \texttt{sa[0] = n}; \texttt{lcp[i] = lcp(sa[i], sa[i-1])}. No nul chars.

### `SuffixAutomaton.h`

- **Now:** Minimal DFA accepting exactly the suffixes of the string (so every substring is a path from state 0). State $v$ stands for all substrings that end at the same set of positions, with lengths $(\texttt{len[link[v]]}, \texttt{len[v]}]$. Number of distinct substrings is $\sum_{v \ne 0} \texttt{len[v]} - \texttt{len[link[v]]}$. After \texttt{count()}, \texttt{cnt[v]} is the number of occurrences of the strings of $v$. Append characters with \texttt{extend}.
- **G:** State $v$: substrings with the same end positions, lengths $(\texttt{len[link[v]]}, \texttt{len[v]}]$. Distinct substrings: $\sum_{v \ne 0} \texttt{len[v]} - \texttt{len[link[v]]}$. \texttt{cnt[v]} (occurrences) after \texttt{count()}.
- **L:** State $v$: lengths $(\texttt{len[link[v]]}, \texttt{len[v]}]$. \texttt{cnt[v]}: occurrences, after \texttt{count()}.
- **M:** = L

### `Hashing.h`

- **Now:** Self-explanatory methods for string hashing.
- **G:** Hashing mod $2^{64} - 1$; \texttt{hashInterval(a, b)} hashes $[a, b)$.
- **L:** *(none)*
- **M:** = L

### `AhoCorasick.h`

- **Now:** Multiple pattern matching. \texttt{AhoCorasick ac(patterns)}; the start node is 0. \texttt{find(word)} gives for each position the index of the longest word ending there, or $-1$. \texttt{findAll($-$, word)} lists all words starting at each position, shortest first (up to $N \sqrt N$ without duplicate patterns). Duplicate patterns are allowed, empty ones are not. Longest words starting at each position: reverse all input. Large alphabets: split symbols into chunks, with sentinel bits for symbol boundaries.
- **G:** Patterns non-empty (duplicates allowed); alphabet: \texttt{alpha}, \texttt{first}. \texttt{find(word)}: longest pattern ending at each position ($-1$ if none); \texttt{findAll(pat, word)}: all patterns starting at each position, shortest first.
- **L:** Non-empty patterns; set \texttt{alpha}, \texttt{first}. \texttt{find}: longest pattern ending at each position, $-1$ if none; \texttt{findAll}: all starting at each position.
- **M:** = L
- Time (L and later): `construction takes $O(26N)$, where $N =$ sum of length of patterns. find(x) is $O(N)$, where N = length of x. findAll is $O(NM)$.` → `O(26N) build ($N$ = total pattern length); find $O(|word|)$; findAll $O(NM)$`


## various

### `IntervalMap.h`

- **Now:** Partitions $[lo, hi)$ into intervals that each hold a value. \texttt{assign} overwrites a range and merges equal neighbours. \texttt{each} calls \texttt{f(a, b, T\& val)} on the pieces of $[l, r)$ and lets \texttt{f} modify the values (e.g. range add, range count). With only \texttt{assign}, also replaces a set of disjoint intervals: \texttt{T = bool}, \texttt{m.assign(l, r, 1)} adds, \texttt{0} removes.
- **G:** Partition of $[lo, hi)$ into intervals with values; \texttt{assign} merges equal neighbours; \texttt{each} visits the pieces of $[l, r)$ by reference. A set of disjoint intervals: \texttt{T = bool}.
- **L:** \texttt{each}: \texttt{f(a, b, val\&)} on the pieces of $[l, r)$. Set of intervals: \texttt{T = bool}.
- **M:** = L

### `IntervalCover.h`

- **Now:** Compute indices of smallest set of intervals covering another interval. Intervals should be [inclusive, exclusive). To support [inclusive, inclusive], change (A) to add \texttt{|| R.empty()}. Returns empty set on failure (or if G is empty).
- **G:** Fewest intervals covering $G$. Half-open (closed: add \texttt{|| R.empty()} at (A)). Empty on failure.
- **L:** Half-open (closed: add \texttt{|| R.empty()} at (A)); empty if impossible.
- **M:** = L

### `TernarySearch.h`

- **Now:** Find the smallest i in $[a,b]$ that maximizes $f(i)$, assuming that $f(a) < \dots < f(i) \ge \dots \ge f(b)$. To reverse which of the sides allows non-strict inequalities, change the < marked with (A) to <=, and reverse the loop at (B). To minimize $f$, change it to >, also at (B).
- **G:** Smallest argmax on $[a, b]$ of $f$ strictly increasing, then non-increasing. Strict on the other side: \texttt{<=} at (A) and reverse (B). For the minimum, \texttt{>} at (A) and (B).
- **L:** $f$ strictly increasing, then non-increasing; smallest argmax. Other side strict: \texttt{<=} at (A), reverse (B). Min: \texttt{>}.
- **M:** $f$ strictly up, then non-increasing. Min: \texttt{>} at (A), (B).

### `DivideAndConquerDP.h`

- **Now:** Given $a[i] = \min_{lo(i) \le k < hi(i)}(f(i, k))$ where the (minimal) optimal $k$ increases with $i$, computes $a[i]$ for $i = L..R-1$.
- **G:** $a[i] = \min_{lo(i) \le k < hi(i)} f(i, k)$ for $i \in [L, R)$, when the smallest optimal $k$ is non-decreasing in $i$.
- **L:** = G
- **M:** Smallest optimal $k$ non-decreasing in $i$.
