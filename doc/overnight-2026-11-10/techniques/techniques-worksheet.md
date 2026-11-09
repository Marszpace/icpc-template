# Item 20: techniques worksheet

Rule (team, 2026-11-09): keep what is hard to see from the statement but clicks once someone names it; drop what is already in the template and what is trivial for us.

Marks: **A** = keep, **B** = maybe (borderline trivial, or rare), **A*** = essential (the tightest list), **C** = wild (niche but advanced; the team chose to include them, 2026-11-10). Levels: essential (A*), core (A), all (A, B), wild (A, B, C); each as names only or with a hint (same number of lines).

Totals: 73 A, 44 B, 63 C, in 15 groups.

## The proposed list

### Reformulate

| | Technique | Hint (printed in the hinted versions) |
|---|---|---|
| A* | Contribution technique | sum what each element adds |
| A | Fix one end, sweep the other | or fix the max / middle |
| A* | Reverse the process | deletions -> insertions, time backwards |
| A* | Invariants, monovariants | sum, parity, xor, mod k, sorted |
| A* | Differences / prefix sums | neighbour ops become simple there |
| A* | Manhattan <-> Chebyshev | (x + y, x - y) turns L1 into L-inf |
| A* | Bound the answer | often <= 2, <= log n or <= sqrt n: try each |
| B | Binary search the answer | when checking a value is easy |
| B | Complement counting | count the bad ones and subtract |
| A* | Swap state and value | dp[value] = min cost, values small |
| A* | Coloring argument | checkerboard or mod k colours, parity |
| A | Pigeonhole | n + 1 prefix sums mod n: a block divisible by n |
| A* | Sqrt threshold | heavy (> sqrt) vs light items, two methods |
| A* | Few distinct sizes | sum of sizes = n: O(sqrt n) distinct |
| A* | Layered / state graph | node = (vertex, extra state), then BFS |
| A | Functional graph | out-degree 1: rho shape, cycle + trees |
| A* | Bit by bit from the top | greedy on xor / and / or optimum |
| B | Lexicographic minimum | fix positions in order, check feasible |
| C | Balanced ternary | digits -1, 0, 1: balance-scale weights |

### Counting

| | Technique | Hint (printed in the hinted versions) |
|---|---|---|
| A* | Linearity of expectation | sum of P(indicator), even dependent |
| A | E[X] = sum P(X >= k) | for X >= 0 integer, e.g. E[max] |
| A* | Reflection principle | bad paths = paths to the mirrored end |
| B | Inclusion-exclusion | sum over subsets of violated rules |
| A | Kummer | v_p(C(n, k)) = carries of k + (n-k) in base p |
| B | Vandermonde | sum C(a, i) C(b, k-i) = C(a+b, k) |
| B | Stars and bars | C(n + k - 1, k - 1) ways to split n into k |
| A* | Hall | match all of L iff |N(S)| >= |S| for all S |
| B | Erdos-Szekeres | n^2 + 1 terms: monotone run of n + 1 |
| B | Coupon collector | n H_n expected draws |
| C | Graph enumeration | connected labeled graphs: log of the EGF |
| C | Entringer / zigzag | alternating permutations, boustrophedon |
| C | Young tableaux | hook length formula; RSK and LIS |
| C | Probability bounds | Markov, Chebyshev, Chernoff, union bound |

### Greedy

| | Technique | Hint (printed in the hinted versions) |
|---|---|---|
| A* | Exchange argument | sort by the pairwise comparison a < b |
| A* | Regret greedy | heap of choices you can still undo |
| A | Deadline scheduling | by deadline, heap; drop worst if late |
| B | Huffman merging | merge the two smallest, cost = merges |
| A | Matroid | greedy is optimal; two of them: intersection |

### Dynamic programming

| | Technique | Hint (printed in the hinted versions) |
|---|---|---|
| A* | Aliens trick (WQS) | exactly k, convex in k: penalty lambda |
| A* | Knuth optimization | opt[i][j-1] <= opt[i][j] <= opt[i+1][j] |
| A | Monotone queue DP | min over a sliding window of k |
| A* | Digit DP | count x <= N: (pos, tight, state) |
| A* | Broken profile DP | tilings of n x m, n small: bitmask row |
| A* | Rerooting | down pass, then up pass with prefix/suffix |
| A | Tree knapsack | merging by subtree sizes is O(n^2) total |
| A* | DP over an automaton | state = (position, KMP / AC node) |
| A | Dynamic DP | segment tree of (max,+) matrices, updates |
| A* | Steiner tree | dp[mask][v]: merge submasks, then Dijkstra |
| B | Bounded knapsack | binary splitting, or monotone queue |
| B | Bitonic tour | dp[i][j]: two paths ending at i and j |
| B | Exchange DP order | iterate over the smallest dimension |
| B | Expected value DP | backwards from the end; cycles: equations |
| C | Garsia-Wachs | optimal alphabetic tree (merge cost) |

### Graphs

