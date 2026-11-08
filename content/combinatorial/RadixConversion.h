/**
 * Author: Claude
 * Date: 2026-11-08
 * License: CC0
 * Source: bijective numeration
 * Description: Converts a sequence of digits in $[0, a)$ to a sequence
 * of digits in $[0, b)$, with $a, b \ge 2$ (below $2^{31}$), most significant
 * first. It is a bijection between all finite sequences: the empty one
 * maps to the empty one, and the $k$-th sequence in (length, lexicographic)
 * order in base $a$ goes to the $k$-th in base $b$. So
 * \texttt{radixconv(radixconv(x, a, b), b, a) == x} always, with no length
 * or leading zeros to remember, and the result has about
 * $|x| \log_b a$ digits (e.g. to send $n$ numbers below $a$ in messages below $b$).
 * Time: O(|x| \cdot |y|), where $y$ is the result
 * Status: stress-tested
 */
#pragma once

vi radixconv(const vi& x, int a, int b) {
	vector<ll> y; // bijective base b (digits 1..b), least significant first
	for (int d : x) {
		ll c = d + 1; // y = y * a + (d + 1)
		for (ll& v : y) {
			ll t = v * a + c;
			v = (t - 1) % b + 1, c = (t - 1) / b;
		}
		for (; c; c = (c - 1) / b)
			y.push_back((c - 1) % b + 1);
	}
	vi r;
	for (int i = sz(y); i--;) r.push_back((int)(y[i] - 1));
	return r;
}
