# Vietnam ICPC configuration

This branch adapts KACTL for the Vietnamese ICPC rounds (target: ICPC Danang
Regionals 2026). The page budget is unchanged: `kactl.pdf` is 25 pages
(cover included), the same as before. These notes record what changed and why.

## Evidence

Problem sets read (statements, plus solve counts from the VNOJ rankings):
ICPC 2026 Central, North and South provincial mirrors and ICPC 2025 Regional
(<https://oj.vnoi.info/contests/>). Hardest problems (fewest solves) and what
they needed:

| Problem | Needs | Now covered by |
|---|---|---|
| 2025 Regional B | offline dynamic connectivity, bipartiteness | `DynCon.h`, parity in `RollbackUF` |
| 2025 Regional C | piecewise-constant profile, interval updates | `IntervalMap.h` |
| 2025 Regional G | floor sums, impartial game | Floor blocks, Sprague-Grundy notes |
| 2025 Regional J | min-cost flow with convex costs | note in graph chapter |
| 2026 North K | continuous k-median, accepted within tolerance | `HillClimbing.h` (kept) |
| 2026 North H | circle blocking a line of sight | `Angle.h`, `CircleTangents.h` (kept) |
| 2026 South G | tree radius reachability, SCC | `CentroidDecomposition.h`, `SCC.h` |
| 2026 South I | layer order from ranges | segment tree graph note, `TopoSort.h` |
| 2026 Central K | min flow with lower bounds | lower-bounds note, `Dinic.h` |
| 2026 Central B | game on a tree | Sprague-Grundy note |

## Added

`IntervalMap`, `DynCon`, `PersistentSegmentTree`, `CentroidDecomposition`,
`DsuOnTree`, `SuffixAutomaton`, `HalfPlane`, `MinkowskiSum`, `LinearSieve`,
`XorBasis`. Notes: flows with lower bounds, segment tree graph, floor blocks,
Sprague-Grundy, Pick's theorem. Every new header has a stress test in
`stress-tests/`.

## Changed

- `UnionFindRollback.h`: optional parity argument `join(a, b, w)` and `par(x)`;
  defaults keep the old behaviour (`DirectedMST` still passes its stress test).
- `IntervalContainer.h` is replaced in the book by `IntervalMap.h`
  (`IntervalMap<bool>` does the same job and also holds values).
- `Dinic.h` replaces `EdmondsKarp.h`; `PushRelabel` is kept.
- `contest/template.cpp`: dropped `cin.exceptions(cin.failbit)`, which makes
  `while (cin >> x)` throw at EOF.

## Removed from the book (files stay in the repo)

3D geometry (`3dHull`, `PolyhedronVolume`, `Point3D`, `sphericalDistance`),
`FastDelaunay`, `SIMD`, `SmallPtr`, `BumpAllocatorSTL`, `Tridiagonal`,
`PolyRoots`, `IntegrateAdaptive`, `GoldenSectionSearch`, `EdgeColoring`,
`SubMatrix`, `FastMod`, `SuffixTree`, `EdmondsKarp`.
`GomoryHu`, `GlobalMinCut`, `HillClimbing` and `CircleTangents` were kept on
purpose: they were first on the cut list and then turned out to be used.

## Running the tests

    make test                # all stress tests
    ./doc/scripts/test-compiles.sh content/graph/DsuOnTree.h   # one header

GCC 16 no longer includes `<cassert>` from `<bits/stdc++.h>`;
`stress-tests/utilities/template.h` includes it explicitly. The contest
template does not, so add `#include <cassert>` if you use `assert` on a new GCC.

## Open points

- Cover page (`content/kactl.tex`) still names KTH.
- The page limit for Danang was assumed to be KACTL's 25 pages; check the rules.
