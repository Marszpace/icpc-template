/**
 * Author: Simon Lindholm
 * Date: 2015-05-12
 * License: CC0
 * Source: own work
 * Description: $f$ strictly increasing, then non-increasing. Strict on the other side: \texttt{<=} at (A) and reverse (B).
 * For the minimum, \texttt{>} at (A) and (B).
 * Usage:
 * 	int ind = ternSearch(0,n-1,[\&](int i){return a[i];});
 * Time: O(\log(b-a))
 * Status: tested; stress-tested
 */
#pragma once

template<class F>
int ternSearch(int a, int b, F f) { // smallest argmax
	assert(a <= b);
	while (b - a >= 5) {
		int mid = (a + b) / 2;
		if (f(mid) < f(mid+1)) a = mid; // (A)
		else b = mid+1;
	}
	rep(i,a+1,b+1) if (f(a) < f(i)) a = i; // (B)
	return a;
}
