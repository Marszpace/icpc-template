# TODO (from the team review, `entries - nx_entries.csv`, and the coverage audit)

State (2026-11-08): the book is 25 PDF pages (cover + 24). **The Danang page limit is 26 (25 + cover), confirmed by the team**,
so there is about one page of room (about 160 lines) plus what the cleanup items free.

## Standing rules (so every item below can be done without asking)
- **Page cap:** never go over 26 PDF pages; aim for 26 or fewer with a few lines to spare. Rebuild with `make kactl` after every item and check
  the count (`Output written on build//kactl.pdf (N pages ...)`). If something does not fit, pay for it in this order: cleanup items,
  then the lowest-value new item (move it to "Deferred" here and say so in the report). Never drop an entry the team marked Keep without telling them.
- **Code:** every new or changed code file gets a stress test in `stress-tests/<chapter>/` that is mutation-checked, passes `make test` and
  `LLINT=1 make test` (with `#define int long long`), and `make test-compiles` in both modes. Library rules for both modes: `(int)(x)` not `int(x)`,
  `max<int>(x, 0)` not `max(x, 0)`, wrap `#include <bits/extc++.h>` in `push_macro("int")` / `#undef int` / `pop_macro("int")`, tests use `signed main`.
- **Style:** lines at most 63 characters (tab = 2), header with Author / Date / License CC0 / Description / Time / Status; text notes in the
  matching `chapter.tex`, short, formulas over prose. New code uses the macros of `content/contest/macros.cpp` (`rep all sz pb ll pii vi`).
- **After each item:** update this file, `CHANGES-vs-original.md`, `entries - nx_entries.csv`, `summary.md` if conventions change; rebuild
  `kactl.pdf`; commit with the Co-Authored-By / Claude-Session lines and push to `vn-icpc-danang-2026-fill` (`git fetch` first; teammates push too).
- **Team decisions already made:** Aliens trick, Knuth DP and game theory are memorized (not added); Simplex stays cut; `PushRelabel` stays
  (O(V^3) on complete graphs); `LCA.h` stays together with `BinaryLifting.h` (`CompressTree` needs it, O(1) queries); `.bashrc` is cut; the
  optional / nice-to-have ideas at the bottom are skipped for now; nothing from the cut files is added back except what is listed here.

## Ready: spec decided, do these without asking (suggested order)
Cleanup first (frees about 65 lines), then additions, cheapest and most useful first.
1. [ ] **Cut `BumpAllocator.h`** (decided): comment out its import in `content/various/chapter.tex`, add it to the cut table in `CHANGES-vs-original.md`
   and the CSV; the file stays in the repo. Frees about 19 lines.
2. [ ] **Drop `DFSMatching.h`**: point `MinimumVertexCover.h` at `HopcroftKarp.h` (same signature; its stress test already includes it), comment out
   the import of `DFSMatching.h`, record the cut. Frees about 38 lines. Re-run the `MinimumVertexCover` test.
3. [ ] **Remove the empty headings** that print with nothing under them: graph "Fundamentals" and "Coloring", number theory "Fractions",
   geometry "3D" (check in the built PDF that nothing is left under them first).
4. [ ] **`lineDistance.h`**: remove the mentions of `Point3D` (the 3D files are cut).
5. [ ] **`CHANGES-vs-original.md` cut table**: add the missing unprinted files: `UnionFind`, `PolygonUnion`, `DelaunayTriangulation`,
   `Hashing-codeforces`, `MatrixInverse-mod`, `Eratosthenes.h`, `Euclid.java`, `Unrolling`.
6. [ ] **Segment tree descent** (`LazySegTree.h` body, about 10 lines): `template<class F> int maxRight(int l, F f)` returning the largest `r`
   such that `f(query(l, r))` holds (`f(e())` must hold), O(log N), AtCoder style; mention it in the description with a usage line.
   Test against brute force with the default block (sum / max predicates) and with the affine block. The block file stays unchanged.
7. [ ] **Lazy implicit treap** (`Treap.h`, about +10 to 15 lines): lazy range reverse and range add, with subtree `sum`; keep the existing API
   (`split`, `merge`, `each`, ...); add `push` and make `split` / `merge` call it. Test against a plain `vector` with random operations.
