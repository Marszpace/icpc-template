/**
 * Author: OI-wiki (exLucas), bug-fixed
 * Date: 2026-10-30
 * License: CC0
 * Source: https://oi-wiki.org/math/number-theory/lucas/
 * Description: Binomial $\binom{n}{k} \bmod m$ for any $m < 2^{31}$ (extended Lucas).
 * Per prime power $q = p^a$: $n!$ with factors $p$ removed (product of units mod $q$
 * is $-1$, or $+1$ if $p=2, a\ge3$) and $v_p(n!)$ by Legendre; then CRT with $c \equiv [q]$.
 * Requires $n \le mx$; tables have size $\min(q, mx+1)$.
 * Usage: BinomMod C(m, maxn); C(n, k);
 * Time: $O(\sqrt m + \omega(m) \cdot mx)$ build, $O(\omega(m) \log n)$ per query.
 * Status: stress-tested vs. exact big integers; AC on CF 896D
 */
#pragma once

#include "euclid.h"

struct BinomPP {
	ll p, q, c, a = 0; vector<ll> f;
	ll inv(ll b) { ll x, y; euclid(b, q, x, y); return (x % q + q) % q; }
	BinomPP(ll p, ll q, ll mx, ll m) : p(p), q(q), f(min(q, mx + 1), 1) {
		rep(i,1,sz(f)) f[i] = f[i-1] * (i % p ? i : 1) % q;
		c = m / q * inv(m / q % q) % m;
		for (ll t = q; t > 1; t /= p) a++;
	}
	ll nu(ll n) { ll e = 0; while (n /= p) e += n; return e; } // v_p(n!)
	ll fact(ll n) { // n! / p^nu(n) mod q
		ll r = 1;
		for (; n; n /= p) {
			if ((p != 2 || q <= 4) && n / q % 2) r = q - r;
			r = r * f[n % q] % q;
		}
		return r;
	}
	ll C(ll n, ll k) {
		ll e = nu(n) - nu(k) - nu(n - k), r;
		if (e >= a) return 0;
		for (r = fact(n) * inv(fact(k) * fact(n - k) % q) % q; e--;) r = r * p % q;
		return r;
	}
};

struct BinomMod {
	ll m; vector<BinomPP> v;
	BinomMod(ll m, ll mx) : m(m) {
		for (ll p = 2, x = m; x > 1; p++) {
			if (p * p > x) p = x;
			ll q = 1;
			while (x % p == 0) x /= p, q *= p;
			if (q > 1) v.emplace_back(p, q, mx, m);
		}
	}
	ll operator()(ll n, ll k) {
		if (k < 0 || k > n) return 0;
		ll r = 0;
		for (auto& b : v) r = (r + b.C(n, k) * b.c) % m;
		return r;
	}
};