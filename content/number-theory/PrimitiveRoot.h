/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: folklore
 * Description: Smallest primitive root. 998244353: 3, $10^9 + 7$: 5.
 * Time: O(\sqrt p + \log^2 p) expected
 * Status: stress-tested
 */
#pragma once

#include "ModMulLL.h"

ull primitiveRoot(ull p) { // prime p <~ 1e12; else Factor
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
