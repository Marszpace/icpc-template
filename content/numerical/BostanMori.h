/**
 * Author: Claude
 * Date: 2026-11-08
 * License: CC0
 * Source: Bostan, Mori: A simple and fast algorithm for computing the N-th term of a linearly recurrent sequence
 * Description: Generates the $k$'th term of an $n$-order linear recurrence
 * $S[i] = \sum_j S[i-j-1]tr[j]$, given $S[0 \ldots \ge n-1]$ and $tr[0 \ldots n-1]$,
 * modulo 998244353 (values in $[0, mod)$). Same interface as \texttt{linearRec}, much faster for large $n$.
 * With $Q = 1 - \sum_j tr[j] x^{j+1}$ and $P = S \cdot Q \bmod x^n$ we want $[x^k] P/Q$;
 * multiplying both by $Q(-x)$ makes the denominator even, so $k$ halves.
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
