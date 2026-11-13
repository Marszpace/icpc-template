# ./checker in out ans: exit 0 = OK
for ((i=1; i<=${1:-1000}; i++)); do
	./gen $i > in
	timeout 5 ./A < in > out ||
		{ echo "A crash/TLE, seed $i"; exit 1; }
	if [ -x A2 ]; then ./A2 < in > ans; else : > ans; fi
	if [ -x checker ]; then ./checker in out ans
	else diff -wB out ans >/dev/null; fi || {
		echo "WA, seed $i"; tail -n+1 in out ans; exit 1; }
done; echo OK