| | Technique | Hint (printed in the hinted versions) |
|---|---|---|
| A* | Difference constraints | x_j - x_i <= w: edge i -> j, Bellman |
| A* | Residue Dijkstra | reachable sums: dist[r mod a_min] |
| A* | Min-plus matrix power | shortest walk with exactly k edges |
| A* | Kruskal reconstruction tree | path max edge, components <= w |
| A | MST cycle property | heaviest cycle edge is never needed |
| A | Boruvka | MST of an implicit graph (xor, geometry) |
| A* | Complement BFS | keep a set of unvisited, scan it |
| A | Triangles in O(m sqrt m) | orient edges low -> high degree |
| A | Planar bounds | E <= 3V - 6; V - E + F = 2 |
| A* | Grid is bipartite | (i + j) parity: matching / flow / cover |
| A | Expected hitting times | linear system; on a tree, DP |
| A | Tree isomorphism | canonical form or hash of sorted children |
| B | Dominator tree | vertices every s -> v path passes |
| B | Stable matching | Gale-Shapley proposals, O(n^2) |
| B | 0-1 BFS | deque: weight 0 front, weight 1 back |
| B | Min mean cycle | Karp O(VE), or binary search + Bellman |
| B | Shortest cycle | BFS from each vertex, O(VE) |
| B | K-th shortest path | Eppstein; or A* with exact heuristic |
| B | Euler tour flattening | subtree = a range of dfs times |
| B | Long-path decomposition | depth DP in O(n) total |
| C | Edge coloring | bipartite: max degree colours; else <= D + 1 |
| C | Vertex coloring | k colours: 2^n incl.-excl. over indep. sets |
| C | Chordal graphs | perfect elimination order (max card. search) |
| C | Max-weight general matching | weighted blossom, O(n^3) |
| C | Min diameter spanning tree | absolute centre of the graph |
| C | Dynamic graphs | extra book-keeping per change |
| C | Lovasz toggle |  |

### Data structures

| | Technique | Hint (printed in the hinted versions) |
|---|---|---|
| A* | Queue from two stacks | sliding min / gcd without undo |
| A* | Cartesian tree | recursion on the minimum; O(n) with stack |
| A | Nearest smaller values | monotone stack; histogram rectangles |
| A | Segment tree merging | merge dynamic trees small to large |
| A | Rebuild every sqrt(Q) | buffer updates, recompute periodically |
| A* | Binary trie | max xor pair, count xor <= k |
| A* | Zobrist / xor hashing | random 64-bit per item: set equality |
| B | Merge sort tree / wavelet | k-th or count in a range, static |
| B | Small to large | each item moves O(log n) times |

### Advanced data structures

| | Technique | Hint (printed in the hinted versions) |
|---|---|---|
| C | Splay tree | amortized log; accessed node goes to the root |
| C | Balanced BSTs | AVL, red-black, AA, SBT, scapegoat |
| C | WBLT | weight-balanced leafy tree: merge / split |
| C | Skip list | random levels, expected O(log n) |
| C | Pairing / leftist heap | mergeable heaps (leftist: rank) |
| C | Persistent heap | leftist heap with path copying (k-th path) |
| C | Persistent balanced tree | path-copied treap (persistent rope) |
| C | Persistent block array | sqrt blocks, copy on write |
| C | Finger tree | O(1) at both ends, log split / concat |
| C | Disjoint sparse table | (cat tree) O(1) query, any assoc. op |
| C | Sqrt tree | O(1) range query, O(n log log n) build |
| C | Kinetic segment tree | max of a_i + t b_i as t only increases |
| C | Euler tour tree | dynamic forest with subtree aggregates |
| C | Top tree | dynamic trees, path and subtree ops |
| C | Global balanced binary tree | HLD paths as weighted BSTs |
| C | Block list | list of sqrt-size blocks, split / merge |
| C | Tree blocking | cut a tree into O(sqrt n) clusters |
| C | Tree in tree | segtree of treaps / BIT of value segtrees |
| C | PQ tree | orders with consecutive-ones constraints |
| C | Quadtree | 2D subdivision (usually kd-tree is better) |

### Offline

| | Technique | Hint (printed in the hinted versions) |
|---|---|---|
| A* | CDQ divide and conquer | left half updates answer right half |
| A* | Parallel binary search | all queries binary search together |
| A* | Sort queries by right end | last occurrence: distinct counts |
| A | D&C on the array | count pairs that cross the middle |
| A* | Discrete 2nd derivatives | add arithmetic progressions in O(1) |
| B | Mo with updates | time as 3rd axis, blocks n^(2/3) |
| C | Rollback Mo | only insertions: roll back to block start |
| C | 2D Mo | Mo over two dimensions / grids |
| C | Secondary offline Mo | answer the pointer moves offline again |
| C | Mo with bitset | bitset as the state of the window |
| C | Interesting points in N log N |  |

### Number theory

