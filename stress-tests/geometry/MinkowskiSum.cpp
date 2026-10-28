#include "../utilities/template.h"

#include "../../content/geometry/ConvexHull.h"
#include "../../content/geometry/MinkowskiSum.h"

vector<P> randConvex(int range, int maxPts) {
	while (true) {
		vector<P> pts;
		int n = 3 + rand() % maxPts;
		rep(i,0,n) pts.push_back(P(rand() % (2 * range + 1) - range, rand() % (2 * range + 1) - range));
		vector<P> h = convexHull(pts);
		if (sz(h) >= 3) return h;
	}
}

int main() {
	srand(123);
	rep(it,0,100000) {
		int range = it % 3 == 0 ? 3 : it % 3 == 1 ? 8 : 100000000;
		vector<P> a = randConvex(range, 8), b = randConvex(range, 8);
		// random cyclic shifts: the function must not depend on the start
		rotate(a.begin(), a.begin() + rand() % sz(a), a.end());
		rotate(b.begin(), b.begin() + rand() % sz(b), b.end());
		vector<P> r = minkowski(a, b);
		vector<P> all_;
		for (P p : a) for (P q : b) all_.push_back(p + q);
		vector<P> want = convexHull(all_);
		// r must be exactly the hull: same vertices, ccw, strictly convex
		assert(sz(r) == sz(want));
		rep(i,0,sz(r)) assert(r[i].cross(r[(i + 1) % sz(r)], r[(i + 2) % sz(r)]) > 0);
		vector<P> s = r;
		sort(all(s)); sort(all(want));
		assert(s == want);
	}
	cout << "Tests passed!" << endl;
}
