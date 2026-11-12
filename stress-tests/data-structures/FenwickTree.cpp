#include "../utilities/template.h"

#include "../../content/data-structures/FenwickTree.h"

signed main() {
	rep(it,0,100000) {
		int N = rand() % 10;
		FT fw(N);
		vi t(N);
		rep(i,0,N) {
			int v = rand() % 3;
			fw.update(i, v);
			t[i] += v;
		}
		int q = rand() % 20;
		int ind = fw.lower_bound(q);
		int res = -1, sum = 0;
		rep(i,0,N+1) {
			if (sum < q) res = i;
			if (i != N) sum += t[i];
		}
		assert(res == ind);
	}
	// update / query against prefix sums: 0-indexed, query(pos) = sum of [0, pos), negative updates allowed
	rep(it,0,50000) {
		int N = rand() % 40;
		FT fw(N);
		vector<ll> t(N);
		rep(op,0,30) {
			if (N && rand() % 2) {
				int i = rand() % N; ll d = rand() % 2001 - 1000;
				fw.update(i, d); t[i] += d;
			}
			int pos = rand() % (N + 1);
			ll want = 0;
			rep(i,0,pos) want += t[i];
			assert(fw.query(pos) == want);
		}
		ll tot = 0;
		rep(i,0,N+1) { assert(fw.query(i) == tot); if (i < N) tot += t[i]; }
	}
	// lower_bound on bigger arrays (the power-of-two descent has to start high enough)
	rep(it,0,2000) {
		int N = rand() % 300;
		FT fw(N);
		vi t(N);
		int tot = 0;
		rep(i,0,N) { t[i] = rand() % 4; fw.update(i, t[i]); tot += t[i]; }
		rep(k,0,10) {
			int q = rand() % (tot + 3) - 1;
			int res = -1, sum = 0;
			rep(i,0,N+1) {
				if (sum < q) res = i;
				if (i != N) sum += t[i];
			}
			assert(fw.lower_bound(q) == (q <= 0 ? -1 : res));
		}
	}
	// large values, and the whole range
	{
		FT fw(1000);
		ll sum = 0;
		rep(i,0,1000) { ll d = (ll)1e15 + i; fw.update(i, d); sum += d; }
		assert(fw.query(1000) == sum && fw.query(0) == 0 && fw.query(1) == (ll)1e15);
	}
	cout<<"Tests passed!"<<endl;
}
