/**
 * Author: Simon Lindholm
 * Date: 2019-05-22
 * License: CC0
 * Description: $0 \le x < \mathrm{lcm}$ if $|a| < m$, $|b| < n$; asserts if none. Needs $mn < 2^{62}$.
 * Time: $\log(n)$
 * Status: Works
 */
#pragma once

#include "euclid.h"

ll crt(ll a, ll m, ll b, ll n) { // x = a (m), x = b (n)
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	assert((a - b) % g == 0); // else no solution
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}
