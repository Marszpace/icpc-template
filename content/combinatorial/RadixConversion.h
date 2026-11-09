/**
 * Author: Claude
 * Date: 2026-11-08
 * License: CC0
 * Source: bijective numeration
 * Description: Bijective base conversion: digits in $[0, a)$ to digits in $[0, b)$ ($2 \le a, b < 2^{31}$), most significant first.
 * The $k$-th sequence in (length, lexicographic) order in base $a$ maps to the $k$-th in base $b$ (empty to empty),
 * so \texttt{radixconv(radixconv(x, a, b), b, a) == x} with no length or leading zeros to store; the result has about $|x| \log_b a$ digits.
\texttt{radixToPerm(x, a)} does the same onto all permutations of $0, \ldots, n-1$ ($n$ comes from the data: 2000 bits give 296 elements),
 * in (size, lexicographic) order; \texttt{permToRadix(p, a)} is its inverse ($O(|y|^2)$, $y$ the result).
 * Fixed size: \texttt{intToPerm}, or \texttt{radixToPerm} on the base $2^{31}-1$ digits of $r + 0! + \dots + (n-1)!$ (one digit for $n \le 12$, two up to 20).
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
