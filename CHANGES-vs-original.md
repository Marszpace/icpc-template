# Changes compared to the original KACTL

"Original" is `main` of this repository, i.e. the default KACTL book. Everything below is about what is
**printed in `kactl.pdf`**; cut files stay in the repository (only their `\kactlimport` line is commented out),
so they can be turned back on in the `chapter.tex` of their directory.

The book is now **25 PDF pages (cover + 24)**, one under the Danang limit (26), after the team cut *C++ pitfalls* and `Int128.h` (2026-11-09), changed the layout and shortened the descriptions (2026-11-11). About 2.2 columns are free on the last body page; the techniques page is full.

## Added to the book

| Chapter | File | Lines (whole file) | Note |
|---|---|---:|---|
| data-structures | `LazySegTreeBlock.h` + `LazySegTree.h` | 38 + 59 | one lazy segment tree: edit block (default: range chmin + add, sum/max/count, segment tree beats) + fixed body; replaces `LazySegmentTree` and the old generic `LazySegTree`; `HLD` uses it; `maxRight(l, f)` descends the tree in O(log N) |
| data-structures | `PersistentSegmentTree.h` | 49 |  |
| data-structures | `DynCon.h` | 45 |  |
| data-structures | `LiChao.h` | 44 |  |
| geometry | `LineProjectionReflection.h` | 21 | existing file, was commented out |
| geometry | `CircleLine.h` | 24 | existing file, was commented out |
| geometry | `HalfPlane.h` | 49 |  |
| geometry | `MinkowskiSum.h` | 33 |  |
| geometry | `ManhattanMST.h` | 38 | existing file, was commented out |
| geometry | `RectangleUnion.h` | 44 |  |
| graph | `Dinic.h` | 53 | existing file, was commented out (replaces `EdmondsKarp`) |
| graph | `BlockCutTree.h` | 40 |  |
| graph | `CentroidDecomposition.h` | 35 |  |
| graph | `DsuOnTree.h` | 43 |  |
| number-theory | `PrimitiveRoot.h` | 30 |  |
| number-theory | `ExLucas.h` | 59 | binomial mod any m |
| number-theory | `Lucy.h` | 37 | prime counting / prime sums for all n/i in O(n^(3/4)), generic in f(p) and the prefix sum g(v) |
| number-theory | `DuSieve.h` | 56 | prefix sums of phi (128 bit) and mu for all n/i in O(n^(2/3)) |
| combinatorial | `RadixConversion.h` | 67 | bijective base conversion of digit vectors (for communication problems), and the same with permutations as the target (`radixToPerm` / `permToRadix`, exact bijection between all digit sequences and all permutations, (length, lex) order to (size, lex) order); shared helper `mulAdd` |
| numerical | `BostanMori.h` | 34 | n-th term of a linear recurrence in O(n log n log k), same interface as `linearRec` (NTT, mod 998244353) |
| numerical | `LagrangeInterpolation.h` | 34 |  |
| numerical | `SolveLinearMod.h` | 43 |  |
| numerical | `XorBasis.h` | 44 |  |
| numerical | `PolyOps.h` | 87 | now also `polyPow` (any a, k up to 1e18), `polySqrt` (a[0] = 1) and `polyDivMod` |
| strings | `PalindromicTree.h` | 39 |  |
| strings | `SuffixAutomaton.h` | 47 | new; replaces `SuffixTree` |
| various | `IntervalMap.h` | 39 | new; replaces `IntervalContainer` (with `bool` values it does the same job) |
| | **27 files** | **1105** | |

Also new in the book, as text notes (no code):

- Graph: *Flows with lower bounds* (incl. min flow, convex edge costs) and *Min cut models*
  (closure, vertex cover, independent set, path cover, Dilworth) and *Segment tree graph*
