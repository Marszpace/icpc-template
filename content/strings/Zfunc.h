/**
 * Author: chilli
 * License: CC0
 * Description: $z[i]$ = lcp of $s[i..]$ and $s$, $z[0] = 0$.
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

vi Z(const string& S) { // abacaba -> 0010301
	vi z(sz(S));
	int l = -1, r = -1;
	rep(i,1,sz(S)) {
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}
