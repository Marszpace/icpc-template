/**
 * Author: Claude
 * Date: 2026-11-08
 * License: CC0
 * Source: Bostan, Mori: A simple and fast algorithm for computing the N-th term of a linearly recurrent sequence
 * Description: Same as \texttt{linearRec} mod 998244353 (values in $[0, mod)$), $O(n \log n \log k)$:
 * halves $k$ via $P(x)Q(-x) / Q(x)Q(-x)$.
 * Usage: bostanMori({0, 1}, {1, 1}, k) // k'th Fibonacci number
 * Time: O(n \log n \log k)
 * Status: stress-tested
 */
#pragma once

#include "NumberTheoreticTransform.h"

ll bostanMori(const vl& S, const vl& tr, ll k) {
	int n = sz(tr);
	if (!n) return 0;
	vl Q(n + 1, 1);
	rep(j,0,n) Q[j + 1] = (mod - tr[j]) % mod;
	vl P = conv(S, Q);
	P.resize(n);
	for (; k; k /= 2) {
		vl R = Q;
		for (int i = 1; i <= n; i += 2) R[i] = (mod - R[i]) % mod;
		vl U = conv(P, R), V = conv(Q, R);
		rep(i,0,n) P[i] = U[2 * i + k % 2];
		rep(i,0,n+1) Q[i] = V[2 * i];
	}
	return P[0];
}
