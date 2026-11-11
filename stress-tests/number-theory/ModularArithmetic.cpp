#include "../utilities/template.h"

// The modulus is global now: run once per prime. 1073741789 is the largest prime
// below 2^30 (the worst case for int sums); 7 and 2 are tiny.
// TEST_MODS: 998244353 1000000007 1073741789 1000003 7 2

#include "../../content/number-theory/ModularArithmetic.h"

ll pw(ll a, ll e, ll m) {
	ll r = 1;
	a = ((a % m) + m) % m;
	for (; e; e >>= 1, a = a * a % m) if (e & 1) r = r * a % m;
	return r;
}

void test(mt19937_64& rng) {
	typedef mint T;
	const ll m = mod;
	rep(it,0,20000) {
		ll x = (ll)(rng() >> (rng() % 40)) * (rng() % 2 ? 1 : -1);
		ll y = (ll)(rng() >> (rng() % 40)) * (rng() % 2 ? 1 : -1);
		ll rx = ((x % m) + m) % m, ry = ((y % m) + m) % m;
		T a(x), b(y);
		assert((ll)(int)a == rx && (ll)(int)b == ry);
		assert((ll)(int)(a + b) == (rx + ry) % m);
		assert((ll)(int)(a - b) == ((rx - ry) % m + m) % m);
		assert((ll)(int)(a * b) == rx * ry % m);
		assert((ll)(int)(-a) == (m - rx) % m);
		T c = a;
		c += b; assert(c == a + b);
		c = a; c -= b; assert(c == a - b);
		c = a; c *= b; assert(c == a * b);
		if (ry) {
			assert((ll)(int)(a / b) == rx * pw(ry, m - 2, m) % m);
			assert((a / b) * b == a && inverse(b) * b == T(1));
			T d = a;
			d /= b; assert(d == a / b);
		}
		ll e = (ll)(rng() >> (1 + rng() % 62));
		assert((ll)(int)fpow(a, e) == pw(rx, e, m)); // also e = 0 and 0^0 = 1
		T u = a;
		assert(u++ == a && u == a + 1 && ++u == a + 2);
		assert(u-- == a + 2 && --u == a);
		assert((a == b) == (rx == ry) && (a != b) == (rx != ry));
		assert((a < b) == (rx < ry));
		stringstream ss;
		ss << rx << ' ' << x;
		T p, q;
		ss >> p >> q;
		assert(p == a && q == a);
		ostringstream os;
		os << a;
		assert(os.str() == to_string(rx));
	}
	assert((int)T(0) == 0 && (int)T(m) == 0 && (int)T(-m) == 0);
	assert((int)T(m - 1) == m - 1 && (int)(T(m - 1) + 1) == 0);
	assert((int)(T(0) - 1) == m - 1);
	assert((int)T(LLONG_MIN) == (((LLONG_MIN % m) + m) % m));
	assert((int)T(LLONG_MAX) == LLONG_MAX % m);
	assert((int)fpow(T(0), 0) == 1 && (int)fpow(T(0), 5) == 0);
	vector<T> v = {T(3), T(1), T(2)};
	sort(all(v));
	vi w;
	for (T x : v) w.push_back((int)x);
	assert(is_sorted(all(w)));
}

signed main() {
	mt19937_64 rng(7);
	test(rng);
	mi z = 5;
	vmi w(3, z);
	assert(sz(w) == 3 && (int)(w[0] * w[1]) == 25 % mod);
	if (mod > 2) assert((int)(mi(1) / mi(2) * mi(2)) == 1);
	cout<<"Tests passed!"<<endl;
}
