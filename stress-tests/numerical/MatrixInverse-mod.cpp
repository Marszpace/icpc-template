#include "../utilities/template.h"

#include "../../content/numerical/MatrixInverse-mod.h"

// rank mod p by plain elimination
int rankMod(vector<vector<ll>> a) {
	int n = sz(a), r = 0;
	rep(c,0,n) {
		int piv = -1;
		rep(i,r,n) if (a[i][c]) { piv = i; break; }
		if (piv < 0) continue;
		swap(a[r], a[piv]);
		ll inv = modpow(a[r][c], mod - 2);
		rep(i,0,n) if (i != r && a[i][c]) {
			ll f = a[i][c] * inv % mod;
			rep(k,0,n) a[i][k] = ((a[i][k] - f * a[r][k]) % mod + mod) % mod;
		}
		r++;
	}
	return r;
}

mt19937 rng(2);
int rnd(int n) { return (int)(rng() % (unsigned)n); }

signed main() {
	
	rep(it,0,30000) {
		int n = rnd(8) + 1;
		vector<vector<ll>> a(n, vector<ll>(n));
		int mode = rnd(3);
		for (auto& r : a) for (ll& x : r)
			x = mode == 0 ? (ll)(rnd(mod)) : mode == 1 ? rnd(3) : (rnd(4) ? 0 : (ll)(rnd(mod)));
		if (rnd(4) == 0 && n > 1) a[rnd(n)] = a[rnd(n)]; // force some singular ones
		int rk = rankMod(a);
		auto A = a;
		int r = matInv(A);
		if (rk == n) {
			assert(r == n);
			rep(i,0,n) rep(j,0,n) {
				ll s = 0;
				rep(k,0,n) s = (s + a[i][k] * A[k][j]) % mod;
				assert(A[i][j] >= 0 && A[i][j] < mod);
				assert(s == (i == j));
			}
		} else assert(r == rk); // full pivoting: the step where it stops is the rank
	}
	cout << "Tests passed!" << endl;
}
