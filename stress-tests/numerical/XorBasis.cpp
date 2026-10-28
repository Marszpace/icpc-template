#include "../utilities/template.h"

#include "../../content/numerical/XorBasis.h"

int main() {
	srand(4);
	// small universe: compare against the explicitly enumerated span
	rep(it,0,20000) {
		const int B = 9;
		XorBasis xb;
		set<ull> span = {0};
		int m = rand() % 8;
		rep(i,0,m) {
			ull x = rand() % (1 << B);
			bool indep = !span.count(x);
			assert(xb.insert(x) == indep);
			if (indep) {
				set<ull> add;
				for (ull s : span) add.insert(s ^ x);
				span.insert(all(add));
			}
		}
		assert((1 << xb.rk) == sz(span));
		vector<ull> sorted(all(span));
		rep(x,0,1 << B) {
			assert(xb.has(x) == (span.count(x) > 0));
			ull best = 0;
			for (ull s : span) best = max(best, x ^ s);
			assert(xb.best(x) == best);
		}
		assert(xb.best() == sorted.back());
		rep(k,0,sz(sorted)) assert(xb.kth(k) == sorted[k]);
		// kth reduced the basis; everything must still hold
		rep(x,0,1 << B) assert(xb.has(x) == (span.count(x) > 0));
		assert(xb.best() == sorted.back());
	}
	// full 64-bit width: a random full-rank set spans everything
	{
		XorBasis xb;
		rep(i,0,64) {
			ull x = 0;
			rep(j,0,4) x = x << 16 | (rand() & 0xffff);
			x |= 1ULL << i; // keep it from being too structured
			xb.insert(x);
		}
		assert(xb.rk <= 64);
		ull x = ~0ULL;
		if (xb.rk == 64) assert(xb.has(x) && xb.best() == ~0ULL);
		// xor-sums of inserted vectors are always inside the span
		XorBasis yb;
		vector<ull> v;
		rep(i,0,20) {
			ull a = 0;
			rep(j,0,4) a = a << 16 | (rand() & 0xffff);
			v.push_back(a);
			yb.insert(a);
		}
		rep(i,0,2000) {
			ull s = 0;
			rep(j,0,20) if (rand() & 1) s ^= v[j];
			assert(yb.has(s));
			assert(!yb.insert(s));
		}
		assert(yb.rk == 20);
		ull k = (1ULL << 19) + 12345;
		ull a = yb.kth(k), b = yb.kth(k + 1);
		assert(a < b && yb.has(a) && yb.has(b));
	}
	cout << "Tests passed!" << endl;
}
