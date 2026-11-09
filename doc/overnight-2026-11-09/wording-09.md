# Patch 09: shorter descriptions, old vs new

Only the *Description* text changes (Usage, Time and code are untouched). Figures stay where they are.
Numbers are characters of the source text (so TeX markup counts); the PDF saves about 2 lines per file.

Total: 8325 → 5459 characters over 17 files.

**What is dropped or changed in meaning** (everything else is the same facts in fewer words):
- Geometry (`SegmentIntersection`, `lineIntersection`, `lineDistance`, `sideOf`): "if using int or long long" becomes just "(overflow)", and
  "P is supposed to be Point<T> where T is e.g. double or long long" is dropped from `sideOf`. `lineIntersection` now says
  "parallel" / "same line" for the 0 / -1 cases.
- `RadixConversion`: the example "send n numbers below a in messages below b" and the sentence "a bijection between all finite
  sequences" are dropped (the k-th-to-k-th rule says the same).
- `HLD`: "Code does additive modifications and max queries" is gone (the default block does that; the text now points to `LazySeg`),
  and "path from any leaf to the root contains at most log(n) light edges" becomes "$O(\log n)$ light edges".
- `BiconnectedComponents`: the definition via "two internally disjoint paths" becomes "any two of its nodes lie on a common cycle".
- `NumberTheoreticTransform`, `FastFourierTransform`: same content, reordered so `conv` comes right after `ntt` / `fft`.

## `combinatorial/RadixConversion.h`  (1098 → 769 chars)

**Now:** Converts a sequence of digits in $[0, a)$ to a sequence of digits in $[0, b)$, with $a, b \ge 2$ (below $2^{31}$), most significant first. It is a bijection between all finite sequences: the empty one maps to the empty one, and the $k$-th sequence in (length, lexicographic) order in base $a$ goes to the $k$-th in base $b$. So \texttt{radixconv(radixconv(x, a, b), b, a) == x} always, with no length or leading zeros to remember, and the result has about $|x| \log_b a$ digits (e.g. to send $n$ numbers below $a$ in messages below $b$). \texttt{radixToPerm(x, a)} is the same with permutations of $0, \ldots, n-1$ as the target: a bijection between all digit sequences and all permutations (the size comes out of the data, e.g. 2000 binary digits give 296 elements), (length, lexicographic) order going to (size, lexicographic) order; \texttt{permToRadix(p, a)} is the inverse ($y$ is the result; it also takes $O(|y|^2)$). For a fixed size use \texttt{intToPerm}, or \texttt{radixToPerm} on the digits of $r + 0! + 1! + \dots + (n-1)!$ in base $2^{31}-1$ (one digit for $n \le 12$, two up to 20).

**Proposed:** Bijective base conversion: digits in $[0, a)$ to digits in $[0, b)$ ($2 \le a, b < 2^{31}$), most significant first. The $k$-th sequence in (length, lexicographic) order in base $a$ maps to the $k$-th in base $b$ (empty to empty), so \texttt{radixconv(radixconv(x, a, b), b, a) == x} with no length or leading zeros to store; the result has about $|x| \log_b a$ digits. \texttt{radixToPerm(x, a)} does the same onto all permutations of $0, \ldots, n-1$ ($n$ comes from the data: 2000 bits give 296 elements), in (size, lexicographic) order; \texttt{permToRadix(p, a)} is its inverse ($O(|y|^2)$, $y$ the result). Fixed size: \texttt{intToPerm}, or \texttt{radixToPerm} on the base $2^{31}-1$ digits of $r + 0! + \dots + (n-1)!$ (one digit for $n \le 12$, two up to 20).

## `geometry/SegmentIntersection.h`  (602 → 323 chars)

**Now:** If a unique intersection point between the line segments going from s1 to e1 and from s2 to e2 exists then it is returned. If no intersection point exists an empty vector is returned. If infinitely many exist a vector with 2 elements is returned, containing the endpoints of the common line segment. The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates. Products of three coordinates are used in intermediate steps so watch out for overflow if using int or long long.

