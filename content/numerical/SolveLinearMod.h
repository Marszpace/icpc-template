/**
 * Author: Per Austrin, Simon Lindholm (SolveLinear); modular version by Claude
 * Date: 2026-10-29
 * License: CC0
 * Description: Solves $A x = b$ over the field $\mathbb Z_{mod}$ ($mod$ prime).
 * Returns the rank, or $-1$ if there is no solution. Free variables are set to 0.
 * Data in $A$ and $b$ is lost. Entries must be in $[0, mod)$.
 * Time: O(n m \min(n, m))
 * Status: stress-tested
 */
#pragma once

#include "../number-theory/ModPow.h"

typedef vector<ll> vl;
int solveLinearMod(vector<vl>& A, vl& b, vl& x) {
	int n = sz(A), m = sz(x), rank = 0;
	vi col(m); iota(all(col), 0);
	rep(i,0,n) {
		int br = -1, bc = 0;
		rep(r,i,n) rep(c,i,m) if (br < 0 && A[r][c]) br = r, bc = c;
		if (br < 0) {
			rep(j,i,n) if (b[j]) return -1;
			break;
		}
		swap(A[i], A[br]); swap(b[i], b[br]); swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		ll iv = modpow(A[i][i], mod - 2);
		rep(j,i+1,n) {
			ll fac = A[j][i] * iv % mod;
			b[j] = (b[j] - fac * b[i] % mod + mod) % mod;
			rep(k,i+1,m) A[j][k] = (A[j][k] - fac * A[i][k] % mod + mod) % mod;
		}
		rank++;
	}
	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] = b[i] * modpow(A[i][i], mod - 2) % mod;
		x[col[i]] = b[i];
		rep(j,0,i) b[j] = (b[j] - A[j][i] * b[i] % mod + mod) % mod;
	}
	return rank; // (multiple solutions if rank < m)
}
