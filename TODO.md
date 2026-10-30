# TODO (from the team review, `entries - nx_entries.csv`)

Book is at 24 pages (cover + 23) after the deletions. Everything below is still open.

## Applies to all code
- [ ] Every kept code file has to be edited to match the new `template.cpp` (macros, `ll`, etc.), once that is final.

## Contest
- [ ] `template.cpp`: add / remove macros.
- [ ] `.bashrc`: change the compile command, remove `xkeymodmap`.
- [ ] `hash.sh`: improve usability.

## Math
- [ ] Derivatives/Integrals: delete integration by parts (memorized).
- [ ] Sums: keep only the sum of 4th powers (others memorized).
- [ ] Series: keep ln and sqrt only; maybe merge into one section to save lines.

## Numerical
- [ ] Add code: Bostan-Mori (nth term of a linear recurrence).

## Data structures
- [ ] Merge `LazySegmentTree.h` and `LazySegTree.h` into one lazy segment tree that supports queries better.

## Combinatorial
- [ ] Add code: RadixConversion.
- [ ] `IntPerm.h`: add "integer to permutation", or delete (undecided).

## Number theory
- [ ] Add text: Garner (CRT for many moduli).

## Graph
- [ ] `LCA.h`: undecided, binary lifting can already do LCA.

## Various
- [ ] `BumpAllocator.h`: delete later. `LazySegmentTree.h` and `HLD.h` still include it, so reformat those first (the merged lazy segment tree may remove one of them).

## Category to decide (`???`)
- [ ] Add text: Ordinary and Exponential Generating Functions.

## Not from the CSV
- [ ] Check the Danang page limit in the contest rules (assumed 25 pages + cover; we are at 23 + cover).
- [ ] Re-run `make test` (not re-run after the removals and `ExLucas`).
- [ ] With the space freed, decide what to add back or add new (candidates: the 23+8 cut files listed in `CHANGES-vs-original.md`).
