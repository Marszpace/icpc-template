/**
 * Author: OI-wiki (exLucas), bug-fixed
 * Date: 2026-10-30
 * License: CC0
 * Source: https://oi-wiki.org/math/number-theory/lucas/
 * Description: Binomial $\binom{n}{k} \bmod m$ for any $m < 2^{31}$ (extended Lucas).
 * Splits $m$ into prime powers $p^a$, computes $n!$ with all factors $p$ removed
 * (product of units mod $p^a$ is $-1$, or $+1$ if $p=2, a\ge3$), counts $v_p$ by
 * Legendre, then combines with CRT. Requires $n \le mx$ in every query; tables have
 * size $\min(p^a, mx+1)$, so a huge prime factor of $m$ is fine.
 * Usage: BinomMod C(m, maxn); C(n, k);
 * Time: $O(\sqrt m + \omega(m) \cdot mx)$ build, $O(\omega(m) \log n)$ per query.
 * Status: stress-tested vs. exact big integers; AC on CF 896D
 */
#pragma once

#include "euclid.h"

struct BinomPP {
	ll p, a, pa; vector<ll> f;
	BinomPP(ll p, ll a, ll pa, ll mx) : p(p), a(a), pa(pa), f(min(pa, mx + 1)) {
		f[0] = 1;
		rep(i,1,sz(f)) f[i] = i % p ? f[i-1] * i % pa : f[i-1];
	}
	ll nu(ll n) { ll c = 0; while (n /= p) c += n; return c; }
	ll fact(ll n) { // n! without factors p, mod pa
		ll r = 1; bool neg = p != 2 || pa <= 4;
		for (; n > 1; n /= p) {
			if (neg && (n / pa) % 2) r = pa - r;
			r = r * f[n % pa] % pa;
		}
		return r;
	}
	ll inv(ll x) { ll u, v; euclid(x, pa, u, v); return (u % pa + pa) % pa; }
	ll C(ll n, ll k) {
		ll v = nu(n) - nu(k) - nu(n - k);
		if (v >= a) return 0;
		ll r = fact(n) * inv(fact(k) * fact(n - k) % pa) % pa;
		while (v--) r = r * p % pa;
		return r;
	}
};

struct BinomMod {
	ll m; vector<BinomPP> v; vector<ll> c;
	BinomMod(ll m, ll mx) : m(m) {
		ll x = m;
		for (ll p = 2; p * p <= x; p++) if (x % p == 0) {
			ll a = 0, pa = 1;
			while (x % p == 0) x /= p, a++, pa *= p;
			add(p, a, pa, mx);
		}
		if (x > 1) add(x, 1, x, mx);
	}
	void add(ll p, ll a, ll pa, ll mx) {
		v.emplace_back(p, a, pa, mx);
		ll q = m / pa;
		c.push_back(q * v.back().inv(q % pa) % m);
	}
	ll operator()(ll n, ll k) {
		if (k < 0 || k > n) return 0;
		ll r = 0;
		rep(i,0,sz(v)) r = (r + v[i].C(n, k) * c[i]) % m;
		return r;
	}
};
