#include "../utilities/template.h"

#include "../../content/geometry/linearTransformation.h"

signed main() {
	mt19937 rng(51);
	auto rd = [&]() { return (double)(int)(rng() % 2001) / 100 - 10; };
	rep(it,0,100000) {
		P p0(rd(), rd()), p1(rd(), rd()), q0(rd(), rd()), q1(rd(), rd()), r(rd(), rd());
		if ((p1 - p0).dist() < 1e-3) continue;
		auto T = [&](P x) { return linearTransformation(p0, p1, q0, q1, x); };
		// complex form: q0 + (r - p0) * (q1 - q0) / (p1 - p0)
		typedef complex<double> C;
		C c = C(q0.x, q0.y) + C(r.x - p0.x, r.y - p0.y) * C(q1.x - q0.x, q1.y - q0.y) / C(p1.x - p0.x, p1.y - p0.y);
		P t = T(r);
		assert(fabs(t.x - c.real()) < 1e-6 && fabs(t.y - c.imag()) < 1e-6);
		assert((T(p0) - q0).dist() < 1e-9 && (T(p1) - q1).dist() < 1e-6);
	}
	cout << "Tests passed!" << endl;
}
