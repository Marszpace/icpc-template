#!/usr/bin/env bash
# Tests content/contest/stress.sh and interactive.sh against planted
# faults (wrong answer, crash, TLE, checker, missing flush, ...).
# Usage: doc/scripts/test-contest-scripts.sh [repo dir]
ROOT=$(cd "${1:-.}" && pwd)
W=$(mktemp -d); trap 'rm -rf $W' EXIT; cd $W
CXX="g++ -O2 -std=c++17 -w"
fails=0
expect() { # expect <0|1> <regex> <name> <command...>
	local want=$1 re=$2 name=$3; shift 3
	out=$("$@" 2>&1); rc=$?
	if [ $rc -ne $want ] || ! grep -Eq "$re" <<< "$out"; then
		echo "FAIL: $name (exit $rc, wanted $want / $re)"; echo "$out" | head -8
		fails=$((fails+1))
	else echo "ok: $name"; fi
}

# ---- problem 1: maximum subarray sum (n <= 6 values in -5..5)
cat > gen.cpp <<'X'
#include <bits/stdc++.h>
int main(int, char** v) { std::mt19937 r(atoi(v[1])); int n = r() % 6 + 1;
	printf("%d\n", n); while (n--) printf("%d ", (int)(r() % 11) - 5); puts(""); }
X
mk() { # mk <name> <body using n and a[]>
	cat > $1.cpp <<X
#include <bits/stdc++.h>
using namespace std;
int main() { int n; cin >> n; vector<int> a(n); for (int& x : a) cin >> x; $2 }
X
	$CXX $1.cpp -o $1
}
mk A_good 'int b = INT_MIN, c = 0; for (int x : a) { c = max(x, c + x); b = max(b, c); } cout << b << endl;'
mk A_bug 'int b = 0, c = 0; for (int x : a) { c = max(x, c + x); b = max(b, c); } cout << b << endl;'
GOOD='int b = INT_MIN, c = 0; for (int x : a) { c = max(x, c + x); b = max(b, c); } cout << b << endl;'
mk A_crash "if (n == 3) return 1; $GOOD"
mk A_tle "if (n == 2) for (;;); $GOOD"
mk A2_brute 'int b = INT_MIN; for (int i = 0; i < n; i++) for (int s = 0, j = i; j < n; j++) { s += a[j]; b = max(b, s); } cout << b << endl;'
$CXX gen.cpp -o gen
S=$ROOT/content/contest/stress.sh
run_stress() { # run_stress <solution> [iterations]: A.cpp = solution
	cp $1 A; bash $S ${2:-300}
}
cp A2_brute A2
expect 0 '^OK$' "stress: correct solution passes" run_stress A_good
expect 1 'WA, seed [0-9]+' "stress: wrong answer is caught" run_stress A_bug
expect 1 'crash/TLE, seed [0-9]+' "stress: crash is caught" run_stress A_crash
expect 1 'crash/TLE, seed [0-9]+' "stress: TLE is caught" run_stress A_tle
out=$(run_stress A_bug 2>&1); grep -q -- '==> A2 <==' <<< "$out" || grep -q -- '==> ans <==' <<< "$out" \
	|| { echo "FAIL: stress prints in/out/ans on WA"; fails=$((fails+1)); }

# ---- problem 2: print ANY index (1-based) of a maximum element
mk B_first 'cout << max_element(a.begin(), a.end()) - a.begin() + 1 << endl;'
mk B_last 'int k = 0; for (int i = 0; i < n; i++) if (a[i] >= a[k]) k = i; cout << k + 1 << endl;'
mk B_bad 'cout << 1 << endl;'
cat > checker.cpp <<'X'
#include <bits/stdc++.h>
using namespace std;
int main(int, char** v) { ifstream in(v[1]), out(v[2]); int n, k; in >> n; vector<int> a(n);
	for (int& x : a) in >> x; if (!(out >> k) || k < 1 || k > n) return 1;
	return a[k - 1] == *max_element(a.begin(), a.end()) ? 0 : 1; }
X
$CXX checker.cpp -o checker_bin
cp B_last A2
expect 1 'WA, seed' "stress: several valid answers fail without checker" run_stress B_first
cp checker_bin checker
expect 0 '^OK$' "stress: checker accepts a different valid answer" run_stress B_first
rm A2
expect 0 '^OK$' "stress: checker without A2" run_stress B_first
expect 1 'WA, seed' "stress: checker without A2 rejects a bad answer" run_stress B_bad
rm checker

