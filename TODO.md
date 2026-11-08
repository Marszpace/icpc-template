# TODO (from the team review, `entries - nx_entries.csv`)

Book is at 25 pages (cover + 24): the last code page holds only `BumpAllocator.h` (8 lines), so deleting it gives 24. Everything below is still open.

## Applies to all code
- [x] Every kept code file has to be edited to match the new `macros.cpp` (done: `ll` stays, no library macro changes, everything also compiles and passes with `#define int long long`; run `LLINT=1 make test` / `LLINT=1 make test-compiles`).

## Contest
- [x] `template.cpp`: add / remove macros (done: renamed to `macros.cpp`, only macros and typedefs, one new macro `pb`; the define is not in the file).
- [x] `.bashrc`: dropped from the book (the team uses VS Code, which does not use it); file kept, import commented out.
- [x] `hash.sh`: improve usability (done: `./hash.sh file.cpp` prints the 6-char hash; stdin still works for the book build and vim).
- [x] `stress.sh` and `interactive.sh` (reference scripts, no compile step; loop + checker call, and the fifo wiring with test / stress modes).
  Done in `content/contest/`, tested by `doc/scripts/test-contest-scripts.sh`.

## Math
- [x] Derivatives/Integrals: delete integration by parts (memorized).
- [x] Sums: keep only the sum of 4th powers (others memorized).
- [x] Series: keep ln and sqrt only; maybe merge into one section to save lines.

## Numerical
- [ ] Add code: Bostan-Mori (nth term of a linear recurrence).

## Data structures
- [x] Merge `LazySegmentTree.h` and `LazySegTree.h` into one lazy segment tree that supports queries better (done: `LazySegTreeBlock.h` + `LazySegTree.h`, `HLD` ported).
- [ ] Edit Fenwick Trees

## Combinatorial
- [x] Add code: RadixConversion (done: `RadixConversion.h`, bijective numeration so `radixconv(radixconv(x, a, b), b, a) == x` always; O(n * m)).
- [ ] `IntPerm.h`: add "integer to permutation", or delete (undecided).

## Number theory
- [ ] Add text: Garner (CRT for many moduli).
- [ ] Edit ModInt

## Graph
- [ ] `LCA.h`: undecided, binary lifting can already do LCA.

## Various
- [ ] Add Python Tricks
- [ ] `BumpAllocator.h`: delete later. nothing printed includes it any more (only the unprinted `SmallPtr.h`), so it can go whenever the team agrees.

## Category to decide (`???`)
- [ ] Add text: Ordinary and Exponential Generating Functions.

## Not from the CSV
- [ ] Check the Danang page limit in the contest rules (assumed 25 pages + cover; we are at 24 + cover).
- [x] Re-run `make test` (104/104 passed after the lazy segment tree merge). `make test-compiles` fails on `PolyOps.h` (`mod` redefined via `NumberTheoreticTransform.h`), not yet fixed.
- [ ] With the space freed, decide what to add back or add new (candidates: the 23+8 cut files listed in `CHANGES-vs-original.md`).

## From the coverage audit (2026-11-01)
Found by a subagent audit of the book; not verified by running anything. Team decisions: Aliens, Knuth DP and game theory are
memorized (not added); Simplex stays cut (flows / LP by hand); `PushRelabel` stays (needed for O(V^3) on complete graphs).

Add, most worthwhile first (about 50 printed lines for the first six):
- [ ] Graph, text: matrix-tree note (directed Laplacian, rooted arborescences, BEST theorem, Lindstrom-Gessel-Viennot). The old 4-line
  "Number of Spanning Trees" section was cut; `stress-tests/graph/matrix-tree.cpp` still exists.
- [ ] Data structures: lazy implicit treap (reverse + add), about +10 lines on `Treap.h` (no lazy tags now).
- [ ] Data structures: segment tree descent (`findFirst` / `maxRight`), about 10 lines, in the `LazySeg` body.
- [ ] Number theory, text: generalized Euler (`a^b mod m` for huge b), lifting-the-exponent lemma, counting solutions of `ax+by=c` in a range.
- [ ] Strings, text: suffix array / suffix automaton identities (lcp via RMQ, distinct substrings, k-th substring, generalized SAM).
- [ ] Contest: C++ pitfalls list, `__int128` print, stress-test loop (done: `stress.sh` / `interactive.sh`).
- [ ] Number theory: Lucy_Hedgehog (prime counting) and Du sieve (prefix sums of phi / mu), about 40 lines, pairs with the Floor blocks text.
- [ ] Numerical: `polyPow`, `polySqrt`, `polyDivMod` in `PolyOps.h`, about 20 lines.

Optional / nice to have: stable marriage, min mean cycle (Karp), Steiner tree DP, tree isomorphism hashing, Lyndon factorization,
subset convolution, online (CDQ) convolution, Mo with updates, circle union area, minimum-area bounding rectangle, 3D formulas as text,
Fibonacci / Josephus identities, Java / Python snippets (only if a teammate uses them).

Cleanup ideas (free about 0.4 page):
- [ ] Drop `DFSMatching.h` (38) after pointing `MinimumVertexCover` at `HopcroftKarp` (same signature, its test already includes it).
- [ ] Remove the empty headings that print with nothing under them: graph "Fundamentals" and "Coloring", number theory "Fractions", geometry "3D".
- [ ] `techniques.txt` (159 lines, one full page) is stale after the cuts (Suffix tree, Edge coloring, Edmonds-Karp, Bellman-Ford, Floyd-Warshall,
  Knuth, Matrix tree, Grundy). Trimming it is the biggest page lever, but the CSV says Keep: team decision.
- [ ] `lineDistance.h` still mentions `Point3D` after the 3D files were cut.
- [ ] The global `const ll mod` is defined in six headers (`ModInverse`, `ModPow`, `ModularArithmetic`, `IntDeterminant`, `LinearRecurrence`,
  `NumberTheoreticTransform`); including two of them fails to compile.
- [ ] `CHANGES-vs-original.md` cut table is missing: `UnionFind`, `PolygonUnion`, `DelaunayTriangulation`, `Hashing-codeforces`,
  `MatrixInverse-mod`, `Eratosthenes.h`, `Euclid.java`, `Unrolling`.
- [ ] Weakly tested: `GeneralMatching` ("not very well tested"), `Integrate` ("mostly untested"); about 20 files have no test with a matching name
  (e.g. `HashMap`, `Manacher`, `Matrix`, `BiconnectedComponents`), maybe covered indirectly.
