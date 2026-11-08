# TODO (from the team review, `entries - nx_entries.csv`, and the coverage audit)

State (2026-11-09): the book is 26 PDF pages (cover + 25), the Danang limit is 26 (25 + cover). `troubleshoot.txt` was cut on 2026-11-09 (the pages just reflowed:
still 26, still full). **The team temporarily allows the book to grow to 27 pages** while the code items (Lucy/Du, `polyPow`, ModInt) are added; the overflow
is then removed again, mainly by the techniques page rework (370 candidate lines vs 159 now) and small trims. The final book must be at most 26 pages.

## Standing rules (so every item below can be done without asking)
- **Page cap:** the final book must be at most 26 PDF pages; until the techniques rework it may temporarily be 27 (team decision 2026-11-09); aim for 26 or fewer with a few lines to spare. Rebuild with `make kactl` after every item and check
  the count (`Output written on build//kactl.pdf (N pages ...)`). If something does not fit, pay for it in this order: cleanup items,
  then the lowest-value new item (move it to "Deferred" here and say so in the report). Never drop an entry the team marked Keep without telling them.
- **Code:** every new or changed code file gets a stress test in `stress-tests/<chapter>/` that is mutation-checked, passes `make test` and
  `LLINT=1 make test` (with `#define int long long`), and `make test-compiles` in both modes. Library rules for both modes: `(int)(x)` not `int(x)`,
  `max<int>(x, 0)` not `max(x, 0)`, wrap `#include <bits/extc++.h>` in `push_macro("int")` / `#undef int` / `pop_macro("int")`, tests use `signed main`.
- **Judge facts:** the judge is Ubuntu 24.04; its Python is CPython 3.12.3 and PyPy 7.3.15 (Python 3.9.18). Both are installed in the working container (`/usr/bin/python3.12`, `/usr/bin/pypy3`), so Python claims are tested on the real interpreters. Python code and notes must work on both (PyPy: no 3.10+ syntax or `math.cbrt`; deep recursion needs a big-stack thread).
- **Text notes:** every formula is checked before it goes in: add a small script to `doc/note-checks/` (python3 or C++, run all with `doc/note-checks/run-all.sh`, not part of `make test`). Build the book with `make kactl < /dev/null` (a LaTeX error otherwise hangs on a prompt) and write `\&` for `&` in `Usage:` lines.
- **Style:** lines at most 63 characters (tab = 2), header with Author / Date / License CC0 / Description / Time / Status; text notes in the
  matching `chapter.tex`, short, formulas over prose. New code uses the macros of `content/contest/macros.cpp` (`rep all sz pb ll pii vi`).
- **After each item:** update this file, `CHANGES-vs-original.md`, `entries - nx_entries.csv`, `summary.md` if conventions change; rebuild
  `kactl.pdf`; commit with the Co-Authored-By / Claude-Session lines and push to `vn-icpc-danang-2026-fill` (`git fetch` first; teammates push too).
- **Team decisions already made:** Aliens trick, Knuth DP and game theory are memorized (not added); Simplex stays cut; `PushRelabel` stays
  (O(V^3) on complete graphs); `LCA.h` stays together with `BinaryLifting.h` (`CompressTree` needs it, O(1) queries); `.bashrc` is cut; the
  optional / nice-to-have ideas at the bottom are skipped for now; nothing from the cut files is added back except what is listed here.

## Ready: spec decided, do these without asking (suggested order)
Cleanup first (frees about 65 lines), then additions, cheapest and most useful first.
1. [x] **Cut `BumpAllocator.h`** (done 2026-11-08) (decided): comment out its import in `content/various/chapter.tex`, add it to the cut table in `CHANGES-vs-original.md`
   and the CSV; the file stays in the repo. Frees about 19 lines.
2. [x] **Drop `DFSMatching.h`** (done: `MinimumVertexCover` uses `hopcroftKarp`; its test keeps `DFSMatching.h` as an oracle for the matching size): point `MinimumVertexCover.h` at `HopcroftKarp.h` (same signature; its stress test already includes it), comment out
   the import of `DFSMatching.h`, record the cut. Frees about 38 lines. Re-run the `MinimumVertexCover` test.
3. [x] **Remove the empty headings** (done: the four headings are commented out, the commented imports stay under them) that print with nothing under them: graph "Fundamentals" and "Coloring", number theory "Fractions",
   geometry "3D" (check in the built PDF that nothing is left under them first).
4. [x] **`lineDistance.h`** (done): remove the mentions of `Point3D` (the 3D files are cut).
5. [x] **`CHANGES-vs-original.md` cut table** (done, corrected: the 8 files turned out to be unprinted in the original KACTL too, so they are noted in a separate sentence, not listed as cuts; totals stay 23 files / 973 lines).
   `Hashing-codeforces`, `MatrixInverse-mod`, `Eratosthenes.h`, `Euclid.java`, `Unrolling`.
