# Changes compared to the original KACTL

"Original" is `main` of this repository, i.e. the default KACTL book. Everything below is about what is
**printed in `kactl.pdf`**; cut files stay in the repository (only their `\kactlimport` line is commented out),
so they can be turned back on in the `chapter.tex` of their directory.

The book is still **26 PDF pages (cover + 25)**, the same as the original. About **50 more lines of code fit**
on the last page before it would grow to 27 pages (measured by importing filler code; it is an estimate, not a promise,
because a long code box can move the page break).

## Added to the book

| Chapter | File | Lines (whole file) | Note |
|---|---|---:|---|
| combinatorial | `Binomial.h` | 23 |  |
| data-structures | `LazySegTree.h` | 57 |  |
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
| number-theory | `LinearSieve.h` | 29 |  |
| numerical | `LagrangeInterpolation.h` | 34 |  |
| numerical | `SolveLinearMod.h` | 43 |  |
| numerical | `XorBasis.h` | 44 |  |
| numerical | `PolyOps.h` | 53 |  |
| strings | `PalindromicTree.h` | 39 |  |
| strings | `SuffixAutomaton.h` | 47 | new; replaces `SuffixTree` |
| various | `IntervalMap.h` | 39 | new; replaces `IntervalContainer` (with `bool` values it does the same job) |
| | **24 files** | **956** | |

Also new in the book, as text notes (no code):

- Graph: *Flows with lower bounds* (incl. min flow, convex edge costs) and *Min cut models*
  (closure, vertex cover, independent set, path cover, Dilworth) and *Segment tree graph*
- Combinatorial: *Sprague-Grundy*
- Number theory: *Floor blocks*
- Math: *Lattice polygons* (Pick's theorem)
- Various / dynamic programming: *Aliens trick*, *Slope trick*, *Digit DP*

## Cut from the book

| Chapter | File | Lines (whole file) | Note |
|---|---|---:|---|
| data-structures | `SubMatrix.h` | 27 |  |
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

Kept on purpose although they were candidates: `GomoryHu`, `GlobalMinCut`, `HillClimbing`, `CircleTangents`,
`LinkCutTree`, `DirectedMST`, `GeneralMatching`, `BumpAllocator` (used by `LazySegmentTree` and `HLD`).

## Existing files that were modified

| File | Change |
|---|---|
| `content/data-structures/UnionFindRollback.h` | optional parity argument `join(a, b, w)` and `par(x)`; old calls behave as before (`DirectedMST` test passes) |
| `content/contest/template.cpp` | removed `cin.exceptions(cin.failbit);` (it makes `while (cin >> x)` throw at EOF) |
| `stress-tests/utilities/template.h` | includes `<cassert>`, which GCC 16's `<bits/stdc++.h>` no longer does |

## New stress tests (all pass; each was mutation-checked)

`IntervalMap`, `DynCon`, `PersistentSegmentTree`, `CentroidDecomposition`, `DsuOnTree`, `SuffixAutomaton`,
`HalfPlane`, `MinkowskiSum`, `LinearSieve`, `XorBasis`, `LazySegTree`, `RectangleUnion`, `PolyOps`,
`SolveLinearMod`, `Binomial`, `LagrangeInterpolation`, `PrimitiveRoot`, `LiChao`, `BlockCutTree`, `PalindromicTree`
(in `stress-tests/<chapter>/`). The whole suite (`make test`) passes: 101/101.

## Things to know

- `PolyOps.h` and `NumberTheoreticTransform.h` use the modulus 998244353, while `ModPow.h`, `SolveLinearMod.h`,
  `Binomial.h`, `LagrangeInterpolation.h` use the global `mod` of `ModPow.h` (default 10^9+7). Set `mod` once when
  mixing them, as with the other KACTL number-theory files.
- The page limit of the Danang contest was assumed to be KACTL's (25 pages + cover). Please check the rules.
- The cover page (`content/kactl.tex`) still names KTH.
- On GCC 16 or newer, add `#include <cassert>` to the contest template if you use `assert`.
