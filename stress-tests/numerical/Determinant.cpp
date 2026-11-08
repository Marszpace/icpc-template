#include "../utilities/template.h"

#include "../../content/numerical/Determinant.h"

// exact determinant of an integer matrix via Bareiss (fraction-free)
ll bareiss(vector<vector<ll>> a) {
	int n = sz(a); ll sign = 1, prev = 1;
	rep(k,0,n-1) {
		if (a[k][k] == 0) {
			int r = -1;
			rep(i,k+1,n) if (a[i][k]) { r = i; break; }
			if (r < 0) return 0;
			swap(a[k], a[r]); sign = -sign;
		}
		rep(i,k+1,n) rep(j,k+1,n)
			a[i][j] = (ll)(((__int128)a[i][j] * a[k][k] - (__int128)a[i][k] * a[k][j]) / prev);
		prev = a[k][k];
	}
	return n ? sign * a[n-1][n-1] : 1;
}

mt19937 rng(3);
int rnd(int n) { return (int)(rng() % (unsigned)n); }

signed main() {
	
	rep(it,0,50000) {
		int n = rnd(7) + 1, K = rnd(10) + 1;
		vector<vector<ll>> a(n, vector<ll>(n));
		for (auto& r : a) for (ll& x : r) x = rnd(2*K+1) - K;
		if (rnd(5) == 0 && n > 1) { // singular: one row is a combination of two others
			int i = rnd(n), j = rnd(n), k = rnd(n);
			rep(c,0,n) a[i][c] = a[j][c] - a[k][c];
		}
		ll d = bareiss(a);
		vector<vector<double>> A(n, vector<double>(n));
		rep(i,0,n) rep(j,0,n) A[i][j] = (double)a[i][j];
		double r = det(A);
		assert(fabs(r - (double)d) <= 1e-6 * max(1.0, fabs((double)d)));
	}
	{ vector<vector<double>> A; assert(det(A) == 1); }
	cout << "Tests passed!" << endl;
}