| | Technique | Hint (printed in the hinted versions) |
|---|---|---|
| A* | Frobenius number | ab - a - b largest non-sum, gcd = 1 |
| A | Stern-Brocot | best rational approximation, binary search |
| B | gcd of powers | gcd(a^m-1, a^n-1) = a^gcd(m,n)-1; same for F |
| B | Wilson | (p - 1)! = -1 mod p |
| B | Sum of two squares | p = 1 mod 4 primes; Gaussian integers |
| B | Vieta jumping | (x, y) -> (k y - x, y), descent |
| B | Hensel lifting | root mod p -> mod p^k |
| B | Pell equation | x^2 - d y^2 = 1 from continued fractions |
| C | Min_25 sieve | prefix sums of multiplicative f |
| C | Powerful number sieve | f = g * h, h only on powerful numbers |
| C | Zhou's sieve | multiplicative prefix sums (like Min_25) |
| C | k-th roots mod p | via primitive root + discrete log |
| C | Quadratic fields | arithmetic in Z[sqrt d] (closed forms) |
| C | Quadratic reciprocity | Legendre symbols of odd primes p, q |

### Polynomials and algebra

| | Technique | Hint (printed in the hinted versions) |
|---|---|---|
| C | Multipoint evaluation | subproduct tree, O(n log^2 n) |
| C | Polynomial shift | p(x + c) with one convolution |
| C | Chirp Z-transform | evaluate at a geometric sequence |
| C | Composition | f(g(x)); compositional inverse |
| C | Lagrange inversion | g = f^-1: [x^n] g = [x^(n-1)] (x/f)^n / n |
| C | Characteristic polynomial | Hessenberg O(n^3); Cayley-Hamilton |
| C | Diagonalization / Jordan | A^k from eigenvalues |
| C | Linear programming | simplex; duality; zero-sum games |
| C | Schreier-Sims | permutation group order and membership |

### Geometry

| | Technique | Hint (printed in the hinted versions) |
|---|---|---|
| A* | Inversion | circles through the centre become lines |
| B | Point-line duality | (a, b) <-> y = ax - b, hull <-> envelope |
| B | Golden section search | unimodal real f, 1 eval per step |
| B | Area by Green | union of circles / arcs: sum over arcs |
| C | Segment intersections | Bentley-Ottmann, O((n + k) log n) |
| C | Triangulation | ear clipping; Delaunay |
| C | 3D basics | cross products, planes, hull |

### Strings

| | Technique | Hint (printed in the hinted versions) |
|---|---|---|
| A* | Period from KMP | p = n - pi[n-1]; full repeat iff p | n |
| A | Next-occurrence table | nxt[i][c]: subsequence checks / counts |
| B | Lyndon / Duval | factorization, min rotation, O(n) |
| B | Hash + binary search | lcp / comparisons of substrings |
| C | Main-Lorentz | all tandem repeats in O(n log n) |
| C | Generalized SAM | one automaton for many strings |
| C | SA-IS | linear-time suffix array |
| C | Suffix balanced tree | online suffix order, add at the front |
| C | Boyer-Moore | bad-character skips, sublinear on average |

### Games

| | Technique | Hint (printed in the hinted versions) |
|---|---|---|
| A* | Sprague-Grundy | g = mex of options; sum: xor |
| A | Nim | first player wins iff xor != 0 |
| A* | Games with cycles | retrograde BFS from terminal states |
| A* | Token on a graph | first wins iff start in every max matching |
| A | Mirror strategy | copy the opponent symmetrically |
| B | Staircase nim | only odd steps matter |
| C | Partizan games | surreal numbers, Hackenbush |
| C | Alpha-beta pruning | minimax with cut-offs |

### Randomization and search

| | Technique | Hint (printed in the hinted versions) |
|---|---|---|
| A* | Meet in the middle | n ~ 40: two halves, sort and combine |
| A* | Bitset speedup | n^3 / 64, subset sums, reachability |
| A* | Random sampling | property of >= half: try ~30 random picks |
| B | Random shuffle | expected bounds (incremental, treap order) |
| B | Simulated annealing | hill climbing that accepts worse moves |
| B | IDA* / A* | admissible heuristic, iterative deepening |
| B | Exact cover | dancing links (sudoku, pentomino) |

### Misc

| | Technique | Hint (printed in the hinted versions) |
|---|---|---|
| A* | Fractional programming | max sum a / sum b: sum(a - x b) >= 0? |
| A | Largest empty rectangle | histogram per row + monotone stack |
| B | Josephus | J(n) = (J(n - 1) + k) mod n |
| B | Majority vote | Boyer-Moore counter; mergeable in a segtree |
| B | Gray code | i ^ (i >> 1): neighbours differ in 1 bit |
| B | Kahan summation | compensated sum for floating error |

## Current techniques.txt (159 lines), line by line

Kept 18, maybe 12, wild 10, in the template 59, trivial 41, left out 0, other niche 0 (headings 19).

