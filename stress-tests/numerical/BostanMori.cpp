#include "../utilities/template.h"

// TEST_MODS: 998244353

#include "../../content/numerical/BostanMori.h"

// terms one by one
vl terms(vl S, const vl& tr, int cnt) {
	int n = sz(tr);
	S.resize(cnt);
	rep(i,n,cnt) {
		S[i] = 0;
		rep(j,0,n) S[i] = (S[i] + tr[j] * S[i - 1 - j]) % mod;
	}
	return S;
}

// matrix power: independent of the polynomial methods
ll viaMatrix(const vl& S, const vl& tr, ll k) {
	int n = sz(tr);
	typedef vector<vl> Mat;
	auto mul = [&](const Mat& a, const Mat& b) {
		Mat c(n, vl(n));
		rep(i,0,n) rep(j,0,n) rep(l,0,n) c[i][j] = (c[i][j] + a[i][l] * b[l][j]) % mod;
		return c;
	};
	Mat M(n, vl(n)), R(n, vl(n)); // state (S[i], ..., S[i-n+1]) -> (S[i+1], ..., S[i-n+2])
	rep(j,0,n) M[0][j] = tr[j];
	rep(i,1,n) M[i][i - 1] = 1;
	rep(i,0,n) R[i][i] = 1;
	for (ll e = k; e; e /= 2, M = mul(M, M)) if (e % 2) R = mul(R, M);
	// S[k] from the state at time n-1: (S[n-1], ..., S[0]), take row 0 of M^(k-n+1) when k >= n
	// simpler: use state at time 0 reversed, rows of R give S[k+n-1-i] ... so use k + n - 1
	ll res = 0;
	rep(j,0,n) res = (res + R[n - 1][j] * S[n - 1 - j]) % mod; // R = M^k: row n-1 gives S[k]
	return res;
}

// Kitamasa, O(n^2 log k): x^k mod (x^n - sum tr[j] x^(n-1-j))
ll viaKitamasa(const vl& S, const vl& tr, ll k) {
	int n = sz(tr);
	auto mulmod = [&](const vl& a, const vl& b) {
		vl c(2 * n);
		rep(i,0,n) rep(j,0,n) c[i + j] = (c[i + j] + a[i] * b[j]) % mod;
		for (int i = 2 * n - 1; i >= n; i--) rep(j,0,n)
			c[i - 1 - j] = (c[i - 1 - j] + c[i] * tr[j]) % mod;
		c.resize(n);
		return c;
	};
	vl r(n), x(n);
	r[0] = 1;
	if (n == 1) x[0] = tr[0]; else x[1] = 1;
	for (ll e = k; e; e /= 2, x = mulmod(x, x)) if (e % 2) r = mulmod(r, x);
	ll res = 0;
	rep(i,0,n) res = (res + r[i] * S[i]) % mod;
	return res;
}

ll rnd() { return ((ll)rand() * 32768 + rand()) % mod; }

signed main() {
	srand(4);
	// every term of small random recurrences, including the extremes of the field
	rep(it,0,400) {
		int n = 1 + rand() % 12, cnt = 60;
		vl S(n), tr(n);
		for (ll& x : S) x = it % 7 == 0 ? mod - 1 : it % 5 == 0 ? rand() % 2 : rnd();
		for (ll& x : tr) x = it % 3 == 0 ? mod - 1 : it % 4 == 0 ? rand() % 2 : rnd();
		vl want = terms(S, tr, cnt);
		rep(k,0,cnt) assert(bostanMori(S, tr, k) == want[k]);
	}
	// huge k against two independent methods
	rep(it,0,200) {
		int n = 1 + rand() % 10;
		vl S(n), tr(n);
		for (ll& x : S) x = rnd();
		for (ll& x : tr) x = rnd();
		ll k = rnd() * rnd() + rand() % 3; // up to about 1e18
		ll a = bostanMori(S, tr, k);
		assert(a == viaMatrix(S, tr, k));
		assert(a == viaKitamasa(S, tr, k));
	}
	// larger orders, S longer than needed
	rep(it,0,6) {
		int n = 50 + rand() % 150;
		vl S(n + rand() % 3), tr(n);
		for (ll& x : S) x = rnd();
		for (ll& x : tr) x = rnd();
		ll k = rnd() * rnd(); // up to about 1e18
		assert(bostanMori(S, tr, k) == viaKitamasa(vl(S.begin(), S.begin() + n), tr, k));
	}
	// Fibonacci: F(10^18) mod 998244353 by fast doubling
	{
		auto fib = [&](ll n, auto&& self) -> pair<ll, ll> { // (F(n), F(n+1))
			if (!n) return {0, 1};
			auto [a, b] = self(n / 2, self);
			ll c = a * ((2 * b - a + mod) % mod) % mod, d = (a * a + b * b) % mod;
			return n % 2 ? make_pair(d, (c + d) % mod) : make_pair(c, d);
		};
		for (ll k : {0LL, 1LL, 2LL, 10LL, 1000000000000000000LL})
			assert(bostanMori({0, 1}, {1, 1}, k) == fib(k, fib).first);
	}
	assert(bostanMori({}, {}, 5) == 0);
	cout<<"Tests passed!"<<endl;
}
