#include "../utilities/template.h"

#include "../../content/numerical/PolyInterpolate.h"

mt19937 rng(7);
int rnd(int n) { return (int)(rng() % (unsigned)n); }

signed main() {
	rep(it,0,100000) {
		int n = rnd(8) + 1;
		vd c(n);
		for (double& x : c) x = rnd(11) - 5;
		vi xs(21); iota(all(xs), -10); shuffle(all(xs), rng);
		vd x(n), y(n);
		rep(i,0,n) {
			x[i] = xs[i];
			rep(j,0,n) y[i] += c[j] * pow(x[i], j);
		}
		vd a = interpolate(x, y, n);
		assert(sz(a) == n);
		rep(i,0,n) assert(fabs(a[i] - c[i]) < 1e-6);
	}
	// the Chebyshev points from the description, degree 29
	{
		int n = 30;
		vd x(n), y(n);
		rep(k,0,n) x[k] = cos((double)k / (n - 1) * M_PI);
		auto f = [](double t) { return 1 / (1 + t * t); };
		rep(k,0,n) y[k] = f(x[k]);
		vd a = interpolate(x, y, n);
		rep(k,0,n) {
			double v = 0;
			for (int i = n; i--;) v = v * x[k] + a[i];
			assert(fabs(v - y[k]) < 1e-9);
		}
	}
	cout << "Tests passed!" << endl;
}
