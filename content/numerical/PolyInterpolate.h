/**
 * Author: Simon Lindholm
 * Date: 2017-05-10
 * License: CC0
 * Source: Wikipedia
 * Description: Coefficients $a$ of the degree $n-1$ polynomial through $(x_i, y_i)$. Precision: pick $x_k = c\cos(k\pi/(n-1))$.
 * Time: O(n^2)
 * Status: stress-tested
 */
#pragma once

typedef vector<double> vd;
vd interpolate(vd x, vd y, int n) { // p(x) = sum a_i x^i
	vd res(n), temp(n);
	rep(k,0,n-1) rep(i,k+1,n)
		y[i] = (y[i] - y[k]) / (x[i] - x[k]);
	double last = 0; temp[0] = 1;
	rep(k,0,n) rep(i,0,n) {
		res[i] += y[k] * temp[i];
		swap(last, temp[i]);
		temp[i] -= last * x[k];
	}
	return res;
}
