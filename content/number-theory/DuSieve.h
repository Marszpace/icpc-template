/**
 * Author: Claude
 * Date: 2026-11-09
 * License: CC0
 * Source: folklore (Du's sieve)
 * Description: Prefix sums $\Phi$ (128-bit) and $M$ of $\phi$ and $\mu$ at any $v = \lfloor n/i \rfloor$ or $v \le n^{2/3}$.
 * Any $f$ with $f * g = h$ and known prefix sums $G$, $H$: $S_f(v) = (H(v) - \sum_{d \ge 2} g(d) S_f(\lfloor v/d \rfloor))/g(1)$.
 * Usage: Du D(n); D.phi(n); D.mu(n); // also D.phi(n / 3)
 * Time: O(n^{2/3}), about 0.3 s for $n = 10^{10}$
 * Status: stress-tested
 */
#pragma once

struct Du {
	typedef __int128 L;
	ll n, B; vector<ll> sp, sm, bm; vector<L> bp;
	Du(ll n) : n(n), B(max<ll>(10, (ll)cbrtl((long double)n) *
			(ll)cbrtl((long double)n))), sp(B + 1), sm(B + 1) {
		vi pr, phi(B + 1), mu(B + 1);
		phi[1] = mu[1] = 1;
		rep(i,2,B+1) {
			if (!phi[i])
				pr.push_back((int)i), phi[i] = (int)i - 1, mu[i] = -1;
			for (int p : pr) {
				if ((ll)i * p > B) break;
				if (i % p) {
					phi[i * p] = phi[i] * (p - 1), mu[i * p] = -mu[i];
				} else {
					phi[i * p] = phi[i] * p, mu[i * p] = 0;
					break;
				}
			}
		}
		rep(i,1,B+1) {
			sp[i] = sp[i-1] + phi[i], sm[i] = sm[i-1] + mu[i];
		}
		ll K = n / B;
		bp.resize(K + 1), bm.resize(K + 1);
		for (ll i = K; i >= 1; i--) {
			ll v = n / i, m = 1; L p = (L)v * (v + 1) / 2;
			for (ll l = 2, r; l <= v; l = r + 1) {
				r = v / (v / l);
				ll d = i * l; // v / l = n / d
				p -= (L)(r - l + 1) * (d <= K ? bp[d] : (L)sp[n / d]);
				m -= (r - l + 1) * (d <= K ? bm[d] : sm[n / d]);
			}
			bp[i] = p, bm[i] = m;
		}
	}
	L phi(ll v) { return v <= B ? (L)sp[v] : bp[n / v]; }
	ll mu(ll v) { return v <= B ? sm[v] : bm[n / v]; }
};
