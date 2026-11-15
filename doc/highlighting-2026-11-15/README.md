# Syntax highlighting samples (2026-11-15)

Samples only: **the book is unchanged.** Every scheme is rendered through the real build (`preprocessor.py`, `kactlpkg.sty`,
LaTeX `listings`) on the same page: `macros.cpp`, `KMP.h`, `SegmentTree.h`, `DominatorTree.h` and a check line.

- `comparison.png`: the same excerpt in all 10 schemes, side by side.
- `all-schemes.pdf`: one page per scheme, at real print size (best way to judge; print one page if you can).

| # | Scheme | Notes |
|---|---|---|
| 00 | current book | no colour, bold keywords, serif italic comments |
| 01 | VS Code Light+ | exact Light+ colours, variables dark blue |
| 02 | VS Code Light+, black variables | 01 with variables in black: less busy |
| 03 | VS Code Light+, darker | 02 with every colour about 20% darker, for small type on a laser printer |
| 04 | VS Code Light+, lite | only keywords, numbers, strings and comments coloured |
| 05 | GitHub light | red keywords, purple functions and types, grey comments |
| 06 | JetBrains (CLion) light | blue keywords, teal types, grey italic comments |
| 07 | Xcode light | bold purple keywords |
| 08 | Atom One Light | purple keywords, blue functions, yellow types |
| 09 | KACTL `\enablecolors` | the colour option that already exists in `kactlpkg.sty` |

| 10 | Catppuccin Latte, Light+ roles | each Light+ role in its nearest Latte colour: keywords Blue, control Mauve, types Sapphire, functions Yellow, numbers Teal, strings Red, comments Green, variables and operators Text (`#4c4f69`) |
| 11 | Catppuccin Latte, darker | 10 with every accent at 72% brightness: Latte is made for its `#eff1f5` background and is pale on white paper |

`comparison-catppuccin.png` compares 02, 10 and 11; `catppuccin.pdf` has 10 and 11 at print size.

VS Code Dark+ is left out: its colours (light yellow functions, light blue variables) are unreadable on white, and a black
background does not print well.

## How it works (prototype)

`listings` only knows keywords, comments and strings. VS Code also colours function names, types and numbers, so the
preprocessor adds them for each file (`prototype/preprocessor.diff`, active when `KACTL_HL=1`):

- **Functions:** identifiers that are followed by `(` more often than not (so `rep`, `sz`, `max`, `push_back`, `query`;
  but not `dfs` in `dfs(dfs, r)` or arrays such as `num` declared as `vi num(n)`). This is close to VS Code's default
  grammar.
- **Types:** STL types, `ll` / `vi` / `pii` and other common typedefs, plus names from `struct`, `class`, `typename`,
  `typedef` and `using ... =` in the file.
- **Control keywords** (`if`, `for`, `return`, ...) are a separate class from the other keywords (`int`, `const`,
  `struct`, ...), as in VS Code (purple and blue).
- **Numbers:** each number literal outside comments and strings is marked with invisible delimiters, so `10`, `0x1F`
  and `1e-9` are coloured but the digits in `x1` or `mt19937_64` are not.

Hashes and line counts do not change (they are computed from the source before this). The VS Code schemes print comments
in the code font instead of serif italic. Since `listings` gives every character the same width, this should not move
any line, but I will check the page count when it is applied.

`prototype/` holds the shared setup (`hlcommon.tex`), the schemes (`schemes/*.tex`), the sample page (`sample.tex`,
`sample/`) and `mk.sh`, which builds one scheme.
