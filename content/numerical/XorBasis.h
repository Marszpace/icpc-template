/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: folklore (xor basis / linear basis over GF(2))
 * Description: Basis of the span of the inserted 64-bit numbers under xor.
 * \texttt{insert} returns whether $x$ was independent. \texttt{has(x)}
 * tests $x \in$ span. \texttt{best(x)} is the maximum of $x \oplus s$ over
 * the span ($x = 0$: maximum element). \texttt{kth(k)} is the $k$-th
 * smallest element of the span (0-indexed, $k < 2^{\texttt{rk}}$);
 * it makes the basis reduced, which is harmless.
 * Time: O(64) per operation
 * Status: stress-tested
 */
#pragma once

typedef unsigned long long ull;
struct XorBasis {
	ull b[64] = {}; int rk = 0;
	bool insert(ull x) {
		for (int i = 64; i--;) if (x >> i & 1) {
			if (!b[i]) { b[i] = x; rk++; return 1; }
			x ^= b[i];
		}
		return 0;
	}
	bool has(ull x) {
		for (int i = 64; i--;) if (x >> i & 1) {
			if (!b[i]) return 0;
			x ^= b[i];
		}
		return 1;
	}
	ull best(ull x = 0) {
		for (int i = 64; i--;) x = max(x, x ^ b[i]);
		return x;
	}
	ull kth(ull k) {
		rep(i,0,64) rep(j,0,i) if (b[j] && (b[i] >> j & 1)) b[i] ^= b[j];
		ull r = 0; int t = 0;
		rep(i,0,64) if (b[i] && (k >> t++ & 1)) r ^= b[i];
		return r;
	}
};
