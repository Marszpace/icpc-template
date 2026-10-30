# Changes compared to the original KACTL

"Original" is `main` of this repository, i.e. the default KACTL book. Everything below is about what is
**printed in `kactl.pdf`**; cut files stay in the repository (only their `\kactlimport` line is commented out),
so they can be turned back on in the `chapter.tex` of their directory.

The book is now **24 PDF pages (cover + 23)**, two fewer than the original (26), after the team review below.

## Added to the book

| Chapter | File | Lines (whole file) | Note |
|---|---|---:|---|
| data-structures | `LazySegTreeBlock.h` + `LazySegTree.h` | 38 + 45 | one lazy segment tree: edit block (default: range chmin + add, sum/max/count, segment tree beats) + fixed body; replaces `LazySegmentTree` and the old generic `LazySegTree`; `HLD` uses it |
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
| numerical | `LagrangeInterpolation.h` | 34 |  |
| numerical | `SolveLinearMod.h` | 43 |  |
| numerical | `XorBasis.h` | 44 |  |
| numerical | `PolyOps.h` | 53 |  |
| strings | `PalindromicTree.h` | 39 |  |
| strings | `SuffixAutomaton.h` | 47 | new; replaces `SuffixTree` |
| various | `IntervalMap.h` | 39 | new; replaces `IntervalContainer` (with `bool` values it does the same job) |
| | **24 files** | **963** | |

Also new in the book, as text notes (no code):

- Graph: *Flows with lower bounds* (incl. min flow, convex edge costs) and *Min cut models*
  (closure, vertex cover, independent set, path cover, Dilworth) and *Segment tree graph*
- Number theory: *Floor blocks*
- Math: *Lattice polygons* (Pick's theorem)
- Various / dynamic programming: *Slope trick*

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
`LinkCutTree`, `DirectedMST`, `GeneralMatching`, `BumpAllocator` (nothing printed needs it any more since `LazySegTree` replaced `LazySegmentTree`; only the unprinted `SmallPtr` does).

## Removed after the team review (2026-10-30)

The team went through every entry (`entries - nx_entries.csv`); these were judged too trivial or already memorized.
As above, code files stay in the repository with the `\kactlimport` line commented out; the text sections are deleted from `chapter.tex`.

| Chapter | Entry | Lines | Reason |
|---|---|---:|---|
| contest | `.vimrc` | 6 | no vim user |
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
| data-structures | `LazySegmentTree.h` | 66 | merged into `LazySegTree` (file deleted; the generic tree with an edit block does the same, `HLD` ported) |

Still open (edit / merge / undecided): see `TODO.md`.

## Existing files that were modified

| File | Change |
|---|---|
| `content/data-structures/UnionFindRollback.h` | optional parity argument `join(a, b, w)` and `par(x)`; old calls behave as before (`DirectedMST` test passes) |
| `content/contest/template.cpp` | removed `cin.exceptions(cin.failbit);` (it makes `while (cin >> x)` throw at EOF) |
| `stress-tests/utilities/template.h` | includes `<cassert>`, which GCC 16's `<bits/stdc++.h>` no longer does |

## New stress tests (all pass; each was mutation-checked)

`IntervalMap`, `DynCon`, `PersistentSegmentTree`, `CentroidDecomposition`, `DsuOnTree`, `SuffixAutomaton`,
`HalfPlane`, `MinkowskiSum`, `LinearSieve`, `ExLucas`, `XorBasis`, `LazySegTree` (4 tests: beats block, affine, clamp, min query), `RectangleUnion`, `PolyOps`,
`SolveLinearMod`, `Binomial`, `LagrangeInterpolation`, `PrimitiveRoot`, `LiChao`, `BlockCutTree`, `PalindromicTree`
(in `stress-tests/<chapter>/`). The whole suite (`make test`) passed 101/101 before `ExLucas` (added by a teammate, with its own test) and the removals below; not re-run since.

## Things to know

- `PolyOps.h` and `NumberTheoreticTransform.h` use the modulus 998244353, while `ModPow.h`, `SolveLinearMod.h`,
  `ExLucas.h`, `LagrangeInterpolation.h` use the global `mod` of `ModPow.h` (default 10^9+7). Set `mod` once when
  mixing them, as with the other KACTL number-theory files.
- The page limit of the Danang contest was assumed to be KACTL's (25 pages + cover). Please check the rules.
- The cover page (`content/kactl.tex`) now names the NTU team.
- On GCC 16 or newer, add `#include <cassert>` to the contest template if you use `assert`.
