#!/bin/bash
# usage: mk.sh name   (schemes/name.tex + hlcommon) | mk.sh name --plain "tex"
cd "$(dirname "$0")"
if [ "$2" = "--plain" ]; then echo "$3" > hl.tex; HL=; else printf '\\input{schemes/%s.tex}\n\\input{content/tex/hlcommon.tex}\n' "$1" > hl.tex; HL=1; fi
printf '\\newcommand\\schemename{%s}\n' "$(echo $1 | sed 's/-/ /g')" >> hl.tex
KACTL_HL=$HL TEXINPUTS=.:content/tex/: pdflatex -shell-escape -interaction=nonstopmode -output-directory build sample.tex > build/s.log 2>&1
grep -E "^!" build/s.log | head -3
mkdir -p out; cp build/sample.pdf out/$1.pdf
pdftoppm -r 150 -png -singlefile out/$1.pdf out/$1-full
convert out/$1-full.png -crop 1150x1230+20+40 +repage out/$1.png; rm out/$1-full.png
