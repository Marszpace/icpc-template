/**
 * Author: Simon Lindholm
 * Date: 2015-02-11
 * License: CC0
 * Source: Wikipedia
 * Description: Simpson's rule with $2n$ intervals; error $\propto h^4$, check that the result is stable when $n$ changes.
 * Status: stress-tested
 */
#pragma once

template<class F>
double quad(double a, double b, F f, const int n = 1000) {
	double h = (b - a) / 2 / n, v = f(a) + f(b);
	rep(i,1,n*2)
		v += f(a + i*h) * (i&1 ? 4 : 2);
	return v * h / 3;
}
