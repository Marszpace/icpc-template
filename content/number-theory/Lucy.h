/**
 * Author: Claude
 * Date: 2026-11-09
 * License: CC0
 * Source: folklore (Lucy\_Hedgehog's method)
 * Description: Prime counting and prime sums for all $v = \lfloor n/i \rfloor$ and
 * all $v \le \sqrt n$. \texttt{f(p)} is a completely multiplicative function
 * at a prime (\texttt{1} counts, \texttt{p} sums, $p^k$ power sums) and
 * \texttt{g(v)} $= f(2) + \dots + f(v)$ in closed form; the type of \texttt{g(v)}
 * is the type of the result (use \texttt{ull} to sum modulo $2^{64}$).
 * \texttt{L(v)} is then $\sum_{p \le v} f(p)$ for such a $v$.
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
