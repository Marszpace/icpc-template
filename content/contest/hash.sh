cpp -dD -P -fpreprocessed < "${1:-/dev/stdin}" |
	tr -d '[:space:]' | md5sum | cut -c-6
