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

int main() {
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
	cout << "Tests passed!" << endl;
}
