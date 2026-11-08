#include "../utilities/template.h"

#include "../../content/geometry/kdTree.h"

signed main() {
	srand(52);
	rep(it,0,3000) {
		int n = 1 + rand() % 200, R = it % 3 == 0 ? 5 : it % 3 == 1 ? 1000 : 1000000000;
		vector<P> v(n);
		for (P& p : v) p = P(rand() % (2 * R + 1) - R, rand() % (2 * R + 1) - R); // duplicates likely for small R
		KDTree t(v);
		rep(q,0,50) {
			P p(rand() % (2 * R + 1) - R, rand() % (2 * R + 1) - R);
			if (q < 5) p = v[rand() % n]; // query a point of the set: distance 0
			T best = INF;
			for (P a : v) best = min(best, (a - p).dist2());
			auto r = t.nearest(p);
			assert(r.first == best && (r.second - p).dist2() == best);
			assert(find(all(v), r.second) != v.end());
		}
	}
	// all points equal
	{
		vector<P> v(1000, P(3, 4));
		KDTree t(v);
		assert(t.nearest(P(0, 0)).first == 25);
	}
	cout << "Tests passed!" << endl;
}