| Line | Verdict | |
|---|---|---|
| **Recursion** | | |
| **Divide and conquer** | | |
| Finding interesting points in N log N | wild (C) | as "Interesting points in N log N" |
| **Algorithm analysis** | | |
| Master theorem | basic / trivial |  |
| Amortized time complexity | basic / trivial |  |
| **Greedy algorithm** | | |
| Scheduling | kept | as "Deadline scheduling" |
| Max contiguous subvector sum | basic / trivial |  |
| Invariants | kept | as "Invariants, monovariants" |
| Huffman encoding | maybe | as "Huffman merging" |
| **Graph theory** | | |
| Dynamic graphs (extra book-keeping) | wild (C) | as "Dynamic graphs" |
| Breadth first search | basic / trivial |  |
| Depth first search | basic / trivial |  |
| Normal trees / DFS trees | basic / trivial |  |
| Dijkstra's algorithm | basic / trivial |  |
| MST: Prim's algorithm | basic / trivial |  |
| Bellman-Ford | basic / trivial |  |
| Konig's theorem and vertex cover | in the template |  |
| Min-cost max flow | in the template |  |
| Lovasz toggle | wild (C) |  |
| Matrix tree theorem | in the template |  |
| Maximal matching, general graphs | in the template |  |
| Hopcroft-Karp | in the template |  |
| Hall's marriage theorem | kept | as "Hall" |
| Graphical sequences | in the template |  |
| Floyd-Warshall | basic / trivial |  |
| Euler cycles | in the template |  |
| Flow networks | in the template |  |
| Augmenting paths | in the template |  |
| Edmonds-Karp | in the template |  |
| Bipartite matching | in the template |  |
| Min. path cover | in the template |  |
| Topological sorting | basic / trivial |  |
| Strongly connected components | in the template |  |
| 2-SAT | in the template |  |
| Cut vertices, cut-edges and biconnected components | in the template |  |
| Edge coloring | wild (C) |  |
| Trees | wild (C) | as "Edge coloring" |
| Vertex coloring | wild (C) |  |
| Bipartite graphs (=> trees) | basic / trivial |  |
| 3^n (special case of set cover) | basic / trivial |  |
| Diameter and centroid | basic / trivial |  |
| K'th shortest path | maybe | as "K-th shortest path" |
| Shortest cycle | maybe |  |
| **Dynamic programming** | | |
| Knapsack | basic / trivial |  |
| Coin change | basic / trivial |  |
| Longest common subsequence | basic / trivial |  |
| Longest increasing subsequence | basic / trivial |  |
| Number of paths in a dag | basic / trivial |  |
| Shortest path in a dag | basic / trivial |  |
| Dynprog over intervals | basic / trivial |  |
| Dynprog over subsets | basic / trivial |  |
| Dynprog over probabilities | maybe | as "Expected value DP" |
| Dynprog over trees | basic / trivial |  |
| 3^n set cover | basic / trivial |  |
| Divide and conquer | basic / trivial |  |
| Knuth optimization | kept |  |
| Convex hull optimizations | in the template |  |
| RMQ (sparse table a.k.a 2^k-jumps) | in the template |  |
| Bitonic cycle | maybe | as "Bitonic tour" |
| Log partitioning (loop over most restricted) | maybe | as "Exchange DP order" |
| **Combinatorics** | | |
| Computation of binomial coefficients | basic / trivial |  |
| Pigeon-hole principle | kept | as "Pigeonhole" |
| Inclusion/exclusion | maybe | as "Inclusion-exclusion" |
| Catalan number | in the template |  |
| Pick's theorem | in the template |  |
| **Number theory** | | |
| Integer parts | in the template |  |
| Divisibility | in the template |  |
| Euclidean algorithm | in the template |  |
| Modular arithmetic | in the template |  |
| Modular multiplication | in the template |  |
| Modular inverses | in the template |  |
| Modular exponentiation by squaring | in the template |  |
| Chinese remainder theorem | in the template |  |
| Fermat's little theorem | in the template |  |
| Euler's theorem | in the template |  |
| Phi function | in the template |  |
| Frobenius number | kept |  |
| Quadratic reciprocity | wild (C) |  |
| Pollard-Rho | in the template |  |
| Miller-Rabin | in the template |  |
| Hensel lifting | maybe |  |
| Vieta root jumping | maybe | as "Vieta jumping" |
| **Game theory** | | |
| Combinatorial games | kept | as "Sprague-Grundy" |
| Game trees | basic / trivial |  |
| Mini-max | basic / trivial |  |
| Nim | kept |  |
| Games on graphs | kept | as "Token on a graph" |
| Games on graphs with loops | kept | as "Games with cycles" |
| Grundy numbers | kept | as "Sprague-Grundy" |
| Bipartite games without repetition | kept | as "Token on a graph" |
| General games without repetition | kept | as "Games with cycles" |
| Alpha-beta pruning | wild (C) |  |
| **Probability theory** | | |
| **Optimization** | | |
| Binary search | basic / trivial |  |
| Ternary search | in the template |  |
| Unimodality and convex functions | in the template |  |
| Binary search on derivative | basic / trivial |  |
| **Numerical methods** | | |
| Numeric integration | in the template |  |
| Newton's method | basic / trivial |  |
| Root-finding with binary/ternary search | basic / trivial |  |
| Golden section search | maybe |  |
| **Matrices** | | |
| Gaussian elimination | in the template |  |
| Exponentiation by squaring | in the template |  |
| **Sorting** | | |
| Radix sort | basic / trivial |  |
| **Geometry** | | |
| Coordinates and vectors | in the template |  |
| Cross product | in the template |  |
| Scalar product | in the template |  |
| Convex hull | in the template |  |
| Polygon cut | in the template |  |
| Closest pair | in the template |  |
| Coordinate-compression | basic / trivial |  |
| Quadtrees | wild (C) | as "Quadtree" |
| KD-trees | in the template |  |
| All segment-segment intersection | wild (C) | as "Segment intersections" |
| **Sweeping** | | |
| Discretization (convert to events and sweep) | basic / trivial |  |
| Angle sweeping | in the template |  |
| Line sweeping | basic / trivial |  |
| Discrete second derivatives | kept | as "Discrete 2nd derivatives" |
| **Strings** | | |
| Longest common substring | in the template |  |
| Palindrome subsequences | basic / trivial |  |
| Knuth-Morris-Pratt | in the template |  |
| Tries | basic / trivial |  |
| Rolling polynomial hashes | in the template |  |
| Suffix array | in the template |  |
| Suffix tree | in the template |  |
| Aho-Corasick | in the template |  |
| Manacher's algorithm | in the template |  |
| Letter position lists | kept | as "Next-occurrence table" |
| **Combinatorial search** | | |
| Meet in the middle | kept |  |
| Brute-force with pruning | basic / trivial |  |
| Best-first (A*) | maybe | as "IDA* / A*" |
| Bidirectional search | basic / trivial |  |
| Iterative deepening DFS / A* | maybe | as "IDA* / A*" |
| **Data structures** | | |
| LCA (2^k-jumps in trees in general) | in the template |  |
| Pull/push-technique on trees | basic / trivial |  |
| Heavy-light decomposition | in the template |  |
| Centroid decomposition | in the template |  |
| Lazy propagation | in the template |  |
| Self-balancing trees | in the template |  |
| Convex hull trick (wcipeg.com/wiki/Convex_hull_trick) | in the template |  |
| Monotone queues / monotone stacks / sliding queues | kept | as "Monotone queue DP" |
| Sliding queue using 2 stacks | kept | as "Queue from two stacks" |
| Persistent segment tree | in the template |  |

