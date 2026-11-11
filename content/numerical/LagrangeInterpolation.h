/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: folklore
 * Description: $f(x) \bmod p$ from $y_i = f(i)$, $i < n$, $\deg f < n$, $p$ prime $> n$.
 * Sums of powers: $\sum_{i \le x} i^k$ has degree $k+1$, so give it $k+2$ prefix sums.
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

#include "../number-theory/ModPow.h"

ll lagrange(const vector<ll>& y, ll x) {
	int n = sz(y);
	x = (x % mod + mod) % mod;
	if (x < n) return y[x];
	vector<ll> pre(n + 1, 1), suf(n + 1, 1), ifact(n, 1);
	rep(i,0,n) pre[i+1] = pre[i] * ((x - i + mod) % mod) % mod;
	for (int i = n; i--;) suf[i] = suf[i+1] * ((x - i + mod) % mod) % mod;
	ll f = 1;
	rep(i,1,n) f = f * i % mod;
	ifact[n-1] = modpow(f, mod - 2);
	for (int i = n-1; i--;) ifact[i] = ifact[i+1] * (i+1) % mod;
	ll ans = 0;
	rep(i,0,n) {
		ll t = y[i] * pre[i] % mod * suf[i+1] % mod * ifact[i] % mod * ifact[n-1-i] % mod;
		ans = (ans + ((n - 1 - i) & 1 ? mod - t : t)) % mod;
	}
	return ans;
}