6. [x] **Segment tree descent** (done: `maxRight`, 12 lines; mutation-checked in the default, clamp and min tests) (`LazySegTree.h` body, about 10 lines): `template<class F> int maxRight(int l, F f)` returning the largest `r`
   such that `f(query(l, r))` holds (`f(e())` must hold), O(log N), AtCoder style; mention it in the description with a usage line.
   Test against brute force with the default block (sum / max predicates) and with the affine block. The block file stays unchanged.
7. [x] **Lazy implicit treap** (done: `Treap.h` with lazy add / reverse / sum and `go`; `val` is `ll`; new `TreapLazy` test, 10 mutations caught) (`Treap.h`, about +10 to 15 lines): lazy range reverse and range add, with subtree `sum`; keep the existing API
   (`split`, `merge`, `each`, ...); add `push` and make `split` / `merge` call it. Test against a plain `vector` with random operations.
8. [x] **`IntPerm.h`: add integer -> permutation** (done: `IntPerm.h` is now the lexicographic rank, widened to `ll`, with `intToPerm`; order preserving, exact for n <= 20; plus, by the team's choice C, `radixToPerm` / `permToRadix` in `RadixConversion.h`, a bijection between all digit sequences and all permutations; `mulAdd` is shared with `radixconv`) (decided). **It must be an exact bijection with `permToInt`:** `intToPerm(permToInt(p), n) == p`
   for every permutation and `permToInt(intToPerm(r, n)) == r` for every `r < n!`; test exhaustively for n <= 8 and randomly for larger n.
   Note `permToInt` is not order preserving; `intToPerm` has to invert exactly that mapping (about 8 lines). Update the description.
9. [x] **Text: matrix-tree note** (done: Graph / Math subsection, checked by `doc/note-checks/check_graph.py`) (Graph, where the old "Number of Spanning Trees" section was; the stress test `matrix-tree.cpp` still exists):
   Kirchhoff (minor of the Laplacian), directed version (rooted arborescences: in / out degree Laplacian), BEST theorem (number of Eulerian
   circuits), Lindstrom-Gessel-Viennot lemma. About 6 lines.
10. [x] **Text: Garner** (done: Number theory, checked by `check_numbertheory.py`) (Number theory): CRT for many moduli as mixed radix, `x = x1 + x2 m1 + x3 m1 m2 + ...`, the formula for each `x_i` with the
    inverse of `m1 ... m(i-1)` mod `m_i`, evaluate mod `M`; a few lines of code-like pseudocode. About 6-8 lines.
11. [x] **Text: generalized Euler, LTE, linear Diophantine** (done: "Exponents" subsection, and the Diophantine part extends the Bezout text; checked by `check_numbertheory.py`) (Number theory): `a^b mod m` for huge `b` (`b >= log2 m`), lifting-the-exponent lemma
    (odd and `p = 2`), solutions of `ax + by = c` in a range (`x0 + (b/g) t`, counting with floor / ceil). About 6 lines.
12. [x] **Text: ordinary and exponential generating functions** (done: Combinatorial, about 1.1 columns: dictionary table, common series, counting structures, computing; checked by `check_gf.py`) (Combinatorial, the old `???` category): definitions, operations (sum, product /
    binomial convolution, derivative, shift, composition with exp / log), standard series, recipes (sequences `1/(1-A)`, sets `exp(A)`, cycles `log`),
    one or two worked counting examples. About 12-15 lines.
13. [x] **Text: suffix array / suffix automaton identities** (done: Strings, new section; checked by `check_strings.cpp`, which also confirmed that the generalized automaton only needs `last = 0` per string) (Strings): `lcp(i, j)` as a range minimum over the lcp array, distinct substrings
    `n(n+1)/2 - sum lcp`, k-th substring, occurrence counts along suffix links, generalized SAM (reset `last` per string). About 5 lines.
14. [x] **Contest / Various: C++ pitfalls list and `__int128` print** (done: Various, new section "C++ pitfalls" with 12 bullets, each reproduced by `doc/note-checks/check_pitfalls.py`; `Int128.h` is a hashed, stress-tested code file; one correction found by the check: `1 << 31` is well defined since C++14, the undefined behaviour starts at `k >= 32`) (about 12 lines): `1 << 31` (use `1LL <<`), `abs(INT_MIN)`, `size() - 1` underflow,
    comparators that are not strict weak orders (`<=` crashes `sort`), negative `%`, printing `-0.0`, `vector<bool>` quirks, `endl` / flush on interactive
    problems, stack limit on deep recursion, uninitialized locals and globals not cleared between tests, `max(int, ll)` mixing, anti-hash tests for
    `unordered_map`; plus a 3-line `__int128` output function (tested).
15. [x] **Python tricks (big integers)** (done: Various, new last section "Python", checked on both judge interpreters, CPython 3.12.3 and PyPy 7.3.15 = Python 3.9.18, by `doc/note-checks/check_python.py`) (Various, text, about 12 lines; the team uses Python mostly for big integers). Include only what is verified
    on the installed Python (3.13); the wiki's `lang/python.md` is a beginner tutorial and is not a source for this: `math.isqrt`, `gcd`, `lcm`, `comb`, `perm`, `factorial`, `prod`, `pow(a, b, m)` and `pow(a, -1, m)`, `divmod`,
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

19. [ ] **Edit ModInt** (the team pasted their template; saved verbatim in `doc/modint-team-template.cpp`). Replace the global-`mod` `struct Mod` in
    `content/number-theory/ModularArithmetic.h` with this `template <int mod> struct mint` (+ `using mi = mint<M>; using vmi = vector<mi>;`), keeping its
    API (`+ - * /`, `+= -= *= /=`, `++ --`, unary `-`, `== != <`, `>> <<`, `fpow`, `inverse`, explicit `int`). Required changes: (1) it has two functional casts,
    `int(a)` in `operator<<` and `int((ll)v * o.v % mod)` in `operator*=`, which **do not compile under `#define int long long`**; write `(int)(...)`, and
    check `-Wconversion` is clean in both modes; (2) the header no longer needs `euclid.h` (inverse is Fermat, so `mod` must be prime; say so); (3) add a
    stress test against plain `%` arithmetic (all operators, negative inputs, `mod - 1`, division, `fpow` with large exponents, `>>`/`<<`) in both modes;
    (4) update the description and usage line (`using mi = mint<998244353>` etc.), and check whether other headers can use it. Fixed `mod` for the
    shared-`mod` item below stays a separate decision (template parameter does not clash with the global `const ll mod` of other headers).
20. [ ] **Techniques worksheet** (prepares the rework above, no questions needed): write `doc/techniques-worksheet.txt` from the zip's 370-line list: one
    entry per line, marked `keep`, `?` or `drop` with my suggestion (drop: trivial sorting / basic techniques / language items / things the team already
    remembers; keep: named techniques that are error-prone or easy to forget), a short reason where it is not obvious, and a count of how many lines the
    `keep` entries add up to against the one-page budget (about 155 lines). The team edits the marks; then regenerate `content/appendix/techniques.txt`.

## Blocked: needs the team or you (do not start these)
- [ ] **Edit Fenwick Trees** (your template). Not decided: the team first has to answer (a) is `FenwickTree.h` 0- or 1-indexed (it is 0-indexed:
  `update(pos, dif)` and `query(pos)` = sum of `[0, pos)`; the confusion is probably about this, so a clearer description / usage line may be
  all that is wanted) and (b) what to do about `FenwickTree2d.h`, which is "really weird" because it needs `fakeUpdate()` for every updated cell before
  `init()` (offline). Options once known: a plain 2D BIT with fixed size, or the offline version with a clearer interface.
- [ ] **One shared `mod`** (six headers define their own `const ll mod`: `ModInverse`, `ModPow`, `ModularArithmetic`, `IntDeterminant`,
  `LinearRecurrence`, `NumberTheoreticTransform`, so two of them cannot be included together; `BostanMori.h` and `PolyOps.h` are in `skip_headers`
  and their tests use a namespace hack because of it). Decided to wait for the ModInt rewrite (item 19); after it, check how many headers still define their own `mod` and ask only if the choice is not obvious.
- [ ] **Rework `techniques.txt`** (159 lines, one page, stale after the cuts). Source: the content dump of the OI Wiki translation the team uploaded
  (`oiwiki-content.zip`: 452 markdown pages in 14 sections, 453 `.cpp` examples, 450 `.in` / `.ans` test pairs). **The zip is enough; the live site is
  not needed** (it never resolved from the session, and the `icpc-template` environment created for it can be ignored). The zip also has a ready-made
  `techniques.txt` in our format: **370 lines, 23 sections** (the wiki's whole table of contents; ours is 159 lines), so it has to *shrink* by about 55%
  to stay near one page. Only 66 of our 158 entry names match exactly (different wording). Roughly 78 of its lines are in sections that are mostly
  basic or niche for the team (Sorting 14, Algorithm analysis 3, Basic techniques 13, Topics 5, Miscellaneous 13, Abstract algebra 5, Probability 5,
  Other math 5, Offline algorithms 10, Randomization 5). Licence: the wiki is CC BY-SA 4.0 + SATA, so use it for topic names and as a reference only;
  do not copy its text or code into the book or the repo. Next step (ready, see item 20): a worksheet. Blocked on: the team's marks in the worksheet.

## Deferred / ideas (skipped for now by the team's decision)
Stable marriage, min mean cycle (Karp), Steiner tree DP, tree isomorphism hashing, Lyndon factorization, subset convolution, online (CDQ) convolution,
Mo with updates, circle union area, minimum-area bounding rectangle, 3D formulas as text, Fibonacci / Josephus identities.

## Done
- [x] `troubleshoot.txt` cut from the book (2026-11-09); the file stays, the import is commented out.
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
