/**
 * Author: Claude
 * Date: 2026-11-09
 * License: CC0
 * Source: folklore (Lucy\_Hedgehog's method)
 * Description: $\sum_{p \le v} f(p)$ over primes, for all $v = \lfloor n/i \rfloor$; $f$ completely multiplicative (\texttt{1}: count, \texttt{p}: sum),
 * \texttt{g(v)} $= f(2) + \dots + f(v)$ in closed form. The result type is \texttt{g}'s (\texttt{ull}: mod $2^{64}$).
 * Usage: Lucy L(n, [](ll) { return 1LL; }, [](ll v) { return v - 1; }); // L(n) = pi(n)
 * Time: O(n^{3/4}), about 0.4 s for $n = 10^{11}$
 * Status: stress-tested
 */
#pragma once

template<class F, class G> struct Lucy {
	typedef decltype(declval<G>()(0LL)) T;
	ll n, s; vector<T> lo, hi;
	Lucy(ll n, F f, G g) : n(n), s((ll)sqrtl((long double)n)),
			lo(s + 2), hi(s + 2) {
		while (s * s > n) s--;
		while ((s + 1) * (s + 1) <= n) s++;
		rep(i,1,s+1) lo[i] = g(i), hi[i] = g(n / i);
		for (ll p = 2; p <= s; p++) if (lo[p] != lo[p - 1]) {
			T fp = f(p), pre = lo[p - 1];
			for (ll i = 1; i <= s && n / i >= p * p; i++) {
				ll d = i * p;
				hi[i] -= fp * ((d <= s ? hi[d] : lo[n / d]) - pre);
			}
			for (ll v = s; v >= p * p; v--)
				lo[v] -= fp * (lo[v / p] - pre);
		}
	}
	T operator()(ll v) { return v <= s ? lo[v] : hi[n / v]; }
};
