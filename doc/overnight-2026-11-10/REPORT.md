# Overnight report (2026-11-10): items 20 and 21

Proposals only: **nothing in the book changed**. Every proposal can be applied with one command (below) and was built
and checked. All numbers are measured.

## TL;DR

| Book | Pages |
|---|---:|
| Now | 26 |
| Descriptions G (gentle) | 25 |
| Descriptions L (lean, your rule) | **24** |
| Descriptions M (minimal) | **24** (plus about 1 column spare) |

Any techniques list below fits in the same count. G, L and M are the three versions of your item 21 rule, from "most
readable" to "most space". The techniques list now has three sizes (essential 0.9 column, core 1.3, all 1.9;
now 2.35), each with or without a short hint per line. The hints cost no lines.

Checks: 0 overfull boxes, no overlaps or orphan titles (`layout-check.py`) in every build. All 124 hashes and line
counts are unchanged; the code comments added by L and M are ignored by `hash.sh`. On the M version (which contains every
code comment L adds), `make test` passes 133/133 and `make test-compiles` 155/155, also with `LLINT=1`.

## Update 2026-11-10 (evening): level H, "hybrid"

Question from the team: is L just G with parts moved into code comments? **No.** L cuts content as well (for example
FenwickTree's "`query(pos)` sums [0, pos)" is gone and many hints shrink to a few words); only 11 files got comments.
So there is now a fourth level, **H**: the content and hints of G, but a fact that belongs to one function moves into a trailing
comment on its signature line (up to 63 columns, so no line is added and the hash does not change). Indexing and other
conventions stay in the description, as the team asked (FenwickTree: "0-indexed." is in the description; in L it is only a
code comment, which goes against that rule: say if L should be changed).

- 41 files get comments, e.g. `vl polyInv(vl a, int n) { // a[0] != 0`, `ll query(int x) { // INF if no line covers x`,
  `bool join(int a, int b, int w = 0) { // par(a)^par(b) = w`; the other 85 files are exactly G.
- With the wild techniques: **25 pages** (G 25, L 24). Space saved against G: 139pt; L saves 623pt.
- Same checks as the others: 0 overfull, no overlaps; all 124 hashes identical to the current book; `make test` 133/133 and
  `make test-compiles` 155/155, also with `LLINT=1`.
- Files: `diffs/21-H-descriptions.diff`, `preview-21H-with-techniques-wild.pdf`, columns H in `descriptions-21.csv`, source
  `tools/hyb21.py` (one entry per file; `python3 tools/apply21.py H`).

## Item 21: descriptions

Read **`descriptions-21.md`**. For each of the 126 files it shows the current text and the G, L and M proposals side by
side, plus any Usage/Time change and any code comment move. `preview-21-{G,L,M}.pdf` are the three books, with the
current techniques page.

| Level | What it keeps | Saved | Pages |
|---|---|---:|---:|
| G, gentle | A few words of what the file does, plus everything needed to use it | 1149pt (2.1 columns) | 25 |
| L, lean | Your rule: conventions, indexing, preconditions and interface. Non-trivial topics keep a few words of what they do. Facts that fit as trailing code comments move there | 1764pt (3.2 columns) | 24 |
| M, minimal | The least that still lets you use the file. Some Usage examples shortened. The two text-only files (`MinCut.h`, `MaximumIndependentSet.h`) are folded into `Dinic.h` and `MaximumClique.h` | 2204pt (4.0 columns) | 24, about 1 column spare |

Examples, by your rule:
- **FenwickTree:** L moves "0-indexed" into a code comment (`struct FT { // 0-indexed`) and keeps one line,
  "`lower_bound` needs non-negative values". M drops even that line.
- **HLD:** L says "Performs HLD. Full adjacency list, root 0; ops use `LazySeg`'s `L` / `S`. `VALS_EDGES`: values on edges."
- **NTT:** L says "Convolution mod 998244353 (or a prime 2^a b + 1, result size ≤ 2^a). Inputs in [0, mod)."

**Code comment moves** (L and M) go into 11 files: SegmentTree, PersistentSegmentTree, UnionFindRollback, LineContainer,
LiChao, FenwickTree, FenwickTree2d, XorBasis, euclid, MinimumVertexCover and PolygonArea. Each is a trailing comment on an existing line,
up to 63 characters, so no line is added and no hash changes.

**Time lines** are shortened in a few places in L/M (Fenwick, Fenwick2D, 2-SAT, MaximumClique, AhoCorasick). LazySegTree's
Time line gains the beats bound that the L/M description drops.
Dinic's complexity moves from the description into its Time line at every level.

**One general fix rides along in all three diffs.** Denser pages put more file names into one page header, and on one
page it overflowed again. The header font now scales with the length (10pt up to 120 characters, then smaller,
minimum 5pt).

**You can mix per file.** Edit `tools/desc21.py` (one entry per file) and rerun
`python3 doc/overnight-2026-11-10/tools/apply21.py L` from a fresh checkout. The script works on the checkout it runs in.

Caveat: L fills its last body page exactly (2pt spare). It is still 24 pages, but the next line added anywhere makes
the body 24 pages and the book 25. That is still well under 26.

## Item 20: techniques

**Update (team decision, 2026-11-10):** the techniques page is the place to go wild; the team is willing to lose a page for
it. So the maybe items (B) and the niche-but-advanced items (new level **C**, 63 entries, each with a hint) go in:
`techniques-wild-hints.txt`, 180 entries in 15 groups, 195 lines. It fills one page (2.87 of 3 columns), so no page is
lost after all: 26 pages with today's descriptions, 24 with L (`preview-21L-with-techniques-wild.pdf`). Left out on
purpose, as they are not algorithms: endianness, theory of computation, Shell sort, Timsort, tournament sort, and the
bare headings groups / rings / fields (Schreier-Sims is in). Two KACTL entries kept without a hint because their meaning
is unclear: "Lovasz toggle" and "Finding interesting points in N log N".

The original proposal follows.

Read **`techniques/techniques-worksheet.md`**. It contains:
- **The proposed list:** 117 entries in 13 groups, marked A (keep), B (maybe) and A* (essential), each with a hint.
- **Every line of the current page and the OI-wiki list:** each with a verdict (kept, maybe, in the template,
  trivial, niche) and, when kept, the entry that covers it.

Rule applied: keep what is hard to see from the statement but clicks once named; drop what the template already has
(code or a text note) and what is trivial for us.

| Source | Kept | Maybe | In the template | Trivial | Niche |
|---|---:|---:|---:|---:|---:|
| Current techniques.txt (140 entries) | 18 | 12 | 59 | 41 | 10 |
| OI-wiki list (346 entries) | 44 | 24 | 128 | 74 | 76 |

43 of the 117 entries are new, from neither list. Examples: contribution technique, reverse the process,
Manhattan to Chebyshev, swap DP state and value, min-plus matrix power, Kruskal reconstruction tree, complement BFS,
regret greedy, bit by bit from the top, Zobrist hashing, Kummer's theorem.

Three sizes, each with or without hints (`techniques/techniques-*.txt`):

| File | Entries | Lines | Columns |
|---|---:|---:|---:|
| `essential-*` | 48 | 61 | 0.9 |
| `core-*` | 73 | 86 | 1.3 |
| `all-*` (core plus maybe) | 117 | 130 | 1.9 |
| current page | | 159 | 2.35 |

A hinted line looks like `Residue Dijkstra: reachable sums: dist[r mod a_min]`, always one line. I recommend the hinted
version: the hint is what makes the name click.

To use a list:

```bash
cp doc/overnight-2026-11-10/techniques/techniques-core-hints.txt content/appendix/techniques.txt
```

Judgment calls worth a look:
- **Aliens trick (WQS):** in core and essential, although the team deleted its 3-line text note as trivial. The one
  line here is a name and a trigger; drop it if it's still trivial for you.
- **Knuth optimization:** kept. `KnuthDP.h` exists in the repo but is not printed.
- **Basics:** binary search the answer, complement counting, inclusion-exclusion, stars and bars, small to large and
  Euler tour flattening are **B** (maybe). They're standard for us but sometimes the missing idea.
- **Dropped as niche:** e.g. Min_25 sieve, Lagrange inversion, chordal graphs, top tree, the balanced-tree zoo, 3D
  geometry, simplex.

## How to apply

```bash
git apply doc/overnight-2026-11-10/diffs/21-L-descriptions.diff
```

The diffs are `21-G-descriptions.diff`, `21-L-descriptions.diff` and `21-M-descriptions.diff`; each applies to the
branch as it is now. Add a techniques file with the `cp` command above, then run:

```bash
make kactl
```

```bash
python3 doc/overnight-2026-11-09/layout-check.py kactl.pdf
```

## Files

- `REPORT.md`: this file.
- `descriptions-21.md`: all 126 descriptions, current against G / L / M.
- `diffs/21-{G,L,M}-descriptions.diff`
- `preview-21-{G,L,M}.pdf`: the three description levels with the current techniques page.
- `preview-21L-with-techniques-wild.pdf`: L plus `techniques-wild-hints.txt` (24 pages).
- `techniques/`: the worksheet and the six techniques variants.
- `tools/`: `desc21.py` (the proposals as data), `apply21.py` (applies a level), `gen21doc.py` (regenerates
  `descriptions-21.md`).
