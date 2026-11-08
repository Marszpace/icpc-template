# Interactive tester. ./A solution; ./interactor in reads the
# test file "in", talks on stdin/stdout (flush every line!),
# verdict on stderr, exit != 0 on WA; ./gen S prints a test.
# Usage: bash interactive.sh in       one test
#        bash interactive.sh gen [N]  stress test
run() {
	timeout 5 ./interactor $1 > to < from 2> verdict & p=$!
	timeout 5 ./A < to > from; ar=$?  # keep this open order
	wait $p; ir=$?
	[ $ar -eq 0 -a $ir -eq 0 ] && return
	echo "A exit $ar (124 = timeout: flush?)," \
		"judge exit $ir: $(cat verdict)"; return 1
}
mkfifo to from; trap 'rm -f to from' EXIT
if [ "$1" = gen ]; then
	for ((i=1; i<=${2:-100}; i++)); do ./gen $i > in
		run in || { echo "seed $i"; exit 1; }
	done; echo OK
else run $1 && cat verdict; fi
