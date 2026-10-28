#include "../utilities/template.h"

#include "../../content/numerical/LagrangeInterpolation.h"

int main() {
	srand(15);
	rep(it,0,20000) {
		int n = 1 + rand() % 20, d = rand() % n;
		vector<ll> coef(d + 1), y(n);
		rep(i,0,d+1) coef[i] = rand() % 3 ? rand() % 100 : (ll)rand() * rand() % mod;
		auto eval = [&](ll x) {
			x = (x % mod + mod) % mod;
			ll r = 0;
			for (int i = d; i >= 0; i--) r = (r * x + coef[i]) % mod;
			return r;
		};
		rep(i,0,n) y[i] = eval(i);
		ll xs[] = {rand() % 30 - 5, rand() % 1000, (ll)rand() * rand() - (ll)rand() * rand(),
			mod - 1, mod, mod + 3, 1000000000000000000LL, -1000000000000000000LL, n - 1, n, n + 1};
		for (ll x : xs) assert(lagrange(y, x) == eval(x));
	}
	// sum of cubes through k + 2 prefix sums
	vector<ll> y(6);
	rep(i,0,6) y[i] = ((ll)i * (i + 1) / 2) * ((ll)i * (i + 1) / 2) % mod;
	for (ll N : {10LL, 1000000LL, 123456789012LL}) {
		ll t = (N % mod) * ((N + 1) % mod) % mod * ((mod + 1) / 2) % mod;
		assert(lagrange(y, N) == t * t % mod);
	}
	// linear time on a million points
	vector<ll> big(1000000);
	rep(i,0,sz(big)) big[i] = (ll)i * 3 % mod; // f(x) = 3x
	assert(lagrange(big, 987654321) == 987654321LL * 3 % mod);
	cout << "Tests passed!" << endl;
}
