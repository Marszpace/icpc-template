#include "../utilities/template.h"

#include "../../content/geometry/HalfPlane.h"

typedef Point<double> P;
typedef pair<P, P> HP;

// Sutherland-Hodgman: keep the part of poly on the left of s->e
vector<P> clip(const vector<P>& poly, P s, P e) {
	vector<P> r;
	int n = sz(poly);
	rep(i,0,n) {
		P a = poly[i], b = poly[(i + 1) % n];
		double ca = (e - s).cross(a - s), cb = (e - s).cross(b - s);
		if (ca >= 0) r.push_back(a);
		if ((ca > 0 && cb < 0) || (ca < 0 && cb > 0))
			r.push_back(a + (b - a) * (ca / (ca - cb)));
	}
	return r;
}

double signedArea(const vector<P>& p) {
	double s = 0;
	rep(i,0,sz(p)) s += p[i].cross(p[(i + 1) % sz(p)]);
	return s / 2;
}

int main() {
	srand(8);
	const double R = 100;
	vector<HP> box;
	{
		P c[4] = {P(-R,-R), P(R,-R), P(R,R), P(-R,R)};
		rep(i,0,4) box.push_back({c[i], c[(i + 1) % 4]});
	}
	int nonEmpty = 0, empty = 0;
	rep(it,0,300000) {
		bool ints = it % 2;
		int pin = (it / 2) % 2 ? 85 : 20; // % of half-planes that keep `inside`
		int n = 1 + rand() % 8;
		P inside(rand() % 7 - 3 + 0.5, rand() % 7 - 3 + 0.25);
		vector<HP> h = box;
		rep(i,0,n) {
			P s, d;
			if (ints) {
				s = P(rand() % 9 - 4, rand() % 9 - 4);
				do d = P(rand() % 7 - 3, rand() % 7 - 3); while (d.x == 0 && d.y == 0);
				d = d * (1 + rand() % 3);
			} else {
				s = P(rand() % 2001 / 100.0 - 10, rand() % 2001 / 100.0 - 10);
				double ang = rand() / (double)RAND_MAX * 2 * M_PI;
				d = P(cos(ang), sin(ang)) * (0.5 + rand() % 100 / 50.0);
			}
			// usually keep `inside` on the left so the result is often non-empty
			if (rand() % 100 < pin && d.cross(inside - s) < 0) d = d * -1;
			h.push_back({s, s + d});
		}
		shuffle(all(h), mt19937(rand()));
		vector<P> res = halfPlanes(h);

		vector<P> poly = {P(-R,-R), P(R,-R), P(R,R), P(-R,R)};
		for (HP& l : h) {
			poly = clip(poly, l.first, l.second);
			if (poly.empty()) break;
		}
		double want = poly.empty() ? 0 : fabs(signedArea(poly));
		double got = res.empty() ? 0 : signedArea(res);
		assert(got >= -1e-7);
		assert(fabs(want - got) <= 1e-6 * (1 + want));
		(want > 1e-6 ? nonEmpty : empty)++;
		// all returned vertices satisfy every half-plane
		for (P& p : res) for (HP& l : h)
			assert((l.second - l.first).cross(p - l.first) >= -1e-5 * (1 + (l.second - l.first).dist()));
		// convexity
		rep(i,0,sz(res)) {
			P a = res[i], b = res[(i + 1) % sz(res)], c = res[(i + 2) % sz(res)];
			assert(a.cross(b, c) >= -1e-6);
		}
	}
	cerr << "non-empty: " << nonEmpty << ", empty/degenerate: " << empty << endl;
	assert(nonEmpty > 20000 && empty > 20000);
	cout << "Tests passed!" << endl;
}
