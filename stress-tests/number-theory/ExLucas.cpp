#include "../utilities/template.h"

#include "../../content/number-theory/ExLucas.h"

mt19937_64 rng(2);
ll rnd(ll lo, ll hi) { return uniform_int_distribution<ll>(lo, hi)(rng); }

const int N = 100000;
vi primes;

// C(n, k) mod m via Legendre exponents of every prime <= n
ll slow(ll n, ll k, ll m) {
	ll r = 1 % m;
	for (int p : primes) {
		if (p > n) break;
		ll e = 0;
		for (ll t = n; t /= p;) e += t;
		for (ll t = k; t /= p;) e -= t;
		for (ll t = n - k; t /= p;) e -= t;
		while (e--) r = r * p % m;
	}
	return r;
}

int main() {
	vector<bool> comp(N + 1);
	rep(i,2,N+1) if (!comp[i]) {
		primes.push_back(i);
		for (ll j = (ll)i * i; j <= N; j += i) comp[j] = 1;
	}
	// exhaustive vs Pascal's triangle
	rep(m,1,301) {
		int mx = 200;
		BinomMod B(m, mx);
		vector<ll> row(mx + 1);
		rep(n,0,mx+1) {
			for (int k = n; k > 0; k--) row[k] = (row[k] + row[k-1]) % m;
			row[0] = 1 % m;
			rep(k,0,n+1) assert(B(n, k) == row[k]);
			assert(B(n, n + 1) == 0 && B(n, -1) == 0);
		}
	}
	// big moduli: prime powers, products, large primes, random
	vector<ll> ms = {1LL << 30, 1LL << 3, 1LL << 2, 2, 1162261467, 9765625 * 2,
		2147483647, 2147483629, 999999937LL * 2, 1 << 20, 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23,
		(1LL << 10) * 59049 * 25, 1000000007};
	rep(i,0,30) ms.push_back(rnd(1, (1LL << 31) - 1));
	rep(i,0,30) { ll m = 1; while (true) { ll q = m * rnd(2, 40); if (q >= (1LL << 31)) break; m = q; } ms.push_back(m); }
	for (ll m : ms) {
		ll mx = rnd(0, 1) ? N : rnd(0, 1000);
		BinomMod B(m, mx);
		rep(it,0,300) {
			ll n = rnd(0, mx), k = rnd(0, n);
			assert(B(n, k) == slow(n, k, m));
		}
	}
	cout << "Tests passed!" << endl;
}
