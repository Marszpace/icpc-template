# Proposed shorter descriptions (same facts). Run inside a copy of the repo.
import re, sys
NEW = {
'combinatorial/RadixConversion.h': r"""Bijective base conversion: digits in $[0, a)$ to digits in $[0, b)$ ($2 \le a, b < 2^{31}$), most significant first.
The $k$-th sequence in (length, lexicographic) order in base $a$ maps to the $k$-th in base $b$ (empty to empty),
so \texttt{radixconv(radixconv(x, a, b), b, a) == x} with no length or leading zeros to store; the result has about $|x| \log_b a$ digits.
\texttt{radixToPerm(x, a)} does the same onto all permutations of $0, \ldots, n-1$ ($n$ comes from the data: 2000 bits give 296 elements),
in (size, lexicographic) order; \texttt{permToRadix(p, a)} is its inverse ($O(|y|^2)$, $y$ the result).
Fixed size: \texttt{intToPerm}, or \texttt{radixToPerm} on the base $2^{31}-1$ digits of $r + 0! + \dots + (n-1)!$ (one digit for $n \le 12$, two up to 20).""",
'geometry/SegmentIntersection.h': r"""\\
\begin{minipage}{75mm}
Intersection of segments s1-e1 and s2-e2: one point, none (empty vector),
or the two endpoints of the common segment if there are infinitely many.
With Point<ll> the point is wrong if it is not integral.
Uses products of three coordinates (overflow).
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentIntersection}
\end{minipage}""",
'geometry/lineIntersection.h': r"""\\
\begin{minipage}{75mm}
Intersection of the lines through s1,e1 and s2,e2: \{1, point\} if unique,
\{0, (0,0)\} if parallel, \{-1, (0,0)\} if they are the same line.
With Point<ll> the point is wrong if it is not integral.
Uses products of three coordinates (overflow).
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineIntersection}
\end{minipage}""",
'geometry/lineDistance.h': r"""\\
\begin{minipage}{75mm}
Signed distance from p to the line through a and b, positive on the left
as seen from a towards b; a==b gives nan. T is double or long long;
uses products of two coordinates (overflow).
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}""",
'geometry/sideOf.h': r"""1/0/-1 if $p$ is left of/on/right of the line from $s$ towards $e$.
With $eps$, 0 if $p$ is within distance $eps$ of the line. Uses products of coordinates (overflow).""",
'geometry/LineHullIntersection.h': r"""Line vs convex polygon (ccw, no collinear points). \texttt{lineHull(line, poly)} returns
$(-1, -1)$ if no collision, $(i, -1)$ if touching corner $i$, $(i, i)$ if along side $(i, i+1)$,
$(i, j)$ if crossing sides $(i, i+1)$ and $(j, j+1)$ (a crossed corner $i$ counts as side $(i, i+1)$), in the order the line hits them.
\texttt{extrVertex} returns the hull point with the max projection onto a line.""",
'strings/AhoCorasick.h': r"""Multiple pattern matching. \texttt{AhoCorasick ac(patterns)}; the start node is 0.
\texttt{find(word)} gives for each position the index of the longest word ending there, or $-1$.
\texttt{findAll($-$, word)} lists all words starting at each position, shortest first (up to $N \sqrt N$ without duplicate patterns).
Duplicate patterns are allowed, empty ones are not. Longest words starting at each position: reverse all input.
Large alphabets: split symbols into chunks, with sentinel bits for symbol boundaries.""",
'graph/HLD.h': r"""Heavy-light decomposition: every path to the root has $O(\log n)$ light edges.
Path and subtree updates and queries go to a \texttt{LazySeg} (edit its block for other operations):
updates take its tag \texttt{L}, queries return its value \texttt{S}, all values start as \texttt{S()}.
Takes the full adjacency list, root 0. \texttt{VALS\_EDGES}: values on the edges instead of the nodes.""",
'geometry/CircleTangents.h': r"""External tangents of two circles (internal ones if r2 is negated). Returns 0 tangents if one circle contains the other
(internal case: also if they overlap; also if equal), 1 if they touch (.first = .second, perpendicular to the center line), else 2.
.first and .second are the tangency points on circle 1 and 2. Tangents from a point: r2 = 0.""",
'numerical/NumberTheoreticTransform.h': r"""\texttt{ntt(a)} computes $\hat f(k) = \sum_x a[x] g^{xk}$ for all $k$, $g=\text{root}^{(mod-1)/N}$, $N$ a power of 2.
\texttt{conv(a, b) = c} with $c[x] = \sum a[i]b[x-i]$, modulo primes $2^a b+1$ with result size at most $2^a$ (any modulus: FFTMod).
By hand: NTT the inputs, multiply pointwise, divide by n, reverse(start+1, end), NTT back. Inputs in [0, mod).""",
'numerical/FastFourierTransform.h': r"""\texttt{fft(a)} computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for all $k$, $N$ a power of 2.
\texttt{conv(a, b) = c} with $c[x] = \sum a[i]b[x-i]$. Complex or more than two vectors: FFT, multiply pointwise, divide by n, reverse(start+1, end), FFT back.
Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$ (in practice $10^{16}$, more if random); else NTT/FFTMod.""",
'strings/SuffixArray.h': r"""\texttt{sa[i]} is the start of the $i$'th smallest suffix; size $n+1$, \texttt{sa[0] = n}.
\texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}. The input must not contain nul chars.""",
'graph/WeightedMatching.h': r"""Min-cost bipartite matching that matches every left node, $N \le M$. Takes cost[N][M] (cost[i][j]: L[i] with R[j]),
returns (min cost, match) with L[i] matched to R[match[i]]. Negate costs for max cost.""",
'graph/BiconnectedComponents.h': r"""Runs the callback on the edges of each biconnected component (any two of its nodes lie on a common cycle).
A node can be in several components; an edge in none is a bridge.""",
'graph/EulerWalk.h': r"""Euler path/cycle, undirected or directed. Input: lists of (dest, global edge index); both directions of an undirected edge share the index.
Returns the nodes of the walk (src at both ends for a cycle), or empty if there is none. Edge indices: add .second to s and ret.""",
'graph/HopcroftKarp.h': r"""Bipartite matching. $g$: neighbours of each left vertex; $r$: all $-1$, size of the right side.
Returns the matching size; $r[i]$ is the match of right vertex $i$, or $-1$.""",
'data-structures/MoQueries.h': r"""Interval or tree path queries: visit the queries along an approximate TSP, adding/removing points at the ends.
Values on tree edges: \texttt{step} adds/removes the edge $(a, c)$ and the initial \texttt{add} goes (keep \texttt{in}).""",
}
for f, new in NEW.items():
    p = 'content/' + f
    s = open(p).read()
    lines = s.split('\n')
    i = next(k for k, l in enumerate(lines) if re.match(r'\s*\*\s*Description:', l))
    j = i + 1
    while not re.match(r'\s*\*\s*(Usage|Time|Status|Memory|Details):', lines[j]) and not lines[j].strip().startswith('*/'):
        j += 1
    nl = new.split('\n')
    out = [' * Description: ' + nl[0]] + [(l if l.startswith('\\') else ' * ' + l) for l in nl[1:]]
    lines[i:j] = out
    open(p, 'w').write('\n'.join(lines))
    print('ok', f)
