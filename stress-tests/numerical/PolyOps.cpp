#include "../utilities/template.h"

typedef vector<ll> vl;
namespace ignore {
#include "../../content/number-theory/ModPow.h"
}
ll modpow(ll a, ll e);
#include "../../content/numerical/PolyOps.h"
ll modpow(ll a, ll e) {
	ll r = 1;
	for (a %= mod; e; e >>= 1, a = a * a % mod)
		if (e & 1) r = r * a % mod;
	return r;
}

// O(n^2) reference implementations from the defining recurrences
vl naiveInv(const vl& a, int n) {
	vl b(n);
	ll i0 = modpow(a[0], mod - 2);
	rep(k,0,n) {
		ll s = k == 0 ? 1 : 0;
		rep(j,1,k+1) s = (s - (j < sz(a) ? a[j] : 0) * b[k-j] % mod + mod) % mod;
		b[k] = s * i0 % mod;
	}
	return b;
}
vl naiveLog(const vl& a, int n) { // n L_n = n a_n - sum_{k=1}^{n-1} k L_k a_{n-k}
	vl L(n);
	rep(m,1,n) {
		ll s = m * (m < sz(a) ? a[m] : 0) % mod;
		rep(k,1,m) s = (s - k * L[k] % mod * (m - k < sz(a) ? a[m-k] : 0) % mod + mod) % mod;
		L[m] = s * modpow(m, mod - 2) % mod;
	}
	return L;
}
vl naiveExp(const vl& a, int n) { // n b_n = sum_{k=1}^n k a_k b_{n-k}
	vl b(n);
	b[0] = 1;
	rep(m,1,n) {
		ll s = 0;
		rep(k,1,m+1) s = (s + k * (k < sz(a) ? a[k] : 0) % mod * b[m-k]) % mod;
		b[m] = s * modpow(m, mod - 2) % mod;
	}
	return b;
}
vl randPoly(int len, ll a0, bool fixA0) {
	vl a(len);
	rep(i,0,len) a[i] = rand() % 2 ? rand() % 10 : ((ll)rand() * 7919 + rand()) % mod;
	if (len && fixA0) a[0] = a0;
	return a;
}

vl mulTrunc(const vl& a, const vl& b, int n) { // O(n^2) product mod x^n
	vl c(n);
	rep(i,0,min(n,sz(a))) rep(j,0,min(n-i,sz(b))) c[i + j] = (c[i + j] + a[i] * b[j]) % mod;
	return c;
}
vl naivePow(const vl& a, ll k, int n) { // repeated squaring
	vl r(n), base(a);
	if (n) r[0] = 1;
	base.resize(n);
	for (; k; k >>= 1, base = mulTrunc(base, base, n)) if (k & 1) r = mulTrunc(r, base, n);
	return r;
}
vl rnd(int len, int zeros) { // random polynomial with the first coefficients zero
	vl a = randPoly(len, 0, false);
	rep(i,0,min(zeros,len)) a[i] = 0;
	return a;
}

signed main() {
	srand(3);
	rep(it,0,1500) {
		int n = 1 + rand() % 70, len = 1 + rand() % 80;
		vl a = randPoly(len, 0, false);
		a[0] = 1 + rand() % 1000;
		assert(polyInv(a, n) == naiveInv(a, n));
		a[0] = 1;
		assert(polyLog(a, n) == naiveLog(a, n));
		a[0] = 0;
		assert(polyExp(a, n) == naiveExp(a, n));
		vl d = polyDer(a);
		assert(sz(d) == len - 1);
		vl back = polyInt(d); // integrating the derivative restores everything but a_0
		rep(i,1,len) assert(back[i] == a[i]);
	}
	// large sizes (not powers of two): inverse by multiplication, exp/log roundtrip
	for (int n : {1000, 1025, 4096, 5000}) {
		vl a = randPoly(n, 1, true);
		vl inv = polyInv(a, n), prod = conv(a, inv);
		assert(prod[0] == 1);
		rep(i,1,n) assert(prod[i] == 0);
		vl l = polyLog(a, n);
		assert(l[0] == 0);
		assert(polyExp(l, n) == a);
		vl z = a; z[0] = 0;
		assert(polyLog(polyExp(z, n), n) == z);
	}
	// polyPow: against repeated squaring, with leading zeros, the zero and the empty polynomial
	rep(it,0,3000) {
		int n = 1 + rand() % 40, z = it % 3 ? 0 : rand() % 5;
		vl a = rnd(rand() % 45, z);
		if (it % 17 == 0) fill(all(a), 0);
		ll k = it % 4 ? rand() % 12 : rand() % 1000;
		vl got = polyPow(a, k, n);
		assert(sz(got) == n && got == naivePow(a, k, n));
	}
	// huge exponents: a^mod = a_0 (Frobenius), (a^k1)^k2 = a^(k1 k2), x^k for k < n and k >= n
	rep(it,0,300) {
		int n = 1 + rand() % 60;
		vl a = rnd(1 + rand() % 50, 0);
		if (!a[0]) a[0] = 5;
		ll k1 = ((ll)rand() * rand()) % 1000000000000LL, k2 = rand() % 1000 + 1;
		vl w(n);
		w[0] = a[0];
		assert(polyPow(a, mod, n) == w);
		assert(polyPow(polyPow(a, k1, n), k2, n) == polyPow(a, k1 * k2, n));
		vl x = {0, 1};
		int e = rand() % (n + 3);
		vl xe = polyPow(x, e, n);
		rep(i,0,n) assert(xe[i] == (i == e));
		assert(polyPow(x, 1000000000000000000LL, n) == vl(n));
	}
	// polySqrt: s^2 = a and s_0 = 1
	rep(it,0,500) {
		int n = 1 + rand() % 60;
		vl a = rnd(1 + rand() % 70, 0);
		a[0] = 1;
		vl s = polySqrt(a, n), t = a;
		t.resize(n);
		assert(sz(s) == n && s[0] == 1 && mulTrunc(s, s, n) == t);
	}
	// polyDivMod: a = q b + r with deg r < deg b
	rep(it,0,3000) {
		int na = rand() % 60, nb = 1 + rand() % 35;
		vl a = rnd(na, 0), b = rnd(nb, 0);
		if (!b.back()) b.back() = 7;
		auto [q, r] = polyDivMod(a, b);
		if (na < nb) { assert(q.empty() && r == a); continue; }
		assert(sz(q) == na - nb + 1 && sz(r) == nb - 1);
		vl back = conv(b, q);
		back.resize(max(sz(back), sz(r)));
		rep(i,0,sz(r)) back[i] = (back[i] + r[i]) % mod;
		back.resize(na);
		assert(back == a);
	}
	cout << "Tests passed!" << endl;
}