**Proposed:** Intersection of segments s1-e1 and s2-e2: one point, none (empty vector), or the two endpoints of the common segment if there are infinitely many. With Point<ll> the point is wrong if it is not integral. Uses products of three coordinates (overflow).

## `geometry/lineIntersection.h`  (513 → 315 chars)

**Now:** If a unique intersection point of the lines going through s1,e1 and s2,e2 exists \{1, point\} is returned. If no intersection point exists \{0, (0,0)\} is returned and if infinitely many exists \{-1, (0,0)\} is returned. The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates. Products of three coordinates are used in intermediate steps so watch out for overflow if using int or ll.

**Proposed:** Intersection of the lines through s1,e1 and s2,e2: \{1, point\} if unique, \{0, (0,0)\} if parallel, \{-1, (0,0)\} if they are the same line. With Point<ll> the point is wrong if it is not integral. Uses products of three coordinates (overflow).

## `geometry/lineDistance.h`  (399 → 251 chars)

**Now:** Returns the signed distance between point p and the line containing points a and b. Positive value on left side and negative on right as seen from a towards b. a==b gives nan. P is supposed to be Point<T> where T is e.g. double or long long. It uses products in intermediate steps so watch out for overflow if using int or long long.

**Proposed:** Signed distance from p to the line through a and b, positive on the left as seen from a towards b; a==b gives nan. T is double or long long; uses products of two coordinates (overflow).

## `geometry/sideOf.h`  (354 → 167 chars)

**Now:** Returns where $p$ is as seen from $s$ towards $e$. 1/0/-1 $\Leftrightarrow$ left/on line/right. If the optional argument $eps$ is given 0 is returned if $p$ is within distance $eps$ from the line. P is supposed to be Point<T> where T is e.g. double or long long. It uses products in intermediate steps so watch out for overflow if using int or long long.

**Proposed:** 1/0/-1 if $p$ is left of/on/right of the line from $s$ towards $e$. With $eps$, 0 if $p$ is within distance $eps$ of the line. Uses products of coordinates (overflow).

## `geometry/LineHullIntersection.h`  (642 → 401 chars)

**Now:** Line-convex polygon intersection. The polygon must be ccw and have no collinear points. lineHull(line, poly) returns a pair describing the intersection of a line with the polygon: \begin{itemize*} \item $(-1, -1)$ if no collision, \item $(i, -1)$ if touching the corner $i$, \item $(i, i)$ if along side $(i, i+1)$, \item $(i, j)$ if crossing sides $(i, i+1)$ and $(j, j+1)$. \end{itemize*} In the last case, if a corner $i$ is crossed, this is treated as happening on side $(i, i+1)$. The points are returned in the same order as the line hits the polygon. \texttt{extrVertex} returns the point of a hull with the max projection onto a line.

**Proposed:** Line vs convex polygon (ccw, no collinear points). \texttt{lineHull(line, poly)} returns $(-1, -1)$ if no collision, $(i, -1)$ if touching corner $i$, $(i, i)$ if along side $(i, i+1)$, $(i, j)$ if crossing sides $(i, i+1)$ and $(j, j+1)$ (a crossed corner $i$ counts as side $(i, i+1)$), in the order the line hits them. \texttt{extrVertex} returns the hull point with the max projection onto a line.

## `strings/AhoCorasick.h`  (600 → 511 chars)

**Now:** Aho-Corasick automaton, used for multiple pattern matching. Initialize with AhoCorasick ac(patterns); the automaton start node will be at index 0. find(word) returns for each position the index of the longest word that ends there, or -1 if none. findAll($-$, word) finds all words (up to $N \sqrt N$ many if no duplicate patterns) that start at each position (shortest first). Duplicate patterns are allowed; empty patterns are not. To find the longest words that start at each position, reverse all input. For large alphabets, split each symbol into chunks, with sentinel bits for symbol boundaries.

