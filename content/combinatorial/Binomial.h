/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Description: Factorial tables modulo a prime for $\binom{n}{k}$ in $O(1)$.
 * Call \texttt{initFact(N)} once; $n < $ \texttt{mod} is required.
 * Time: O(N) precomputation
 * Status: stress-tested
 */
#pragma once

#include "../number-theory/ModPow.h"

vector<ll> fact, ifact;
void initFact(int n) {
	fact.assign(n + 1, 1); ifact.assign(n + 1, 1);
	rep(i,1,n+1) fact[i] = fact[i-1] * i % mod;
	ifact[n] = modpow(fact[n], mod - 2);
	for (int i = n; i--;) ifact[i] = ifact[i+1] * (i + 1) % mod;
}
ll nCr(int n, int k) {
	return k < 0 || k > n ? 0 : fact[n] * ifact[k] % mod * ifact[n-k] % mod;
}