8. [ ] **`IntPerm.h`: add integer -> permutation** (decided). **It must be an exact bijection with `permToInt`:** `intToPerm(permToInt(p), n) == p`
   for every permutation and `permToInt(intToPerm(r, n)) == r` for every `r < n!`; test exhaustively for n <= 8 and randomly for larger n.
   Note `permToInt` is not order preserving; `intToPerm` has to invert exactly that mapping (about 8 lines). Update the description.
9. [ ] **Text: matrix-tree note** (Graph, where the old "Number of Spanning Trees" section was; the stress test `matrix-tree.cpp` still exists):
   Kirchhoff (minor of the Laplacian), directed version (rooted arborescences: in / out degree Laplacian), BEST theorem (number of Eulerian
   circuits), Lindstrom-Gessel-Viennot lemma. About 6 lines.
10. [ ] **Text: Garner** (Number theory): CRT for many moduli as mixed radix, `x = x1 + x2 m1 + x3 m1 m2 + ...`, the formula for each `x_i` with the
    inverse of `m1 ... m(i-1)` mod `m_i`, evaluate mod `M`; a few lines of code-like pseudocode. About 6-8 lines.
11. [ ] **Text: generalized Euler, LTE, linear Diophantine** (Number theory): `a^b mod m` for huge `b` (`b >= log2 m`), lifting-the-exponent lemma
    (odd and `p = 2`), solutions of `ax + by = c` in a range (`x0 + (b/g) t`, counting with floor / ceil). About 6 lines.
12. [ ] **Text: ordinary and exponential generating functions** (Combinatorial, the old `???` category): definitions, operations (sum, product /
    binomial convolution, derivative, shift, composition with exp / log), standard series, recipes (sequences `1/(1-A)`, sets `exp(A)`, cycles `log`),
    one or two worked counting examples. About 12-15 lines.
13. [ ] **Text: suffix array / suffix automaton identities** (Strings): `lcp(i, j)` as a range minimum over the lcp array, distinct substrings
    `n(n+1)/2 - sum lcp`, k-th substring, occurrence counts along suffix links, generalized SAM (reset `last` per string). About 5 lines.
14. [ ] **Contest / Various: C++ pitfalls list and `__int128` print** (about 12 lines): `1 << 31` (use `1LL <<`), `abs(INT_MIN)`, `size() - 1` underflow,
    comparators that are not strict weak orders (`<=` crashes `sort`), negative `%`, printing `-0.0`, `vector<bool>` quirks, `endl` / flush on interactive
    problems, stack limit on deep recursion, uninitialized locals and globals not cleared between tests, `max(int, ll)` mixing, anti-hash tests for
    `unordered_map`; plus a 3-line `__int128` output function (tested).
15. [ ] **Python tricks (big integers)** (Various, text, about 12 lines; the team uses Python mostly for big integers). Include only what is verified
    on the installed Python (3.13): `math.isqrt`, `gcd`, `lcm`, `comb`, `perm`, `factorial`, `prod`, `pow(a, b, m)` and `pow(a, -1, m)`, `divmod`,
    `int.bit_length`, `sys.set_int_max_str_digits(0)` (int <-> str conversion is limited to 4300 digits since 3.11), `decimal` (`getcontext().prec`,
    `sqrt`, `ln`, `exp`, `quantize`, rounding modes), `fractions.Fraction`, fast input via `sys.stdin`, `sys.setrecursionlimit` with a thread for stack.
16. [ ] **Lucy_Hedgehog and Du sieve** (Number theory, about 40 lines, pairs with the Floor blocks text): prime counting and prime sums up to about
    1e11 in O(n^(3/4)); prefix sums of phi and mu in about O(n^(2/3)). Test against a sieve up to 1e7 and the known value pi(1e11) = 4118054813.
17. [ ] **`polyPow`, `polySqrt`, `polyDivMod` in `PolyOps.h`** (about 20 lines): `polyPow(a, k, n)` must handle leading zeros and huge `k`,
    `polySqrt(a, n)` for `a[0] = 1`, `polyDivMod(a, b)` via `polyInv` of the reversed polynomials. Test against naive O(n^2) versions.