**Proposed:** Multiple pattern matching. \texttt{AhoCorasick ac(patterns)}; the start node is 0. \texttt{find(word)} gives for each position the index of the longest word ending there, or $-1$. \texttt{findAll($-$, word)} lists all words starting at each position, shortest first (up to $N \sqrt N$ without duplicate patterns). Duplicate patterns are allowed, empty ones are not. Longest words starting at each position: reverse all input. Large alphabets: split symbols into chunks, with sentinel bits for symbol boundaries.

## `graph/HLD.h`  (594 → 386 chars)

**Now:** Decomposes a tree into vertex disjoint heavy paths and light edges such that the path from any leaf to the root contains at most log(n) light edges. Code does additive modifications and max queries, but can support commutative segtree modifications/queries on paths and subtrees. Uses LazySeg (edit its block for other operations); modifications take its tag \texttt{L}, queries return its value \texttt{S}. Takes as input the full adjacency list. VALS\_EDGES being true means that values are stored in the edges, as opposed to the nodes. All values initialized to \texttt{S()}. Root must be 0.

**Proposed:** Heavy-light decomposition: every path to the root has $O(\log n)$ light edges. Path and subtree updates and queries go to a \texttt{LazySeg} (edit its block for other operations): updates take its tag \texttt{L}, queries return its value \texttt{S}, all values start as \texttt{S()}. Takes the full adjacency list, root 0. \texttt{VALS\_EDGES}: values on the edges instead of the nodes.

## `geometry/CircleTangents.h`  (496 → 343 chars)

**Now:** Finds the external tangents of two circles, or internal if r2 is negated. Can return 0, 1, or 2 tangents -- 0 if one circle contains the other (or overlaps it, in the internal case, or if the circles are the same); 1 if the circles are tangent to each other (in which case .first = .second and the tangent line is perpendicular to the line between the centers). .first and .second give the tangency points at circle 1 and 2 respectively. To find the tangents of a circle with a point set r2 to 0.

**Proposed:** External tangents of two circles (internal ones if r2 is negated). Returns 0 tangents if one circle contains the other (internal case: also if they overlap; also if equal), 1 if they touch (.first = .second, perpendicular to the center line), else 2. .first and .second are the tangency points on circle 1 and 2. Tangents from a point: r2 = 0.

## `numerical/NumberTheoreticTransform.h`  (472 → 361 chars)

**Now:** ntt(a) computes $\hat f(k) = \sum_x a[x] g^{xk}$ for all $k$, where $g=\text{root}^{(mod-1)/N}$. N must be a power of 2. Useful for convolution modulo specific nice primes of the form $2^a b+1$, where the convolution result has size at most $2^a$. For arbitrary modulo, see FFTMod. \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$. For manual convolution: NTT the inputs, multiply pointwise, divide by n, reverse(start+1, end), NTT back. Inputs must be in [0, mod).

**Proposed:** \texttt{ntt(a)} computes $\hat f(k) = \sum_x a[x] g^{xk}$ for all $k$, $g=\text{root}^{(mod-1)/N}$, $N$ a power of 2. \texttt{conv(a, b) = c} with $c[x] = \sum a[i]b[x-i]$, modulo primes $2^a b+1$ with result size at most $2^a$ (any modulus: FFTMod). By hand: NTT the inputs, multiply pointwise, divide by n, reverse(start+1, end), NTT back. Inputs in [0, mod).

## `numerical/FastFourierTransform.h`  (469 → 399 chars)

**Now:** fft(a) computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for all $k$. N must be a power of 2. Useful for convolution: \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$. For convolution of complex numbers or more than two vectors: FFT, multiply pointwise, divide by n, reverse(start+1, end), FFT back. Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$ (in practice $10^{16}$; higher for random inputs). Otherwise, use NTT/FFTMod.

