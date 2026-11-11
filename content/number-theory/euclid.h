/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Returns $\gcd(a, b)$; if coprime, $x = a^{-1} \bmod b$.
 */
#pragma once

ll euclid(ll a, ll b, ll &x, ll &y) { // ax + by = gcd
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}
