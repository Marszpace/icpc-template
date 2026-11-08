#!/bin/bash
# Prints the first 6 chars of the md5 of a file (or stdin),
# ignoring whitespace and comments: to check typed code.
# Usage: chmod +x hash.sh; ./hash.sh [file.cpp]
[ -z "$1" -o -r "$1" ] || { echo "can't read $1"; exit 1; }
cpp -dD -P -fpreprocessed < "${1:-/dev/stdin}" |
	tr -d '[:space:]' | md5sum | cut -c-6
