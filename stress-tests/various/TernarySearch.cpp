#include "../utilities/template.h"

#include "../../content/various/TernarySearch.h"

mt19937 rng(9);
int rnd(int n) { return (int)(rng() % (unsigned)n); }

signed main() {
	rep(it,0,300000) {
		int len = rnd(it < 1000 ? 8 : 60) + 1, off = rnd(21) - 10, peak = rnd(len);
		vi v(len);
		// strictly increasing up to peak, then non-increasing (plateaus allowed, also at the peak)
		v[peak] = 1000;
		for (int i = peak; i--;) v[i] = v[i+1] - 1 - rnd(3);
		rep(i,peak+1,len) v[i] = v[i-1] - (rnd(3) ? 0 : 1 + rnd(3));
		int calls = 0;
		int r = ternSearch(off, off + len - 1, [&](int i) { calls++; assert(off <= i && i < off + len); return v[i - off]; });
		int best = (int)(max_element(all(v)) - v.begin());
		assert(r == off + best);
		assert(calls <= 4 * 64 + 20);
	}
	cout << "Tests passed!" << endl;
}
