#include "../utilities/template.h"

#include "../../content/numerical/Polynomial.h"

mt19937 rng(6);
int rnd(int n) { return (int)(rng() % (unsigned)n); }

signed main() {
	rep(it,0,100000) {
		int d = rnd(8);
		vector<double> r(d + 1);
		for (double& x : r) x = rnd(11) - 5;
		double x0 = rnd(9) - 4;
		// p = (x - x0) * r
		Poly p; p.a.assign(d + 2, 0);
		rep(i,0,d+1) p.a[i+1] += r[i], p.a[i] -= x0 * r[i];
		// evaluation
		double x = (rnd(2001) - 1000) / 250.0, want = 0, pw = 1;
		rep(i,0,d+2) want += p.a[i] * pw, pw *= x;
		assert(fabs(p(x) - want) <= 1e-9 * max(1.0, fabs(want)));
		assert(fabs(p(x0)) < 1e-9);
		// derivative
		Poly q = p; q.diff();
		assert(sz(q.a) == d + 1);
		rep(i,0,d+1) assert(q.a[i] == (i + 1) * p.a[i+1]);
		// division by (x - x0)
		Poly s = p; s.divroot(x0);
		assert(sz(s.a) == d + 1);
		rep(i,0,d+1) assert(fabs(s.a[i] - r[i]) < 1e-9);
	}
	// divroot when x0 is not a root: quotient of p by (x - x0), remainder dropped
	rep(it,0,10000) {
		int d = rnd(6) + 1;
		Poly p; p.a.resize(d + 1);
		for (double& x : p.a) x = rnd(11) - 5;
		double x0 = rnd(9) - 4, rem = p(x0);
		Poly s = p; s.divroot(x0);
		rep(t,0,5) {
			double x = rnd(9) - 4;
			assert(fabs((x - x0) * s(x) + rem - p(x)) < 1e-6);
		}
	}
	cout << "Tests passed!" << endl;
}