- Number theory: *Floor blocks*
- Math: *Lattice polygons* (Pick's theorem)
- Graph: *Spanning trees, Euler circuits, disjoint paths* (matrix-tree theorem with the directed conventions, BEST theorem, Lindstrom-Gessel-Viennot lemma)
- Number theory: *Garner's algorithm*, *Exponents* (generalized Euler, lifting the exponent), and the linear Diophantine part added to the Bezout text (also fixes its "a != " typo)
- Strings: *Suffix array and automaton facts* (lcp by range minimum, distinct / k-th substring, longest common substring, generalized automaton)
- Combinatorial: *Generating functions* (about one column: dictionary, common series, counting structures, computing)
- Various: *Python* (big integers, `math`, `decimal`, recursion; checked on the judge's CPython 3.12.3 and PyPy 7.3.15)
- All formulas of these notes are checked by the scripts in `doc/note-checks/` (`run-all.sh`, not part of `make test`)
- Contest: `stress.sh` (stress loop with optional brute force / checker) and `interactive.sh` (interactor wired with fifos; one test or stress mode with a generator; commented-out `tee` transcript), 38 lines
- Various / dynamic programming: *Slope trick*
- Various / dynamic programming: *Sum over subsets (SOS DP)* (definition, recurrence, in-place loop, supersets, inverse); replaces the one-line "sums of subsets" bit hack

## Cut from the book

| Chapter | File | Lines (whole file) | Note |
|---|---|---:|---|
| data-structures | `SubMatrix.h` | 27 |  |
| various | `Int128.h` | 21 | printing for `__int128`; team: known by heart (kept as file, stress-tested, used by the DuSieve test) |
| geometry | `FastDelaunay.h` | 106 |  |
| geometry | `PolyhedronVolume.h` | 14 |  |
| geometry | `Point3D.h` | 43 |  |
| geometry | `3dHull.h` | 63 |  |
| geometry | `sphericalDistance.h` | 23 |  |
| graph | `EdmondsKarp.h` | 47 | replaced by `Dinic` |
| graph | `EdgeColoring.h` | 46 |  |
| number-theory | `ContinuedFractions.h` | 37 | niche number theory |
| number-theory | `FracBinarySearch.h` | 38 | niche number theory |
| numerical | `PolyRoots.h` | 35 |  |
| numerical | `GoldenSectionSearch.h` | 33 |  |
| numerical | `IntegrateAdaptive.h` | 30 |  |
| numerical | `Simplex.h` | 85 | LP is rare; flows cover most uses |
| numerical | `Tridiagonal.h` | 61 |  |
| strings | `SuffixTree.h` | 65 | replaced by `SuffixAutomaton` |
| various | `IntervalContainer.h` | 34 | replaced by `IntervalMap` |
| various | `ConstantIntervals.h` | 32 | niche |
| various | `FastKnapsack.h` | 27 | niche optimisation |
| various | `FastMod.h` | 23 |  |
| various | `SmallPtr.h` | 22 |  |
| various | `BumpAllocatorSTL.h` | 25 |  |
| various | `SIMD.h` | 57 |  |
| | **23 files** | **973** | |

Also in the repository but **not printed in the original KACTL either** (so they are not cuts): `UnionFind.h`, `PolygonUnion.h`,
`DelaunayTriangulation.h`, `Euclid.java`, `MatrixInverse-mod.h`, `Unrolling.h` (their imports are commented out in the original `chapter.tex`),
and `Eratosthenes.h`, `Hashing-codeforces.h` (no import at all).

Kept on purpose although they were candidates: `GomoryHu`, `GlobalMinCut`, `HillClimbing`, `CircleTangents`,
`LinkCutTree`, `DirectedMST`, `GeneralMatching`.

## Removed after the team review (2026-10-30)

The team went through every entry (`entries - nx_entries.csv`); these were judged too trivial or already memorized.
As above, code files stay in the repository with the `\kactlimport` line commented out; the text sections are deleted from `chapter.tex`.

| Chapter | Entry | Lines | Reason |
|---|---|---:|---|
| contest | `.vimrc` | 6 | no vim user |
| contest | `.bashrc` | 3 | the team uses VS Code, which does not use it |
| contest | `troubleshoot.txt` | 52 | team decision 2026-11-09 (generic checklist; frees a column) |
| math | Equations | 7 | elementary |
| math | Recurrences | 3 | can be derived |
| math | Spherical coordinates | 5 | memorized |
| math | Probability theory, Discrete / Continuous distributions, Markov chains | 50 | memorized |
| number-theory | `LinearSieve.h` | 29 | memorized |
| combinatorial | `Binomial.h` | 23 | trivial |
| combinatorial | Sprague-Grundy (whole *Games* section) | 5 | trivial |
| graph | `BellmanFord.h`, `FloydWarshall.h`, `TopoSort.h` | 83 | trivial |
| graph | Number of Spanning Trees | 4 | trivial |
| various | `LIS.h`, `KnuthDP.h` | 36 | trivial |
| various | `FastInput.h` | 29 | optimisation, never used |
| various | Aliens trick, Digit DP | 5 | trivial |
| various | `BumpAllocator.h` | 19 | nothing printed uses it any more (since `LazySegTree` replaced `LazySegmentTree`); team decision 2026-11-08 |
| graph | `DFSMatching.h` | 38 | `HopcroftKarp` is faster with the same interface; `MinimumVertexCover` now uses it (team decision 2026-11-08) |
| data-structures | `LazySegmentTree.h` | 66 | merged into `LazySegTree` (file deleted; the generic tree with an edit block does the same, `HLD` ported) |

Still open (edit / merge / undecided): see `TODO.md`.

## Existing files that were modified

| File | Change |
|---|---|
| `content/data-structures/Treap.h` | lazy range add and reverse with subtree sums (`go(t, l, r, f)`, `Node::app`, `push`); `val` is now `ll`; the old API (`split`, `merge`, `ins`, `each`, `move`) is unchanged and its test still passes |
| `content/combinatorial/IntPerm.h` | `permToInt` is now the lexicographic rank (order preserving), widened to `ll` (the old `int` version overflowed from n = 13), exact for n <= 20, plus its exact inverse `intToPerm` |
| `content/number-theory/ModularArithmetic.h` | replaced by the team's `mint` (prime `mod` below 2^30, Fermat inverse; no longer a template since 2026-11-11: it uses the global `const ll mod` that you declare; the old euclid-based `Mod` also inverted modulo composites); postfix `++` / `--` take `signed` so that it builds with `#define int long long` |
| `content/data-structures/UnionFindRollback.h` | optional parity argument `join(a, b, w)` and `par(x)`; old calls behave as before (`DirectedMST` test passes) |
| `content/contest/template.cpp` -> `macros.cpp` | removed `cin.exceptions(cin.failbit);` (it makes `while (cin >> x)` throw at EOF); then renamed to `macros.cpp` and reduced to the macros and typedefs: no `#include <bits/stdc++.h>`, no `using namespace std`, no `main` (remembered by the team), plus the new macro `#define pb push_back` |
| `stress-tests/utilities/template.h` | includes `<cassert>`, which GCC 16's `<bits/stdc++.h>` no longer does; now includes `macros.cpp` itself, and `-DLLINT` adds `#define int long long` |
| `content/contest/hash.sh` | takes a file argument (`./hash.sh file.cpp`; stdin still works for the book build); refuses unreadable files; same hash as before for the same input |
| `doc/scripts/prelude.h` | new: what `macros.cpp` assumes before it (includes, `using namespace std`, optional `#define int long long`), used by `make test-compiles` |
| 8 printed headers + 3 unprinted | work with `#define int long long` as well as without it (see below) |

### Compatibility with `#define int long long`

The team usually adds `#define int long long` (with `signed main`) after the includes. It is **not** in `macros.cpp`, but the whole library compiles and passes its tests both ways (`make test`, `make test-compiles`, and the same with `LLINT=1`). What had to change:

| Problem under the define | Files | Fix (works in both modes) |
|---|---|---|
| `int(x)` becomes `long long(x)` | `RectangleUnion`, `FastEratosthenes`, `FastFourierTransformMod` | `(int)(x)` |
| `max(int_var, 0)`: the literal stays 32-bit | `MaximumClique`, `MinRotation`, `SuffixArray`, `FastKnapsack` | `max<int>(...)` |
| `#include <bits/extc++.h>` after the define breaks the std headers | `HashMap`, `OrderStatisticTree`, `MinCostMaxFlow` (include line), `SIMD` | wrap the include in `#pragma push_macro("int")`, `#undef int`, `#pragma pop_macro("int")` |

Gotchas for your own code with the define: `max(x, 0)` / `min(x, 1)` need `0LL` or `<int>`, `int(x)` casts need `(int)(x)`, `__builtin_popcount` / `clz` take 32 bits (use the `ll` versions for wide masks), `1 << k` is still a 32-bit shift, and an `#include` of an extra std/ext header must come before the define.

## New stress tests (all pass; each was mutation-checked)

`IntervalMap`, `DynCon`, `PersistentSegmentTree`, `CentroidDecomposition`, `DsuOnTree`, `SuffixAutomaton`,
`HalfPlane`, `MinkowskiSum`, `LinearSieve`, `ExLucas`, `XorBasis`, `RadixConversion` (incl. `radixToPerm` / `permToRadix`), `Int128` (file only, not printed), `Lucy`, `DuSieve`, `ModularArithmetic` (rewritten for `mint`), `IntPerm`, `TreapLazy`, `BostanMori`, `LazySegTree` (4 tests, incl. `maxRight`: beats block, affine, clamp, min query), `RectangleUnion`, `PolyOps`,
`SolveLinearMod`, `Binomial`, `LagrangeInterpolation`, `PrimitiveRoot`, `LiChao`, `BlockCutTree`, `PalindromicTree`,
and for original KACTL files that had no test of the real header: `MatrixInverse`, `MatrixInverse-mod`, `Determinant`, `IntDeterminant`, `SolveLinear` (real header added to the old test), `Polynomial`, `PolyInterpolate`, `Integrate`, `HillClimbing`, `TernarySearch`, `BiconnectedComponents`, `CompressTree`, `GeneralMatching`, `Manacher`, `DivideAndConquerDP`, `IntervalCover`, `HashMap`, `OrderStatisticTree`, `Matrix`, `phiFunction`, `multinomial`, `linearTransformation`, `kdTree`, `Angle`
(in `stress-tests/<chapter>/`). The whole suite passes: `make test` 133/133 and `make test-compiles` 155/155, both also with `LLINT=1` (2026-11-09).

## Layout changes (2026-11-09)

Applied on top of the original KACTL layout (details, pictures and the rejected experiments: `doc/overnight-2026-11-09/REPORT.md`):

- File header: name, include list beside it and hash + line count flush right, then a thin rule, then the description with `Time:` behind it
  and `Usage:` at the bottom; 2.5pt of space before the code rule.
- Tighter spacing above and below listings, smaller section and subsection headings, a compact table of contents, 6pt column gap, 3pt above and below
  display equations (and a stray `\\` removed from the first trigonometry equations).
- Bug fixes: overlapping lines in text sections (the `\subsection` skip had negative stretch), the page 20 header ran into "NTU", two `Time:` lines ran
  into the hash, file titles stranded at the bottom of a column, figures in 4 geometry files overlapping the header.
- Shorter descriptions for 17 files (patch 09), 27 code lines shortened so they no longer wrap (the hashes of 15 files changed).
- Descriptions of all 126 files shortened (2026-11-11, level H of `doc/overnight-2026-11-10/`): the useful facts of the original text are kept, and facts that belong to one function (index base, return value, precondition) moved into trailing comments on its signature line (36 files, 42 comments); hashes unchanged. Two text-only headers keep their text.
- *Techniques* page: replaced by a 180-entry list of non-obvious techniques, each with a one-line hint (from the original page, the OI-wiki list and our own); `doc/overnight-2026-11-10/techniques/techniques.csv` has every candidate, kept or not, with the reason.

## Things to know

- There is **one** modulus convention now: a header that needs a modulus uses the global `const ll mod` that your solution declares first, and no header defines it
  (originally each of `ModPow`, NTT, `IntDeterminant` and `LinearRecurrence` defined its own, so two of them could not be included together). Used by `mint`,
  `modpow`, NTT, `PolyOps`, `BostanMori`, `IntDeterminant`, `LinearRecurrence`, `SolveLinearMod`, `LagrangeInterpolation`, ... `ModPow.h` is only `modpow` now.
  NTT has a `static_assert` that `mod = c * 2^k + 1`. The test prelude declares it (998244353, `-DTEST_MOD` overrides).
- The page limit of the Danang contest is 26 PDF pages (25 + cover), confirmed by the team on 2026-11-08.
- The cover page (`content/kactl.tex`) now names the NTU team.
- On GCC 16 or newer, add `#include <cassert>` to the contest template if you use `assert`.