18. [ ] **Tests for the gaps**: first list which printed files have no coverage at all (the audit only compared file names; `HashMap`, `Manacher`,
    `Matrix`, `BiconnectedComponents`, `OrderStatisticTree`, `kdTree`, `Angle`, `IntervalCover`, `DivideAndConquerDP`, `UnionFindRollback`,
    `Polynomial`, `PolyInterpolate`, `Integrate`, `HillClimbing`, `TernarySearch`, `Determinant`, `MatrixInverse`, ... may be covered indirectly);
    then write stress tests for the non-trivial ones and fix any bug found. `GeneralMatching` ("not very well tested") and `Integrate`
    ("mostly untested") are in scope. Report the list at the end.

## Blocked: needs the team or you (do not start these)
- [ ] **Edit Fenwick Trees** (your template). Not decided: the team first has to answer (a) is `FenwickTree.h` 0- or 1-indexed (it is 0-indexed:
  `update(pos, dif)` and `query(pos)` = sum of `[0, pos)`; the confusion is probably about this, so a clearer description / usage line may be
  all that is wanted) and (b) what to do about `FenwickTree2d.h`, which is "really weird" because it needs `fakeUpdate()` for every updated cell before
  `init()` (offline). Options once known: a plain 2D BIT with fixed size, or the offline version with a clearer interface.
- [ ] **Edit ModInt** (your template): you will paste your version; then adapt `ModularArithmetic.h` to it and test it.
- [ ] **One shared `mod`** (six headers define their own `const ll mod`: `ModInverse`, `ModPow`, `ModularArithmetic`, `IntDeterminant`,
  `LinearRecurrence`, `NumberTheoreticTransform`, so two of them cannot be included together; `BostanMori.h` and `PolyOps.h` are in `skip_headers`
  and their tests use a namespace hack because of it). Decided to wait for the ModInt rewrite.
- [ ] **Rework `techniques.txt`** (159 lines, one page, stale after the cuts): replace its content with the non-trivial entries of
  https://en-oi-wiki.marszpace.dev/ (the English translation of oi-wiki.org). It may shrink or grow, and a lot of techniques are trivial for the team,
  so the team lists what goes in. Blocked on (a) the host: it did not resolve from this session even after a personal environment `icpc-template` with
  `en-oi-wiki.marszpace.dev` on its allowlist was created and this session was switched to it (the proxy can take up to an hour to pick it up); if it still
  fails in a new session, add the host under the environment's network settings; (b) the team's list. Then draft a candidate list from the wiki for the team
  to cross out.

## Deferred / ideas (skipped for now by the team's decision)
Stable marriage, min mean cycle (Karp), Steiner tree DP, tree isomorphism hashing, Lyndon factorization, subset convolution, online (CDQ) convolution,
Mo with updates, circle union area, minimum-area bounding rectangle, 3D formulas as text, Fibonacci / Josephus identities.

## Done
- [x] Danang page limit: 26 (25 + cover), confirmed by the team on 2026-11-08.
- [x] Every kept code file matches the new `macros.cpp` and also works with `#define int long long` (`LLINT=1 make test` / `LLINT=1 make test-compiles`).
- [x] `template.cpp` -> `macros.cpp` (macros and typedefs only, new macro `pb`; the define is not in the file).
- [x] `.bashrc` cut (the team uses VS Code); `hash.sh` takes a file (`./hash.sh file.cpp`); `stress.sh` and `interactive.sh` (with tests in
  `doc/scripts/test-contest-scripts.sh`).
- [x] Math: integration by parts deleted, sums reduced to 4th powers, series reduced to ln and sqrt.
- [x] Lazy segment trees merged: `LazySegTreeBlock.h` + `LazySegTree.h` (default block: chmin + add beats), `HLD` ported.
- [x] New code: `RadixConversion.h` (bijective base conversion), `BostanMori.h` (n-th term in O(n log n log k)).
- [x] `make test` 104/104 and `make test-compiles` 152/152, with and without `#define int long long`.
- [x] SOS DP note (Various).