# ---- problem 3: guess x in [1, 1000] with "? k" queries, at most 11
cat > gen.cpp <<'X'
#include <bits/stdc++.h>
int main(int, char** v) { int s = atoi(v[1]); std::mt19937 r(s);
	printf("%d\n", s % 3 == 0 ? 1 : s % 3 == 1 ? 1000 : (int)(r() % 1000) + 1); }
X
$CXX gen.cpp -o gen
cat > interactor.cpp <<'X'
#include <bits/stdc++.h>
using namespace std;
int main(int, char** v) { int x, q = 0; ifstream(v[1]) >> x; string t; cout << 1000 << endl;
	while (cin >> t) {
		if (t == "?") { int k; cin >> k; if (++q > 11) { cerr << "WA: too many queries\n"; return 1; }
			cout << (x < k ? "<" : x > k ? ">" : "=") << endl; }
		else { int g; cin >> g; if (g == x) { cerr << "OK x=" << x << " q=" << q << "\n"; return 0; }
			cerr << "WA: said " << g << " truth " << x << "\n"; return 1; }
	}
	cerr << "WA: no answer\n"; return 1; }
X
$CXX interactor.cpp -o interactor
mki() { # mki <name> <flush> <ending code> <answer shift> <search>
	cat > $1.cpp <<X
#include <bits/stdc++.h>
using namespace std;
int main() { cin.tie(0)->sync_with_stdio(0); int n; cin >> n; int lo = 1, hi = n;
	while (lo <= hi) { int m = $5; cout << "? " << m $2; string r; cin >> r;
		if (r == "=") { cout << "! " << m + $4 $2; return $3; }
		if (r == "<") hi = m - 1; else lo = m + 1; } }
X
	$CXX $1.cpp -o $1
}
mki I_good ' << endl' 0 0 '(lo + hi) / 2'
mki I_noflush ' << "\n"' 0 0 '(lo + hi) / 2'
mki I_wrong ' << endl' 0 1 '(lo + hi) / 2'
mki I_toomany ' << endl' 0 0 'lo'
mki I_crash ' << endl' 3 0 '(lo + hi) / 2'
I=$ROOT/content/contest/interactive.sh
run_inter() { cp $1 A; shift; bash ${SC:-$I} "$@"; }
run_inter_t() { SC=$W/transcript.sh run_inter "$@"; }
echo 7 > in
expect 0 'OK x=7' "interactive test: good solution" run_inter I_good in
expect 1 'WA: said 8' "interactive test: wrong answer" run_inter I_wrong in
expect 0 'OK x=7' "interactive test: linear search is fine for small x" run_inter I_toomany in
echo 500 > in
expect 1 'WA: too many' "interactive test: too many queries" run_inter I_toomany in
echo 7 > in
expect 1 'exit 124.*flush' "interactive test: missing flush times out" run_inter I_noflush in
expect 1 'A exit 3' "interactive test: crash after answering" run_inter I_crash in
expect 0 '^OK$' "interactive stress: good solution" run_inter I_good gen 60
expect 1 'seed [0-9]+' "interactive stress: wrong answer" run_inter I_wrong gen 60
expect 1 'WA: too many' "interactive stress: too many queries" run_inter I_toomany gen 60
# commented-out transcript: swap the active lines for the "#<tab>" ones
grep -v -e '^	timeout 5 ./interactor' -e '^	timeout 5 ./A <' $I | sed 's/^#	/	/' > $W/transcript.sh
echo 7 > in
expect 0 'OK x=7' "interactive transcript variant: still works" run_inter_t I_good in
cp I_good A; bash $W/transcript.sh in > /dev/null 2>&1; sleep 0.3
if [ "$(grep -c '^? ' log)" -ge 3 ] && grep -q '^=$' log && grep -q '^! 7$' log; then echo "ok: transcript log has the conversation"
else echo "FAIL: transcript log"; cat log 2>&1 | head; fails=$((fails+1)); fi
expect 1 'exit 124.*flush' "interactive transcript variant: missing flush" run_inter_t I_noflush in
cp I_good A; bash $W/transcript.sh gen 40 > /dev/null 2>&1 && echo "ok: transcript variant, stress mode" || { echo "FAIL: transcript stress"; fails=$((fails+1)); }
[ ! -e to ] && [ ! -e from ] || { echo "FAIL: fifos not cleaned up"; fails=$((fails+1)); }

[ $fails -eq 0 ] && echo "all contest script tests passed" || { echo "$fails failed"; exit 1; }
