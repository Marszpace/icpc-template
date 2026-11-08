#include "../utilities/template.h"

// The real header, with its composite modulus 12345 = 3 * 5 * 823.
#include "../../content/numerical/IntDeterminant.h"

// The pure-integer version the description mentions (modulos removed).
ll idet(vector<vector<ll>>& a) {
	int n = sz(a); ll ans = 1;
	rep(i,0,n) {
		rep(j,i+1,n) {
			while (a[j][i] != 0) { // gcd step
				ll t = a[i][i] / a[j][i];
				if (t) rep(k,i,n) a[i][k] -= a[j][k] * t;
				swap(a[i], a[j]);
				ans *= -1;
			}
		}
		ans *= a[i][i];
		if (!ans) return 0;
	}
	return ans;
}

// determinant by permutation expansion, mod m
ll brute(vector<vector<ll>>& a, ll m) {
	int n = sz(a); vi p(n); iota(all(p), 0);
	ll res = 0;
	do {
		ll t = 1;
		rep(i,0,n) t = t * a[i][p[i]] % m;
		int inv = 0;
		rep(i,0,n) rep(j,i+1,n) inv += p[i] > p[j];
		res = ((res + (inv & 1 ? -t : t)) % m + m) % m;
	} while (next_permutation(all(p)));
	return res;
}

mt19937 rng(5);
int rnd(int n) { return (int)(rng() % (unsigned)n); }

signed main() {
	// exhaustive small cases mod 12345 with entries 0..3, and n <= 2 with entries 0..5
	rep(it,0,200000) {
		int n = rnd(6) + 1, mode = rnd(4);
		vector<vector<ll>> a(n, vector<ll>(n));
		for (auto& r : a) for (ll& x : r)
			x = mode == 0 ? rnd(4) : mode == 1 ? rnd((int)mod) : mode == 2 ? (rnd(3) ? 0 : rnd((int)mod)) : rnd(2001) - 1000;
		if (mode == 3) for (auto& r : a) for (ll& x : r) x = (x % mod + mod) % mod; // header wants entries in [0, mod)
		ll want = brute(a, mod);
		auto b = a;
		ll got = det(b);
		assert(got == want);
		// pure-integer version vs exact (small entries)
		vector<vector<ll>> c(n, vector<ll>(n));
		for (auto& r : c) for (ll& x : r) x = rnd(11) - 5;
		ll e = brute(c, (ll)1e18 + 9); // exact up to sign wrap: |det| <= 5^6 * 720
		if (e > (ll)5e17) e -= (ll)1e18 + 9;
		auto c2 = c;
		assert(idet(c2) == e);
	}
	cout << "Tests passed!" << endl;
}
