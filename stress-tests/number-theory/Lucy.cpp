#include "../utilities/template.h"

#include "../../content/number-theory/Lucy.h"

typedef unsigned long long ull;
ull tri(ull v) { return v % 2 ? v * ((v + 1) / 2) : (v / 2) * (v + 1); } // v(v+1)/2 modulo 2^64

signed main() {
	auto count = [](ll n) {
		return Lucy(n, [](ll) { return 1LL; }, [](ll v) { return v - 1; });
	};
	auto sums = [](ll n) {
		return Lucy(n, [](ll p) { return (ull)p; },
			[](ll v) { return tri((ull)v) - 1; });
	};
	auto squares = [](ll n) { // sum of p^2 modulo 2^64: g(v) = v(v+1)(2v+1)/6 - 1
		return Lucy(n, [](ll p) { return (ull)p * (ull)p; }, [](ll v) {
			unsigned __int128 x = (unsigned __int128)v * (v + 1) * (2 * v + 1) / 6;
			return (ull)x - 1;
		});
	};
	// against a sieve, at every value n / i and every v <= sqrt(n)
	int LIM = 2000000;
	vector<char> comp(LIM + 1);
	vector<ll> pc(LIM + 1);
	vector<ull> ps(LIM + 1), pq(LIM + 1);
	rep(i,2,LIM+1) {
		if (!comp[i]) for (ll j = (ll)i * i; j <= LIM; j += i) comp[(int)j] = 1;
		pc[i] = pc[i-1] + !comp[i];
		ps[i] = ps[i-1] + (comp[i] ? 0 : (ull)i);
		pq[i] = pq[i-1] + (comp[i] ? 0 : (ull)i * (ull)i);
	}
	mt19937_64 rng(1);
	rep(it,0,300) {
		ll n = (ll)(rng() % LIM) + 1;
		if (it < 60) n = it + 1; // tiny n too
		auto C = count(n);
		auto S = sums(n);
		auto Q = squares(n);
		for (ll l = 1, r; l <= n; l = r + 1) {
			r = n / (n / l);
			ll v = n / l;
			assert(C(v) == pc[v] && S(v) == ps[v] && Q(v) == pq[v]);
		}
		for (ll v = 1; v * v <= n; v++) assert(C(v) == pc[v] && S(v) == ps[v]);
	}
	// known values
	assert(count(1000000000LL)(1000000000LL) == 50847534);
	assert(count(10000000000LL)(10000000000LL) == 455052511);
	assert(sums(1000000000LL)(1000000000LL) == 24739512092254535ULL);
	clock_t st = clock();
	assert(count(100000000000LL)(100000000000LL) == 4118054813LL);
	assert((double)(clock() - st) / CLOCKS_PER_SEC < 20); // about 0.4 s
	cout<<"Tests passed!"<<endl;
}
