# Additions test (2026-11-15)

Preview only: **the book (`content/`, `kactl.pdf`) is unchanged.** This folder shows what the book looks like with the
items from the "risky cuts" and "never included" lists added.

## Result

**Everything does not fit: 27 pages**, about 0.8 of a column (427pt) over the 26-page limit. Dropping one item fits.

| Preview | Pages | Room left within 26 pages |
|---|---:|---:|
| Today's book (`kactl.pdf`) | 25 | 3085pt (5.5 columns) |
| `preview-all.pdf`: everything | **27** | -427pt (-0.8 columns) |
| `preview-no-simplex.pdf`: everything but `Simplex` | 26 | 548pt (1.0 column) |
| `preview-no-3d.pdf`: everything but the 3D trio | 26 | 593pt (1.1 columns) |

The additions take about 3500pt (6.3 columns). Small trims do not help. A file never splits across columns, so the
space a file takes depends on where the column breaks fall after it. Turning 4 comment lines in `Point3D` into
trailing comments changed nothing (still -427pt). Measured by building the book without each item:

| Dropped from "everything" | Pages |
|---|---:|
| `Point3D` + `3dHull` + `PolyhedronVolume` | 26 |
| `Simplex` | 26 |
| `MatrixInverse-mod` | 26 (but `GeneralMatching` needs it) |
| `DominatorTree` | 26 |
| `SubsetConvolution`, `PolygonUnion` or `CircleUnion` | 26 (only about 45pt left) |
| `IntegrateAdaptive` or `ChromaticNumber` | still 27 |

These numbers were measured before 4 new headers were reflowed to fit the column width. Afterwards the no-Simplex
build has 548pt left (before: 141pt), so they may have shifted a little.

Checks on all three previews: 0 overfull boxes, no orphan titles (`layout-check.py`).

## What was added

| Item | Lines printed | Status |
|---|---:|---|
| `MatrixInverse-mod.h` (restored) | 37 | already tested; **`GeneralMatching` includes it, but the book does not print it** |
| `Simplex.h` (restored) | 68 | **new test**: all vertices by brute force over 20000 random LPs (6750 infeasible, 6686 unbounded, 6564 bounded), plus the Usage example |
| `IntegrateAdaptive.h` (restored) | 15 | **new test**: exact integrals (kinks, sqrt end, Gaussian, nested), random polynomials, evaluation count |
| `Point3D.h`, `3dHull.h`, `PolyhedronVolume.h` (restored, new 3D section) | 31 + 49 + 6 | **new test**: hull faces and volume against brute force (all triples), outward normals, ccw order, `rotate` / `phi` / `theta` |
| `PolygonUnion.h` (restored; never printed, even in the original KACTL) | 33 | already tested |
| `DominatorTree.h` (new) | 39 | **new test**: brute force (remove each vertex, check reachability) on 20000 random graphs, 200000-vertex path |
| `ChromaticNumber.h` (new) | 17 | **new test**: brute force over all colourings, complete graphs up to K20, odd / even cycles |
| `SubsetConvolution.h` (new) | 16 | **new test**: brute force over all subsets, with 3 moduli, plus size 2^20 (about 1s) |
| `CircleUnion.h` (new) | 33 | **new test**: numeric integration (Gauss-Legendre between all critical x) on 3000 random sets with duplicates, nested and tangent circles, r = 0; plus exact cases |

The descriptions of the restored files were shortened to the book's level H style. Every new test was mutation-checked;
survivors were either equivalent mutants (e.g. flipping the sign of a sum that is only tested for zero) or led to a
stronger test.

Full suites on this content: `make test` 139/139 and `make test-compiles` 161/161, also with `LLINT=1`. The suites ran
before the 4 new headers were reflowed to fit the column width; after that, their tests were rerun in both modes and
each header was compiled on its own.

## Files

- `preview-all.pdf`, `preview-no-simplex.pdf`, `preview-no-3d.pdf`
- `additions.diff`: everything (headers, chapter imports, tests). Applies to the branch as it is now:

```bash
git apply doc/additions-2026-11-15/additions.diff
```

For a variant, comment out the imports you don't want in `content/<chapter>/chapter.tex`, then run `make kactl`.
