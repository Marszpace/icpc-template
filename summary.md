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
- `make test` runs the stress tests in `stress-tests/<chapter>/` (about 100). New code should get a stress test.
- The built `kactl.pdf` is committed; rebuild and commit it with content changes.
- Page budget: the original KACTL is 26 pages (cover + 25). The page limit of the Danang contest is unconfirmed.

## Current state (as of 2026-10-30)
- Book is **24 pages** (cover + 23) after the team review. `ExLucas.h` (number-theory) was added by a teammate.
- `CHANGES-vs-original.md`: everything added, cut and removed compared to stock KACTL, with reasons. Keep it up to date.
- `entries - nx_entries.csv`: the team's per-entry decision (Keep / Delete / Edit / Merge / ?). Columns: Category, Topic, Lines,
  Status, Reason, "What to edit & reason". It is the source of truth for decisions. Its bottom block lists cut files.
- `TODO.md`: open work. Mainly: edit `template.cpp`, `.bashrc`, `hash.sh`; shorten Derivatives/Sums/Series notes; merge the two
  lazy segment trees (`LazySegmentTree.h` + `LazySegTree.h`); decide `IntPerm.h` and `LCA.h`; later delete `BumpAllocator.h`;
  add Bostan-Mori, RadixConversion, Garner and a generating-functions note; adapt all kept code to the new `template.cpp`.

## Conventions and gotchas
- Team policy: remove entries that are trivial or memorized by a team member (the reason given in the CSV). Hard-to-remember
  or error-prone code stays.
- Removed code files stay in the repo (only the import is commented out); removed text sections are deleted from `chapter.tex`.
- Dropping a section header such as `\section{Games}` also drops its text; the script I used cut from a heading to the next heading
  of the same or higher level.
- `LazySegmentTree.h` and `HLD.h` include `BumpAllocator.h`, so that cannot be deleted before they are reformatted.
- `PolyOps.h` and `NumberTheoreticTransform.h` use modulus 998244353; other number-theory files use the global `mod` from `ModPow.h`.
- `make test` was not re-run after the review's removals or after `ExLucas`.
- Never commit or push without being asked. Commit messages here end with the Co-Authored-By line from the session's attribution reminder.
- Scratch work goes in the session scratchpad, not in the repo. A scratch copy of the repo can be made with `tar --exclude=.git`
  to test a build without touching the working tree.

## How to regenerate the entries table
It was produced by a throwaway script (not in the repo) that read the `\kactlimport` lines and `\section`/`\subsection` headings of
each `chapter.tex`, counted lines of each file (text sections: non-blank non-comment `.tex` lines), and took reasons from
`CHANGES-vs-original.md`. If needed, rebuild it the same way, or just edit the CSV by hand.
