/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: folklore
 * Description: Smallest primitive root of the prime $p$ ($p \le 7 \cdot 10^{18}$,
 * but $p - 1$ is factored by trial division, so $p \lesssim 10^{12}$; use \texttt{Factor} beyond).
 * A primitive root $g$ has order $p - 1$; e.g. 998244353 has $g = 3$, $10^9 + 7$ has $g = 5$.
 * Time: O(\sqrt p + \log^2 p) expected
 * Status: stress-tested
 */
#pragma once

#include "ModMulLL.h"

ull primitiveRoot(ull p) {
	if (p == 2) return 1;
	vector<ull> f;
	ull m = p - 1;
	for (ull d = 2; d * d <= m; d++) if (m % d == 0) {
		f.push_back(d);
		while (m % d == 0) m /= d;
	}
	if (m > 1) f.push_back(m);
	for (ull g = 2;; g++) {
		bool ok = 1;
		for (ull q : f) ok &= modpow(g, (p - 1) / q, p) != 1;
		if (ok) return g;
	}
}
