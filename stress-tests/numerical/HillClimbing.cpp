#include "../utilities/template.h"

#include "../../content/numerical/HillClimbing.h"

signed main() {
	mt19937 rng(8);
	rep(it,0,200) {
		double cx = (int)(rng() % 2001) - 1000, cy = (int)(rng() % 2001) - 1000;
		double sx = (int)(rng() % 2001) - 1000, sy = (int)(rng() % 2001) - 1000;
		double w = (int)(rng() % 10) + 1;
		// smooth convex bowl, anisotropic
		auto f = [&](P p) { return (p[0] - cx) * (p[0] - cx) + w * (p[1] - cy) * (p[1] - cy); };
		auto r = hillClimb(P{sx, sy}, f);
		assert(fabs(r.second[0] - cx) < 1e-6 && fabs(r.second[1] - cy) < 1e-6);
		assert(fabs(r.first - f(r.second)) < 1e-12);
		// non-smooth convex (L1 / L-infinity mix)
		auto g = [&](P p) { return fabs(p[0] - cx) + 2 * fabs(p[1] - cy) + max(fabs(p[0] - cx), fabs(p[1] - cy)); };
		auto s = hillClimb(P{sx, sy}, g);
		assert(s.first < 1e-6);
	}
	// far from the start: the first jumps (1e9) matter
	{
		auto f = [](P p) { return fabs(p[0] - 3e8) + fabs(p[1] + 7e8); };
		auto r = hillClimb(P{0, 0}, f);
		assert(r.first < 1e-3);
	}
	cout << "Tests passed!" << endl;
}