## OI-wiki list (370 lines), line by line

Kept 44, maybe 24, wild 68, in the template 128, trivial 74, left out 8, other niche 0 (headings 24).

| Line | Verdict | |
|---|---|---|
| **Algorithm analysis** | | |
| Complexity | basic / trivial |  |
| Amortized complexity | basic / trivial |  |
| **Basic techniques** | | |
| Enumeration | basic / trivial |  |
| Simulation | basic / trivial |  |
| Recursion and divide and conquer | basic / trivial |  |
| Greedy algorithms | basic / trivial |  |
| Prefix sums and differences | kept | as "Differences / prefix sums" |
| Binary search | basic / trivial |  |
| Binary lifting | in the template |  |
| Construction | basic / trivial |  |
| Discretization | basic / trivial |  |
| Two pointers | basic / trivial |  |
| Fractional programming | kept |  |
| Space optimization | basic / trivial |  |
| **Sorting** | | |
| Selection sort | basic / trivial |  |
| Bubble sort | basic / trivial |  |
| Insertion sort | basic / trivial |  |
| Counting sort | basic / trivial |  |
| Radix sort | basic / trivial |  |
| Quick sort | basic / trivial |  |
| Merge sort | basic / trivial |  |
| Heap sort | basic / trivial |  |
| Bucket sort | basic / trivial |  |
| Shell sort | left out (not an algorithm) |  |
| Tournament sort | left out (not an algorithm) |  |
| Timsort | left out (not an algorithm) |  |
| Applications of sorting | basic / trivial |  |
| **Combinatorial search** | | |
| DFS | basic / trivial |  |
| BFS | basic / trivial |  |
| Bidirectional search | basic / trivial |  |
| Heuristic search | maybe | as "IDA* / A*" |
| Best-first (A*) | maybe | as "IDA* / A*" |
| Iterative deepening DFS / IDA* | maybe | as "IDA* / A*" |
| Backtracking | basic / trivial |  |
| Dancing links | maybe | as "Exact cover" |
| Alpha-beta pruning | wild (C) |  |
| Optimizing search (pruning) | basic / trivial |  |
| **Dynamic programming** | | |
| Memoized search | basic / trivial |  |
| Knapsack | basic / trivial |  |
| Advanced knapsack | maybe | as "Bounded knapsack" |
| Dynprog over intervals | basic / trivial |  |
| Dynprog over DAGs | basic / trivial |  |
| Dynprog over trees | kept | as "Rerooting" |
| Dynprog over subsets (bitmask) | in the template |  |
| Digit DP | kept |  |
| Plug DP | kept | as "Broken profile DP" |
| Counting DP | basic / trivial |  |
| Dynamic DP | kept |  |
| Dynprog over probabilities | maybe | as "Expected value DP" |
| DP of DP | kept | as "DP over an automaton" |
| DP optimization | heading |  |
| Monotone queues / monotone stacks | kept | as "Monotone queue DP" |
| Convex hull optimization (slope optimization) | in the template |  |
| Quadrangle inequality (Knuth optimization) | kept | as "Knuth optimization" |
| Slope trick | in the template |  |
| WQS binary search | kept | as "Aliens trick (WQS)" |
| State design | basic / trivial |  |
| **Strings** | | |
| String matching | basic / trivial |  |
| Rolling polynomial hashes | in the template |  |
| Tries | kept | as "Binary trie" |
| Knuth-Morris-Pratt (prefix function) | in the template |  |
| Boyer-Moore | wild (C) |  |
| Z-function | in the template |  |
| Aho-Corasick | in the template |  |
| Suffix array | in the template |  |
| Optimal in-place suffix sorting | wild (C) | as "SA-IS" |
| Suffix automaton | in the template |  |
| Generalized suffix automaton | wild (C) | as "Generalized SAM" |
| Suffix balanced tree | wild (C) |  |
| Suffix tree | in the template |  |
| Manacher's algorithm | in the template |  |
| Palindromic tree | in the template |  |
| Subsequence automaton | kept | as "Next-occurrence table" |
| Minimal rotation | in the template |  |
| Lyndon decomposition | maybe | as "Lyndon / Duval" |
| Main-Lorentz algorithm | wild (C) | as "Main-Lorentz" |
| **Math basics** | | |
| Boolean algebra | basic / trivial |  |
| Numeral systems | basic / trivial |  |
| Positional notation | basic / trivial |  |
| Balanced ternary | wild (C) |  |
| Gray code | maybe |  |
| Bit manipulation | in the template |  |
| Binary set operations | in the template |  |
| Arbitrary-precision arithmetic | in the template |  |
| Exponentiation by squaring | in the template |  |
| Permutations | in the template |  |
| Radians and coordinate systems | basic / trivial |  |
| Complex numbers | basic / trivial |  |
| **Number theory** | | |
| Modular arithmetic | in the template |  |
| Primes | in the template |  |
| Greatest common divisor | in the template |  |
| Euler's totient function | in the template |  |
| Sieves | in the template |  |
| Prime factorization (Pollard-Rho, Miller-Rabin) | in the template |  |
| Bezout's theorem and linear Diophantine equations | in the template |  |
| Fermat's little theorem and Euler's theorem | in the template |  |
| Modular inverses | in the template |  |
| Linear congruences | in the template |  |
| Chinese remainder theorem | in the template |  |
| Lifting the exponent | in the template |  |
| Factorials modulo | in the template |  |
| Lucas's theorem | in the template |  |
| Congruence equations | in the template |  |
| Quadratic residues | in the template |  |
| Order and primitive roots | in the template |  |
| Discrete logarithm | in the template |  |
| Higher-order residues and roots of unity | wild (C) | as "k-th roots mod p" |
| Floor division blocks | in the template |  |
| Dirichlet convolution | in the template |  |
| Mobius inversion | in the template |  |
| Dirichlet hyperbola method and Du's sieve | in the template |  |
| Prime counting | in the template |  |
| Powerful number sieve | wild (C) |  |
| Min_25 sieve | wild (C) |  |
| Zhou's sieve | wild (C) |  |
| Euclid-like algorithm | in the template |  |
| Continued fractions | kept | as "Stern-Brocot" |
| Stern-Brocot tree and Farey sequence | kept | as "Stern-Brocot" |
| Quadratic fields | wild (C) |  |
| Pell's equation | maybe | as "Pell equation" |
| **Polynomials and generating functions** | | |
| Fundamental theorem of algebra | basic / trivial |  |
| Fast Fourier transform | in the template |  |
| Number theoretic transform | in the template |  |
| Fast Walsh-Hadamard transform | in the template |  |
| Chirp Z-transform | wild (C) |  |
| Polynomial Newton iteration | in the template |  |
| Multipoint evaluation / fast interpolation | wild (C) | as "Multipoint evaluation" |
| Elementary functions of polynomials | in the template |  |
| Linear recurrences with constant coefficients | in the template |  |
| Polynomial shift | wild (C) |  |
| Symbolic method | in the template |  |
| Lagrange inversion | wild (C) |  |
| Composition and compositional inverse | wild (C) | as "Composition" |
| Ordinary generating functions | in the template |  |
| Exponential generating functions | in the template |  |
| **Combinatorics** | | |
| Permutations and combinations | basic / trivial |  |
| Pigeon-hole principle | kept | as "Pigeonhole" |
| Inclusion/exclusion | maybe | as "Inclusion-exclusion" |
| Fibonacci numbers | maybe | as "gcd of powers" |
| Derangements | in the template |  |
| Catalan number | in the template |  |
| Stirling numbers | in the template |  |
| Bell numbers | in the template |  |
| Bernoulli numbers | in the template |  |
| Entringer numbers | wild (C) | as "Entringer / zigzag" |
| Eulerian numbers | in the template |  |
| Partition numbers | in the template |  |
| Vandermonde convolution | maybe | as "Vandermonde" |
| Polya enumeration | in the template |  |
| Graph enumeration | wild (C) |  |
| **Linear algebra** | | |
| Vectors | basic / trivial |  |
| Inner and outer products | basic / trivial |  |
| Matrices | in the template |  |
| Elementary operations | basic / trivial |  |
| Determinants | in the template |  |
| Vector spaces | basic / trivial |  |
| Linear basis | in the template |  |
| Linear maps | basic / trivial |  |
| Characteristic polynomial | wild (C) |  |
| Diagonalization | wild (C) | as "Diagonalization / Jordan" |
| Jordan normal form | wild (C) | as "Diagonalization / Jordan" |
| Linear programming | wild (C) |  |
| Simplex method | wild (C) | as "Linear programming" |
| **Abstract algebra** | | |
| Groups | left out (not an algorithm) |  |
| Rings | left out (not an algorithm) |  |
| Fields | left out (not an algorithm) |  |
| Schreier-Sims algorithm | wild (C) | as "Schreier-Sims" |
| **Probability theory** | | |
| Conditional probability and independence | basic / trivial |  |
| Random variables | basic / trivial |  |
| Expectation and variance | kept | as "Linearity of expectation" |
| Probability inequalities | wild (C) | as "Probability bounds" |
| **Game theory** | | |
| Impartial combinatorial games | kept | as "Sprague-Grundy" |
| Zero-sum games | wild (C) | as "Linear programming" |
| Partizan games | wild (C) |  |
| **Numerical methods** | | |
| Interpolation | in the template |  |
| Numeric integration | in the template |  |
| Gaussian elimination | in the template |  |
| Newton's method | basic / trivial |  |
| **Other math** | | |
| Order theory | in the template |  |
| Young tableaux | wild (C) |  |
| Matroids | kept | as "Matroid" |
| Berlekamp-Massey | in the template |  |
| **Data structures** | | |
| Stack | basic / trivial |  |
| Queue | basic / trivial |  |
| Linked list | basic / trivial |  |
| Hash table | in the template |  |
| Disjoint-set union | in the template |  |
| Complexity of DSU | basic / trivial |  |
| Heaps | basic / trivial |  |
| Binary heap | basic / trivial |  |
| Pairing heap | wild (C) | as "Pairing / leftist heap" |
| Leftist tree | wild (C) | as "Pairing / leftist heap" |
| Blocking (sqrt decomposition) | kept | as "Rebuild every sqrt(Q)" |
| Block array | basic / trivial |  |
| Block list | wild (C) |  |
| Tree blocking | wild (C) |  |
| Sqrt tree | wild (C) |  |
| Monotone stack | kept | as "Nearest smaller values" |
| Monotone queue | kept | as "Monotone queue DP" |
| RMQ (sparse table a.k.a 2^k-jumps) | in the template |  |
| Fenwick tree | in the template |  |
| Segment tree | in the template |  |
| Lazy propagation | in the template |  |
| Merging and splitting | kept | as "Segment tree merging" |
| Li Chao tree | in the template |  |
| Cat tree | wild (C) | as "Disjoint sparse table" |
| Segment tree beats (range chmin/chmax, historical extrema) | in the template |  |
| Kinetic tournament tree | wild (C) | as "Kinetic segment tree" |
| Partition tree | maybe | as "Merge sort tree / wavelet" |
| Self-balancing trees | in the template |  |
| Treap | in the template |  |
| Splay tree | wild (C) |  |
| WBLT | wild (C) |  |
| Scapegoat tree | wild (C) | as "Balanced BSTs" |
| Cartesian tree | kept |  |
| Size balanced tree | wild (C) | as "Balanced BSTs" |
| AVL tree | wild (C) | as "Balanced BSTs" |
| Red-black tree | wild (C) | as "Balanced BSTs" |
| Left-leaning red-black tree | wild (C) | as "Balanced BSTs" |
| AA tree | wild (C) | as "Balanced BSTs" |
| Skip list | wild (C) |  |
| Persistent data structures | in the template |  |
| Persistent segment tree | in the template |  |
| Persistent block array | wild (C) |  |
| Persistent balanced tree | wild (C) |  |
| Persistent trie | maybe | as "Binary trie" |
| Persistent mergeable heap | wild (C) | as "Persistent heap" |
| Trees in trees | in the template |  |
| Segment tree in segment tree | in the template |  |
| Segment tree in balanced tree | wild (C) | as "Tree in tree" |
| Balanced tree in segment tree | wild (C) | as "Tree in tree" |
| Weight segment tree in Fenwick tree | wild (C) | as "Tree in tree" |
| Fenwick tree in block array | wild (C) | as "Tree in tree" |
| KD-trees | in the template |  |
| Global balanced binary tree | wild (C) |  |
| Dynamic trees | in the template |  |
| Link-cut tree | in the template |  |
| Euler tour tree | wild (C) |  |
| Top tree | wild (C) |  |
| Split-merge tree | kept | as "Segment tree merging" |
| PQ tree | wild (C) |  |
| Finger tree | wild (C) |  |
| Huffman tree | maybe | as "Huffman merging" |
| **Graph theory** | | |
| Graph concepts | basic / trivial |  |
| Graph storage | basic / trivial |  |
| Depth first search | basic / trivial |  |
| Breadth first search | basic / trivial |  |
| Tree diameter | basic / trivial |  |
| Tree center | basic / trivial |  |
| Centroid | basic / trivial |  |
| LCA (2^k-jumps in trees in general) | in the template |  |
| Heavy-light decomposition | in the template |  |
| Small-to-large on trees (DSU on tree) | in the template |  |
| Virtual tree | in the template |  |
| Centroid decomposition | in the template |  |
| Dynamic centroid decomposition | in the template |  |
| AHU algorithm (tree isomorphism) | kept | as "Tree isomorphism" |
| Tree hashing | kept | as "Tree isomorphism" |
| Random walks on trees | kept | as "Expected hitting times" |
| Directed acyclic graphs | basic / trivial |  |
| Topological sorting | basic / trivial |  |
| Shortest paths | basic / trivial |  |
| Dijkstra's algorithm | basic / trivial |  |
| Bellman-Ford | basic / trivial |  |
| Floyd-Warshall | basic / trivial |  |
| Difference constraints | kept |  |
| K'th shortest path | maybe | as "K-th shortest path" |
| Shortest paths modulo m | kept | as "Residue Dijkstra" |
| Minimum spanning tree | kept | as "MST cycle property" |
| Minimum arborescence | in the template |  |
| Minimum diameter spanning tree | wild (C) | as "Min diameter spanning tree" |
| Steiner tree | kept |  |
| Node splitting | in the template |  |
| Strongly connected components | in the template |  |
| Biconnected components | in the template |  |
| Cut vertices and cut-edges | in the template |  |
| Round-square tree | in the template |  |
| Vertex/edge connectivity | in the template |  |
| Cycle counting | kept | as "Triangles in O(m sqrt m)" |
| Shortest cycle | maybe |  |
| 2-SAT | in the template |  |
| Euler cycles | in the template |  |
| Hamiltonian graphs | basic / trivial |  |
| Bipartite graphs | kept | as "Grid is bipartite" |
| Planar graphs | kept | as "Planar bounds" |
| Chordal graphs | wild (C) |  |
| Graph coloring | wild (C) | as "Vertex coloring" |
| Flow networks | in the template |  |
| Max flow | in the template |  |
| Min cut | in the template |  |
| Min-cost max flow | in the template |  |
| Flows with lower and upper bounds | in the template |  |
| Stoer-Wagner | in the template |  |
| Graph matching | in the template |  |
| Bipartite matching | in the template |  |
| Max-weight bipartite matching | in the template |  |
| Maximal matching, general graphs | in the template |  |
| Max-weight matching, general graphs | wild (C) | as "Max-weight general matching" |
| Stable matching | maybe |  |
| Prufer sequences | in the template |  |
| Matrix tree theorem | in the template |  |
| LGV lemma | in the template |  |
| Maximum clique search | in the template |  |
| Dominator tree | maybe |  |
| Random walks on graphs | kept | as "Expected hitting times" |
| **Geometry** | | |
| Coordinates and vectors (2D) | in the template |  |
| 3D basics | wild (C) |  |
| Distance | in the template |  |
| Pick's theorem | in the template |  |
| Triangulation | wild (C) |  |
| Convex hull | in the template |  |
| Sweep line | basic / trivial |  |
| Rotating calipers | in the template |  |
| Half-plane intersection | in the template |  |
| Closest pair | in the template |  |
| Randomized incremental construction | in the template |  |
| Smallest enclosing circle | in the template |  |
| Inversion | kept |  |
| **Offline algorithms** | | |
| CDQ divide and conquer | kept |  |
| Parallel binary search | kept |  |
| Mo's algorithm | in the template |  |
| Mo's algorithm with modifications | maybe | as "Mo with updates" |
| Mo's algorithm on trees | in the template |  |
| Rollback Mo's algorithm | wild (C) | as "Rollback Mo" |
| 2D Mo's algorithm | wild (C) | as "2D Mo" |
| Secondary offline Mo's algorithm | wild (C) | as "Secondary offline Mo" |
| Mo's algorithm with bitset | wild (C) | as "Mo with bitset" |
| **Randomization** | | |
| Random functions | basic / trivial |  |
| Randomization techniques | kept | as "Random sampling" |
| Hill climbing | in the template |  |
| Simulated annealing | maybe |  |
| **Miscellaneous** | | |
| Hanging-line method | kept | as "Largest empty rectangle" |
| Finite state automata | basic / trivial |  |
| Fundamentals of computational theory | left out (not an algorithm) |  |
| Byte order (endianness) | left out (not an algorithm) |  |
| Josephus problem | maybe | as "Josephus" |
| Expression evaluation | basic / trivial |  |
| Scheduling jobs on one machine | kept | as "Exchange argument" |
| Majority element | maybe | as "Majority vote" |
| Garsia-Wachs algorithm | wild (C) | as "Garsia-Wachs" |
| 15-puzzle | kept | as "Invariants, monovariants" |
| Kahan summation | maybe |  |
| Chtholly tree (color segment amortization) | in the template |  |
| **Topics** | | |
| RMQ | in the template |  |
| Applications of disjoint-set union | basic / trivial |  |
| Bracket sequences | kept | as "Reflection principle" |
| Segment tree and offline queries | kept | as "Sort queries by right end" |
