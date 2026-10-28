#include "../utilities/template.h"

#include "../../content/numerical/SolveLinearMod.h"

// rank over the rationals with fraction-free (Bareiss) elimination; the
// entries are small, so it equals the rank mod 10^9+7 and is independent of
// the code under test
int rankQ(vector<vector<ll>> a) {
	int n = sz(a), m = n ? sz(a[0]) : 0, r = 0;
	ll prev = 1;
	rep(c,0,m) {
		int p = -1;
		rep(i,r,n) if (a[i][c]) { p = i; break; }
		if (p < 0) continue;
		swap(a[p], a[r]);
		rep(i,r+1,n) {
			rep(j,c+1,m) a[i][j] = (a[r][c] * a[i][j] - a[i][c] * a[r][j]) / prev;
			a[i][c] = 0;
		}
		prev = a[r][c];
		r++;
	}
	return r;
}

int main() {
	srand(6);
	int solvable = 0, unsolvable = 0;
	rep(it,0,40000) {
		int n = 1 + rand() % 6, m = 1 + rand() % 6;
		vector<vl> A(n, vl(m));
		rep(i,0,n) rep(j,0,m) A[i][j] = rand() % 3 == 0 ? 0 : rand() % 5;
		if (rand() % 3 == 0 && n > 1) A[n-1] = A[0]; // force dependent rows
		vl b(n), x0(m);
		if (rand() % 2) {
			rep(j,0,m) x0[j] = rand() % 5;
			rep(i,0,n) rep(j,0,m) b[i] += A[i][j] * x0[j];
		} else rep(i,0,n) b[i] = rand() % 5;
		vector<vl> aug = A;
		rep(i,0,n) aug[i].push_back(b[i]);
		int rA = rankQ(A), rAug = rankQ(aug);

		vector<vl> A2 = A; vl b2 = b, x(m);
		int ret = solveLinearMod(A2, b2, x);
		if (rA < rAug) {
			assert(ret == -1);
			unsolvable++;
		} else {
			assert(ret == rA);
			assert(sz(x) == m);
			rep(i,0,n) {
				ll s = 0;
				rep(j,0,m) s = (s + A[i][j] * x[j]) % mod;
				assert(s == b[i] % mod);
			}
			solvable++;
		}
	}
	cerr << "solvable " << solvable << ", unsolvable " << unsolvable << endl;
	assert(solvable > 5000 && unsolvable > 5000);
	cout << "Tests passed!" << endl;
}
