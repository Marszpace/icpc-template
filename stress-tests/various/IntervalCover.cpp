#include "../utilities/template.h"

#include "../../content/various/IntervalCover.h"

signed main() {
	srand(46);
	rep(it,0,100000) {
		int n = rand() % 9;
		vector<pii> I(n);
		for (auto& [a, b] : I) { a = rand() % 12; b = a + rand() % 6; } // empty intervals allowed
		int g0 = rand() % 12, g1 = g0 + rand() % 8 - 1;
		pii G(g0, g1);
		auto covers = [&](const vi& S) {
			rep(x,G.first,G.second) {
				bool ok = 0;
				for (int i : S) ok |= I[i].first <= x && x < I[i].second;
				if (!ok) return false;
			}
			return true;
		};
		int best = INT_MAX;
		rep(mask,0,1 << n) {
			vi S;
			rep(i,0,n) if (mask >> i & 1) S.push_back(i);
			if (covers(S)) best = min(best, sz(S));
		}
		vi r = cover(G, I);
		set<int> u(all(r));
		assert(sz(u) == sz(r));
		for (int i : r) assert(0 <= i && i < n);
		if (G.first >= G.second) assert(r.empty());
		else if (best == INT_MAX) assert(r.empty());
		else assert(covers(r) && sz(r) == best);
	}
	// doubles
	{
		vector<pair<double, double>> I = {{0, 0.5}, {0.4, 1.2}, {0.1, 0.9}, {1.1, 2}};
		vi r = cover(make_pair(0.0, 2.0), I);
		assert(sz(r) == 3);
		assert(cover(make_pair(0.0, 2.5), I).empty());
	}
	cout << "Tests passed!" << endl;
}
