/**
 * Author: Simon Lindholm, Claude
 * Date: 2018-07-06
 * License: CC0
 * Description: Exact for $n \le 20$. Unknown size: \texttt{radixToPerm}.
 * Usage: intToPerm(0, 3) // {0, 1, 2}, intToPerm(5, 3) // {2, 1, 0}
 * Time: O(n) and O(n^2)
 * Status: stress-tested
 */
#pragma once

ll permToInt(vi& v) { // rank in lexicographic order
	ll use = 0, r = 0;
	int n = sz(v);
	rep(i,0,n) {
		int x = v[i];
		r = r * (n - i) + x
			- __builtin_popcountll(use & ((1LL << x) - 1));
		use |= 1LL << x;
	}
	return r;
}
vi intToPerm(ll r, int n) { // inverse: the r'th permutation
	vi c(n), s(n), v(n);
	iota(all(s), 0);
	for (int i = n; i--; r /= n - i) c[i] = (int)(r % (n - i));
	rep(i,0,n) v[i] = s[c[i]], s.erase(s.begin() + c[i]);
	return v;
}