**Proposed:** \texttt{fft(a)} computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for all $k$, $N$ a power of 2. \texttt{conv(a, b) = c} with $c[x] = \sum a[i]b[x-i]$. Complex or more than two vectors: FFT, multiply pointwise, divide by n, reverse(start+1, end), FFT back. Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$ (in practice $10^{16}$, more if random); else NTT/FFTMod.

## `strings/SuffixArray.h`  (401 → 188 chars)

**Now:** Builds suffix array for a string. \texttt{sa[i]} is the starting index of the suffix which is $i$'th in the sorted suffix array. The returned vector is of size $n+1$, and \texttt{sa[0] = n}. The \texttt{lcp} array contains longest common prefixes for neighbouring strings in the suffix array: \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}. The input string must not contain any nul chars.

**Proposed:** \texttt{sa[i]} is the start of the $i$'th smallest suffix; size $n+1$, \texttt{sa[0] = n}. \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}. The input must not contain nul chars.

## `graph/WeightedMatching.h`  (367 → 202 chars)

**Now:** Given a weighted bipartite graph, matches every node on the left with a node on the right such that no nodes are in two matchings and the sum of the edge weights is minimal. Takes cost[N][M], where cost[i][j] = cost for L[i] to be matched with R[j], and returns (min cost, match), where L[i] is matched with R[match[i]]. Negate costs for max cost. Requires $N \le M$.

**Proposed:** Min-cost bipartite matching that matches every left node, $N \le M$. Takes cost[N][M] (cost[i][j]: L[i] with R[j]), returns (min cost, match) with L[i] matched to R[match[i]]. Negate costs for max cost.

## `graph/BiconnectedComponents.h`  (353 → 172 chars)

**Now:** Finds all biconnected components in an undirected graph, and runs a callback for the edges in each. In a biconnected component there are at least two internally disjoint paths between any two nodes (a cycle exists through them). Note that a node can be in several components. An edge which is not in a component is a bridge, i.e., not part of any cycle.

**Proposed:** Runs the callback on the edges of each biconnected component (any two of its nodes lie on a common cycle). A node can be in several components; an edge in none is a bridge.

## `graph/EulerWalk.h`  (352 → 268 chars)

**Now:** Eulerian undirected/directed path/cycle algorithm. Input should be a vector of (dest, global edge index), where for undirected graphs, forward/backward edges have the same index. Returns a list of nodes in the Eulerian path/cycle with src at both start and end, or empty list if no cycle/path exists. To get edge indices back, add .second to s and ret.

**Proposed:** Euler path/cycle, undirected or directed. Input: lists of (dest, global edge index); both directions of an undirected edge share the index. Returns the nodes of the walk (src at both ends for a cycle), or empty if there is none. Edge indices: add .second to s and ret.

## `graph/HopcroftKarp.h`  (302 → 172 chars)

**Now:** Fast bipartite matching algorithm. Graph $g$ should be a list of neighbors of the left partition, and $r$ should be a vector full of $-1$'s of the same size as the right partition. Returns the size of the matching. $r[i]$ will be the match for vertex $i$ on the right side, or $-1$ if it's not matched.

**Proposed:** Bipartite matching. $g$: neighbours of each left vertex; $r$: all $-1$, size of the right side. Returns the matching size; $r[i]$ is the match of right vertex $i$, or $-1$.

## `data-structures/MoQueries.h`  (311 → 231 chars)

**Now:** Answer interval or tree path queries by finding an approximate TSP through the queries, and moving from one query to the next by adding/removing points at the ends. If values are on tree edges, change \texttt{step} to add/remove the edge $(a, c)$ and remove the initial \texttt{add} call (but keep \texttt{in}).

**Proposed:** Interval or tree path queries: visit the queries along an approximate TSP, adding/removing points at the ends. Values on tree edges: \texttt{step} adds/removes the edge $(a, c)$ and the initial \texttt{add} goes (keep \texttt{in}).
