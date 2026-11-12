/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description: $b^e \bmod mod$. Convention: every header that needs a modulus uses the global \texttt{const ll mod} that your solution declares first.
 * Status: tested
 */
#pragma once

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
