#include "../utilities/template.h"

#include "../../content/numerical/MatrixInverse.h"

// exact rank over Q of a small integer matrix, via rank mod two big primes
int rankModP(vector<vector<ll>> a, ll p) {
	int n = sz(a), m = n ? sz(a[0]) : 0, r = 0;
	auto pw = [&](ll b, ll e) { ll x = 1; b %= p; for (; e; e /= 2, b = b * b % p) if (e & 1) x = x * b % p; return x; };
	for (auto& row : a) for (ll& v : row) v = (v % p + p) % p;
	rep(c,0,m) {
		int piv = -1;
		rep(i,r,n) if (a[i][c]) { piv = i; break; }
		if (piv < 0) continue;
		swap(a[r], a[piv]);
		ll inv = pw(a[r][c], p - 2);
		rep(i,0,n) if (i != r && a[i][c]) {
			ll f = a[i][c] * inv % p;
			rep(k,0,m) a[i][k] = ((a[i][k] - f * a[r][k]) % p + p) % p;
		}
		r++;
	}
	return r;
}

mt19937 rng(1);
int rnd(int n) { return (int)(rng() % (unsigned)n); }

signed main() {
	
	rep(it,0,30000) {
		int n = rnd(8) + 1, K = rnd(6) + 1;
		vector<vector<ll>> a(n, vector<ll>(n));
		int lowrank = rnd(3) == 0;
		if (lowrank) { // product of n x k and k x n
			int k = rnd(n);
			vector<vector<ll>> u(n, vector<ll>(k)), v(k, vector<ll>(n));
			for (auto& r : u) for (ll& x : r) x = rnd(2*K+1) - K;
			for (auto& r : v) for (ll& x : r) x = rnd(2*K+1) - K;
			rep(i,0,n) rep(j,0,n) rep(t,0,k) a[i][j] += u[i][t] * v[t][j];
		} else
			for (auto& r : a) for (ll& x : r) x = rnd(2*K+1) - K;
		int rk = rankModP(a, 1000000007);
		assert(rk == rankModP(a, 998244353));
		vector<vector<double>> A(n, vector<double>(n));
		rep(i,0,n) rep(j,0,n) A[i][j] = (double)a[i][j];
		auto orig = A;
		int r = matInv(A);
		assert(r == rk);
		if (r == n) {
			rep(i,0,n) rep(j,0,n) {
				double s = 0;
				rep(k,0,n) s += orig[i][k] * A[k][j];
				assert(fabs(s - (i == j)) < 1e-6);
			}
		}
	}
	// n = 0 and a well-conditioned big case
	{ vector<vector<double>> A; assert(matInv(A) == 0); }
	{
		int n = 60;
		vector<vector<double>> A(n, vector<double>(n));
		rep(i,0,n) rep(j,0,n) A[i][j] = (double)(rnd(1000)) / 100 + (i == j) * 300;
		auto orig = A;
		assert(matInv(A) == n);
		rep(i,0,n) rep(j,0,n) {
			double s = 0;
			rep(k,0,n) s += orig[i][k] * A[k][j];
			assert(fabs(s - (i == j)) < 1e-9);
		}
	}
	cout << "Tests passed!" << endl;
}
