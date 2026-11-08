#include "../utilities/template.h"

#include "../../content/numerical/Integrate.h"

signed main() {
	auto near = [](double a, double b, double eps) { return fabs(a - b) <= eps * max(1.0, fabs(b)); };
	// Simpson is exact for cubics
	rep(t,0,1000) {
		double c0 = t % 7 - 3, c1 = t % 5 - 2, c2 = t % 3 - 1, c3 = t % 11 - 5;
		double a = t % 13 - 6, b = a + t % 17 - 8; // b < a is allowed and gives the negative
		auto f = [&](double x) { return ((c3 * x + c2) * x + c1) * x + c0; };
		auto F = [&](double x) { return (((c3 / 4 * x + c2 / 3) * x + c1 / 2) * x + c0) * x; };
		assert(near(quad(a, b, f, 1), F(b) - F(a), 1e-9));
		assert(near(quad(a, b, f), F(b) - F(a), 1e-9));
	}
	assert(near(quad(0, M_PI, [](double x) { return sin(x); }), 2, 1e-11));
	assert(near(quad(0, 1, [](double x) { return 4 / (1 + x * x); }), M_PI, 1e-12));
	assert(near(quad(-3, 2, [](double x) { return exp(x); }), exp(2) - exp(-3), 1e-11));
	assert(near(quad(1, 0, [](double x) { return x * x; }), -1.0 / 3, 1e-12));
	// error ~ h^4: halving h cuts the error by about 16
	{
		auto f = [](double x) { return exp(sin(3 * x)); };
		double exact = quad(0, 2, f, 200000);
		double e1 = fabs(quad(0, 2, f, 50) - exact), e2 = fabs(quad(0, 2, f, 100) - exact);
		assert(e1 / e2 > 12 && e1 / e2 < 20);
	}
	// non-smooth integrand (sqrt at 0) still converges, only slower
	assert(near(quad(0, 1, [](double x) { return sqrt(x); }), 2.0 / 3, 1e-5));
	// double integral: area of the unit disk
	{
		auto inner = [](double x) { double h = sqrt(max(0.0, 1 - x * x)); return quad(-h, h, [](double) { return 1.0; }, 10); };
		assert(near(quad(-1, 1, inner, 1000), M_PI, 1e-4));
	}
	cout << "Tests passed!" << endl;
}
