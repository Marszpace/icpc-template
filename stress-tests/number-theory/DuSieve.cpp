#include "../utilities/template.h"

#include "../../content/various/Int128.h"
#include "../../content/number-theory/DuSieve.h"

signed main() {
	// against sieved prefix sums, at every value n / i
	int LIM = 3000000;
	vector<int> phi(LIM + 1), mu(LIM + 1);
	vector<ll> sp(LIM + 1), sm(LIM + 1);
	iota(all(phi), 0);
	rep(i,2,LIM+1) if (phi[i] == i) for (int j = i; j <= LIM; j += i) phi[j] -= phi[j] / i;
	mu[1] = 1;
	rep(i,1,LIM+1) for (int j = 2 * i; j <= LIM; j += i) mu[j] -= mu[i];
	rep(i,1,LIM+1) sp[i] = sp[i-1] + phi[i], sm[i] = sm[i-1] + mu[i];
	mt19937_64 rng(2);
	rep(it,0,150) {
		ll n = (ll)(rng() % LIM) + 1;
		if (it < 30) n = it + 1;
		Du D(n);
		for (ll l = 1, r; l <= n; l = r + 1) {
			r = n / (n / l);
			ll v = n / l;
			assert(D.phi(v) == sp[v] && D.mu(v) == sm[v]);
		}
	}
	// Mertens function M(10^k)
	ll want[] = {1, -1, 1, 2, -23, -48, 212, 1037, 1928, -222, -33722};
	ll p10 = 1;
	rep(k,0,11) {
		Du D(p10);
		assert(D.mu(p10) == want[k]);
		p10 *= 10;
	}
	// Phi(n) = (1 + sum_d mu(d) floor(n/d)^2) / 2, and a known value
	for (ll n : {1000000000LL, 10000000000LL}) {
		Du D(n);
		__int128 s = 0;
		for (ll l = 1, r; l <= n; l = r + 1) {
			r = n / (n / l);
			s += (__int128)(D.mu(r) - D.mu(l - 1)) * (n / l) * (n / l);
		}
		assert((1 + s) / 2 == D.phi(n));
	}
	assert(to_string(Du(1000000000LL).phi(1000000000LL)) == "303963551173008414");
	cout<<"Tests passed!"<<endl;
}
