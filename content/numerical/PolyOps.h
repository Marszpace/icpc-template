/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: https://cp-algorithms.com/algebra/polynomial.html
 * Description: Power series modulo $x^n$ (coefficients in $[0, mod)$, NTT prime).
 * \texttt{polyInv} needs $a_0 \ne 0$, \texttt{polyLog} needs $a_0 = 1$, \texttt{polyExp} needs $a_0 = 0$.
 * All results have exactly $n$ coefficients.
 * \texttt{polyPow(a, k, n)} is $a^k \bmod x^n$ for any $a$ (also with leading zeros) and $k$ up to $10^{18}$;
 * \texttt{polySqrt} needs $a_0 = 1$; \texttt{polyDivMod(a, b)} returns $(q, r)$ with $a = qb + r$,
 * $\deg r < \deg b$, and needs \texttt{b.back() != 0}.
 * Usage: polyExp(polyLog(a, n), n) == a
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

#include "NumberTheoreticTransform.h"

vl polyInv(vl a, int n) {
	vl b = {modpow(a[0], mod - 2)};
	for (int m = 1; m < n; m *= 2) {
		vl f(a.begin(), a.begin()+min(sz(a), 2*m)), c = conv(f, b);
		c.resize(2 * m);
		for (ll& x : c) x = (mod - x) % mod;
		c[0] = (c[0] + 2) % mod;
		b = conv(b, c); b.resize(2 * m);
	}
	b.resize(n); return b;
}
vl polyDer(vl a) {
	rep(i,1,sz(a)) a[i-1] = a[i] * i % mod;
	if (!a.empty()) a.pop_back();
	return a;
}
vl polyInt(vl a) {
	a.insert(a.begin(), 0);
	vl inv(sz(a), 1);
	rep(i,2,sz(a)) inv[i] = (mod - mod/i*inv[mod%i] % mod) % mod;
	rep(i,1,sz(a)) a[i] = a[i] * inv[i] % mod;
	return a;
}
vl polyLog(vl a, int n) {
	vl c = conv(polyDer(a), polyInv(a, n));
	c.resize(n - 1); return polyInt(c);
}
vl polyExp(vl a, int n) {
	vl b = {1};
	for (int m = 1; m < n; m *= 2) {
		vl l = polyLog(b, 2 * m), f(2 * m);
		rep(i,0,2*m) f[i] = ((i<sz(a) ? a[i] : 0)-l[i]+mod) % mod;
		f[0] = (f[0] + 1) % mod;
		b = conv(b, f); b.resize(2 * m);
	}
	b.resize(n); return b;
}
vl polyPow(vl a, ll k, int n) { // a^k mod x^n, k >= 0
	int z = 0;
	while (z < sz(a) && !a[z]) z++;
	vl r(n);
	if (!k) { r[0] = n > 0; return r; }
	if (z == sz(a) || z > (n - 1) / k) return r; // z * k >= n
	int m = n - (int)(z * k);
	ll c = a[z], ci = modpow(c, mod - 2);
	vl b(a.begin() + z, a.end());
	for (ll& x : b) x = x * ci % mod;
	b = polyLog(b, m); // a^k = c^k x^(zk) exp(k log b)
	for (ll& x : b) x = x * (k % mod) % mod;
	b = polyExp(b, m);
	ll ck = modpow(c, k);
	rep(i,0,m) r[z * k + i] = b[i] * ck % mod;
	return r;
}
vl polySqrt(vl a, int n) { // a[0] = 1
	return polyPow(a, (mod + 1) / 2, n);
}
pair<vl, vl> polyDivMod(vl a, vl b) {
	int n = sz(a), m = sz(b);
	if (n < m) return {{}, a};
	vl ra(a.rbegin(), a.rend()), rb(b.rbegin(), b.rend());
	vl q = conv(ra, polyInv(rb, n - m + 1)), r = b;
	q.resize(n - m + 1), reverse(all(q));
	r = conv(b, q);
	rep(i,0,m-1) r[i] = (a[i] - r[i] + mod) % mod;
	r.resize(m - 1);
	return {q, r};
}
