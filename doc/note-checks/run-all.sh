#!/usr/bin/env bash
# Re-checks the formulas written in the text notes of the book (not part of `make test`).
# Usage: doc/note-checks/run-all.sh   (needs python3 and g++)
cd "$(dirname "$0")/../.." || exit 1
fail=0
for f in doc/note-checks/check_*.py; do
	if [ "$f" = doc/note-checks/check_python.py ]; then
		# the judge has CPython 3.12 and PyPy 3.9: run on every interpreter that exists here
		for py in python3.12 pypy3 python3; do
			command -v $py > /dev/null && { echo "== $f ($py)"; $py "$f" || fail=1; }
		done
	else
		echo "== $f"; python3 "$f" || fail=1
	fi
done
for f in doc/note-checks/check_*.cpp; do
	echo "== $f"
	g++ -std=c++17 -O2 -w "$f" -o /tmp/note-check-bin && /tmp/note-check-bin || fail=1
done
[ $fail -eq 0 ] && echo "all note checks passed" || { echo "SOME NOTE CHECK FAILED"; exit 1; }
