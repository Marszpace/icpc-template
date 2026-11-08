/**
 * Author: Claude
 * Date: 2026-11-08
 * License: CC0
 * Source: bijective numeration
 * Description: Converts a sequence of digits in $[0, a)$ to a sequence
 * of digits in $[0, b)$, with $a, b \ge 2$ (below $2^{31}$), most significant
 * first. It is a bijection between all finite sequences: the empty one
 * maps to the empty one, and the $k$-th sequence in (length, lexicographic)
 * order in base $a$ goes to the $k$-th in base $b$. So
 * \texttt{radixconv(radixconv(x, a, b), b, a) == x} always, with no length
 * or leading zeros to remember, and the result has about
 * $|x| \log_b a$ digits (e.g. to send $n$ numbers below $a$ in messages below $b$).
 * \texttt{radixToPerm(x, a)} is the same with permutations of $0, \ldots, n-1$
 * as the target: a bijection between all digit sequences and all permutations
 * (the size comes out of the data, e.g. 2000 binary digits give 296 elements),
 * (length, lexicographic) order going to (size, lexicographic) order;
 * \texttt{permToRadix(p, a)} is the inverse ($y$ is the result; it also takes $O(|y|^2)$). For a fixed size use \texttt{intToPerm},
 * or \texttt{radixToPerm} on the digits of $r + 0! + 1! + \dots + (n-1)!$ in base $2^{31}-1$ (one digit for $n \le 12$, two up to 20).
 * Time: O(|x| \cdot |y|)
 * Status: stress-tested
 */
#pragma once

// y = y * m + c in bijective mixed radix: digit i (least
// significant first) is in [1, r(i)]
template<class F> void mulAdd(vector<ll>& y, ll m, ll c, F r) {
	rep(i,0,sz(y)) {
		ll t = y[i] * m + c, R = r(i);
		y[i] = (t - 1) % R + 1, c = (t - 1) / R;
	}
	while (c) {
		ll R = r(sz(y));
		y.push_back((c - 1) % R + 1), c = (c - 1) / R;
	}
}
vi radixconv(const vi& x, int a, int b) {
	vector<ll> y; // bijective base b, least significant first
	for (int d : x) mulAdd(y, a, d + 1, [&](int) { return b; });
	vi r;
	for (int i = sz(y); i--;) r.push_back((int)(y[i] - 1));
	return r;
}
vi radixToPerm(const vi& x, int a) {
	vector<ll> y; // bijective factorial base
	for (int d : x)
		mulAdd(y, a, d + 1, [](int i) { return i + 1; });
	int n = sz(y);
	vi s(n), p(n);
	iota(all(s), 0);
	rep(i,0,n) {
		int c = (int)y[n - 1 - i] - 1;
		p[i] = s[c], s.erase(s.begin() + c);
	}
	return p;
}
vi permToRadix(const vi& p, int a) {
	int n = sz(p);
	vector<ll> z; // bijective base a
	rep(k,0,n) {
		int c = 0;
		rep(j,k+1,n) c += p[j] < p[k];
		mulAdd(z, n - k, c + 1, [&](int) { return a; });
	}
	vi x;
	for (int i = sz(z); i--;) x.push_back((int)z[i] - 1);
	return x;
}
