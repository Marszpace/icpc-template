# TODO (from the team review, `entries - nx_entries.csv`)

Book is at 24 pages (cover + 23) after the deletions. Everything below is still open.

## Applies to all code
- [ ] Every kept code file has to be edited to match the new `template.cpp` (macros, `ll`, etc.), once that is final.

## Contest
- [ ] `template.cpp`: add / remove macros.
- [ ] `.bashrc`: change the compile command, remove `xkeymodmap`.
- [ ] `hash.sh`: improve usability.
- [ ] `stress.sh`: stress-test script for normal problems (compile the solution, a brute force and a generator; loop over seeds, run
  generator -> both programs, `diff` the outputs, stop and keep the failing input on the first mismatch).
- [ ] `interactive.sh`: stress-test script for interactive problems (run the solution against an interactor / judge program through
  named pipes, seed-driven generator, stop on wrong answer, crash or timeout, keep the failing case). Both scripts should be short enough to type in contest.

## Math
- [x] Derivatives/Integrals: delete integration by parts (memorized).
- [x] Sums: keep only the sum of 4th powers (others memorized).
- [x] Series: keep ln and sqrt only; maybe merge into one section to save lines.

## Numerical
- [ ] Add code: Bostan-Mori (nth term of a linear recurrence).

## Data structures
- [x] Merge `LazySegmentTree.h` and `LazySegTree.h` into one lazy segment tree that supports queries better (done: `LazySegTreeBlock.h` + `LazySegTree.h`, `HLD` ported).

## Combinatorial
- [ ] Add code: RadixConversion.
- [ ] `IntPerm.h`: add "integer to permutation", or delete (undecided).

## Number theory
- [ ] Add text: Garner (CRT for many moduli).

## Graph
- [ ] `LCA.h`: undecided, binary lifting can already do LCA.

## Various
- [ ] `BumpAllocator.h`: delete later. nothing printed includes it any more (only the unprinted `SmallPtr.h`), so it can go whenever the team agrees.

## Category to decide (`???`)
- [ ] Add text: Ordinary and Exponential Generating Functions.

## Not from the CSV
- [ ] Check the Danang page limit in the contest rules (assumed 25 pages + cover; we are at 23 + cover).
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
- [ ] Contest: C++ pitfalls list, `__int128` print, stress-test loop (now covered by `stress.sh` / `interactive.sh` under Contest).
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
