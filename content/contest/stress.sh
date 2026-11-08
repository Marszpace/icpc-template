# Stress test. Compile first, e.g.
#   g++ -O2 -std=c++17 -fsanitize=address,undefined A.cpp -o A
# ./A solution, ./gen S prints a small random test (seed S),
# ./A2 brute force (may be missing if ./checker exists),
# ./checker in out ans: optional, exit 0 = OK (ans = A2 output)
# Usage: bash stress.sh [iterations]
for ((i=1; i<=${1:-1000}; i++)); do
	./gen $i > in
	timeout 5 ./A < in > out ||
		{ echo "A crash/TLE, seed $i"; exit 1; }
	if [ -x A2 ]; then ./A2 < in > ans; else : > ans; fi
	if [ -x checker ]; then ./checker in out ans
	else diff -wB out ans >/dev/null; fi || {
		echo "WA, seed $i"; tail -n+1 in out ans; exit 1; }
done; echo OK
