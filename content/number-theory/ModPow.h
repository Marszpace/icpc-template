/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description: The modulus shared by every header that needs one: set \texttt{mod} here.
 * \texttt{modpow(b, e)} $= b^e \bmod mod$.
 * Status: tested
 */
#pragma once

#ifdef TEST_MOD /// exclude-line
const int mod = TEST_MOD; /// exclude-line
#else /// exclude-line
const int mod = 998244353; // prime; NTT needs c * 2^k + 1
#endif /// exclude-line

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
