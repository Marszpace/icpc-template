# Project summary (for a future Claude Code instance)

## What this repo is
A fork of KACTL (KTH's ICPC team reference document) for the user's team (NTU, "Domain Expansion: Infinite Penalty"),
for the Vietnam / Danang 2026 ICPC contest. Branch: `vn-icpc-danang-2026-fill` (remote `origin`, Marszpace/icpc-template).
Teammates (autoastt, saltyy) also push here, so `git fetch` before working.
The user is Marszpace; use they/them for people whose pronouns are unknown.

## How the book is built
- `make kactl` builds `kactl.pdf` (two LaTeX passes, needs `test-session.pdf`, which is in the repo). `make fast` is one pass only,
  so the table of contents can be off; use `make kactl` for page counts. `pdfinfo` is not installed; read the page count from
  the `Output written on build//kactl.pdf (N pages ...)` line.
- `content/<chapter>/chapter.tex` decides what is printed, via `\kactlimport{File.h}`. Commenting the line out (`% \kactlimport...`)
  removes it from the book but keeps the file. `content/kactl.tex` is the cover and chapter order.
- `doc/scripts/test-contest-scripts.sh` tests `content/contest/stress.sh` and `interactive.sh` against planted faults (WA, crash, TLE, checker, missing flush, too many queries); not part of `make test`, run it by hand (about 35 s).
- The contest file is `content/contest/macros.cpp` (only macros/typedefs: `rep all sz pb ll pii vi`; the includes, `using namespace std` and `main` are not printed, the team remembers them). The team usually adds `#define int long long` + `signed main` after the includes; it is not in the file but the library works with it: `LLINT=1 make test` and `LLINT=1 make test-compiles` run everything in that mode (CI does both). `doc/scripts/prelude.h` is the includes + macros prelude for `make test-compiles`; `stress-tests/utilities/template.h` includes `macros.cpp` itself. Code rules for both modes: `(int)(x)` not `int(x)`, `max<int>(x, 0)` not `max(x, 0)`, wrap `#include <bits/extc++.h>` in `#pragma push_macro("int")` / `#undef int` / `#pragma pop_macro("int")`, postfix `operator++(signed)` (not `(int)`), tests use `signed main`.
- `content/contest/hash.sh [file]` prints the first 6 hex chars of the md5 of a file (or stdin) with whitespace and comments stripped; it is also what `content/tex/preprocessor.py` runs (`sh hash.sh < code`) to compute the hashes printed in the book. The typed code is hashed, so a repo file with `#pragma once`, local `#include`s or `include-line` lines will not match the printed hash (the book prints those differently).
- `doc/scripts/skip_headers` lists headers that cannot compile alone in `make test-compiles` (they are snippets or need other headers first): `ModInverse.h`, `ModSqrt.h` and others. (`NumberTheoreticTransform.h`, `BostanMori.h`, `PolyOps.h` were removed from it on 2026-11-11: there is one shared `mod` now.) `make test-compiles` is 158/158 in both modes.
- The judge runs Ubuntu 24.04 with Python = CPython 3.12.3 and PyPy 7.3.15 (Python 3.9.18); both are installed here (`/usr/bin/python3.12`, `/usr/bin/pypy3`, from apt) and `doc/note-checks/check_python.py` runs on each. PyPy differences that matter: deep recursion segfaults in the main thread (needs `threading.stack_size(2**29)` for depth 1e6), no `math.cbrt`; CPython 3.12: `lru_cache` recursion fails near depth 3300.
- Text notes are checked by `doc/note-checks/run-all.sh` (python3 / C++ scripts that verify every formula by brute force; not part of `make test`). Build the book with `make kactl < /dev/null`: a LaTeX error otherwise waits on a prompt forever (an unescaped `&` in a `Usage:` line is the usual cause; write `\&`).
- `make test` runs the stress tests in `stress-tests/<chapter>/` (133; every printed code file is now covered except text-only headers). New code should get a stress test.
- The built `kactl.pdf` is committed; rebuild and commit it with content changes.
- Page budget: the original KACTL is 26 pages (cover + 25). **The Danang limit is 26 PDF pages (25 + cover), confirmed by the team**; never go over it (the book is 25 now).
- `TODO.md` now has "Standing rules" (so items can be done without asking), "Ready" items with decided specs, and "Blocked" items (Fenwick edit, ModInt, shared `mod`, techniques.txt rework from en-oi-wiki.marszpace.dev). The host `en-oi-wiki.marszpace.dev` was not reachable from the session that wrote this; a personal environment `icpc-template` with that host allowed was created for it.

## Current state (as of 2026-10-30)
- Layout (2026-11-09, applied): file header = name, include list beside it, hash + line count flush right (own right-justified line if it does not fit), thin rule, then Description + `Time:`, Memory, Usage at the bottom (`\kactltitle` in `content/tex/kactlpkg.sty`); tighter listing spacing, smaller headings, 6pt column gap, 3pt display-equation spacing; `\subsection` skip fixed (it had negative stretch and made lines overlap); long page headers shrink to 7pt; shorter descriptions (09) and 27 unwrapped code lines (12). `doc/overnight-2026-11-09/layout-check.py kactl.pdf` checks a build for overlaps, header overflow and orphan titles; run it after every rebuild. Not taken: 07 (techniques in the same flow), 08 (no blank lines in code); see `doc/overnight-2026-11-09/REPORT.md`.
- Descriptions and techniques (2026-11-11, applied): the printed descriptions are level **H** (G's content, facts that belong to one function moved into trailing code comments on its signature line; <= 63 columns, so hashes and line counts do not change). `content/appendix/techniques.txt` is the 180-entry wild list (one full page). Everything that led to this, including the other levels (G, L, M), the worksheet for every candidate technique and the scripts, is in `doc/overnight-2026-11-10/` (`REPORT.md`); keep it for reference.
- Book is **25 pages** (cover + 24), one page under the Danang limit (26), with about 2.2 columns free on the last body page (the techniques page is full); after the team cut *C++ pitfalls* and `Int128.h` (known by heart; files/checker stay). `ExLucas.h` (number-theory) was added by a teammate; `RadixConversion.h`, `BostanMori.h`, the lazy treap, `maxRight` and the text notes (matrix-tree / BEST / LGV, Garner, exponents, suffix facts, generating functions) by us.
- `CHANGES-vs-original.md`: everything added, cut and removed compared to stock KACTL, with reasons. Keep it up to date.
- `entries - nx_entries.csv`: the team's per-entry decision (Keep / Delete / Edit / Merge / ?). Columns: Category, Topic, Lines,
  Status, Reason, "What to edit & reason". It is the source of truth for decisions. Its bottom block lists cut files.
- `TODO.md`: the work list: standing rules, ready items with decided specs (work through them in order, one plan / go / report cycle per item), blocked items.

## Conventions and gotchas
- Team policy: remove entries that are trivial or memorized by a team member (the reason given in the CSV). Hard-to-remember
  or error-prone code stays.
- Removed code files stay in the repo (only the import is commented out); removed text sections are deleted from `chapter.tex`.
- Dropping a section header such as `\section{Games}` also drops its text; the script I used cut from a heading to the next heading
  of the same or higher level.
- Lazy segment tree = `LazySegTreeBlock.h` (edit block: `S`, `L`, `e/id/op/ok/app/comp`; default is chmin+add beats) + `LazySegTree.h` (fixed body, listed in `doc/scripts/skip_headers` because it needs the block first). Two files so each keeps its own hash. `HLD.h` includes both. Tests: `stress-tests/data-structures/LazySegTree*.cpp` (the non-default blocks in the description are tested there too).
- `BumpAllocator.h` is cut from the book (team decision 2026-11-08; nothing printed uses it; the file stays, only the unprinted `SmallPtr.h` includes it).
- **Modulus convention** (2026-11-12, team): a header that needs a modulus *uses* a global `const ll mod` that the solution declares first; no header defines it, and `mint` (`ModularArithmetic.h`, not a template; `mi`, `vmi` aliases) needs nothing else. `ModPow.h` is just `modpow(b, e)`. The test prelude (`doc/scripts/prelude.h`, `stress-tests/utilities/template.h`) declares `const ll mod = 998244353` and `-DTEST_MOD=<v>` overrides it; a test lists `// TEST_MODS: a b c` and `doc/scripts/run-all.sh` runs it once per value (GCC then skips the precompiled header, which is correct but slower). NTT / PolyOps / BostanMori need `mod = c * 2^k + 1` (`static_assert`); with 10^9+7 use FFTMod. A test must not define its own global `mod`. `ModInverse.h` (a snippet) prints only `const ll LIM = 200000;`, no `mod`.
- `make test` was not re-run after the review's removals or after `ExLucas`.
- Never commit or push without being asked. Commit messages here end with the Co-Authored-By line from the session's attribution reminder.
- Scratch work goes in the session scratchpad, not in the repo. A scratch copy of the repo can be made with `tar --exclude=.git`
  to test a build without touching the working tree.

## How to regenerate the entries table
It was produced by a throwaway script (not in the repo) that read the `\kactlimport` lines and `\section`/`\subsection` headings of
each `chapter.tex`, counted lines of each file (text sections: non-blank non-comment `.tex` lines), and took reasons from
`CHANGES-vs-original.md`. If needed, rebuild it the same way, or just edit the CSV by hand.
