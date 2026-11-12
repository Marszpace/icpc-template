/**
 * Author: NTU team (their template), Claude
 * Date: 2026-11-09
 * License: CC0
 * Source: the team's template
 * Description: Integers mod the global \texttt{const ll mod} (prime $< 2^{30}$): arithmetic, comparisons, I/O, \texttt{fpow(a, p)}, \texttt{inverse(a)}; \texttt{(int)a} is the value.
 * Usage: mi a = 5, b = 7; cout << a / b << ' ' << fpow(a, 100); vmi v(n);
 * Time: O(\log p) for \texttt{fpow}
 * Status: stress-tested
 */
#pragma once

struct mint { // mod: prime < 2^30
	int v;
	explicit operator int() const { return v; }
	mint() : v(0) {}
	mint(ll x) : v((int)(x % mod)) { if (v < 0) v += (int)mod; }
	bool operator==(mint o) const { return v == o.v; }
	friend bool operator!=(mint a, mint b) { return !(a == b); }
	friend bool operator<(mint a, mint b) { return a.v < b.v; }
	friend istream& operator>>(istream& is, mint& a) {
		ll x; is >> x; a = mint(x); return is;
	}
	friend ostream& operator<<(ostream& os, mint a) {
		return os << (int)a;
	}
	mint& operator+=(mint o) {
		if ((v += o.v) >= mod) v -= (int)mod;
		return *this;
	}
	mint& operator-=(mint o) {
		if ((v -= o.v) < 0) v += (int)mod;
		return *this;
	}
	mint& operator*=(mint o) {
		v = (int)((ll)v * o.v % mod);
		return *this;
	}
	mint& operator/=(mint o) { return *this *= inverse(o); }
	friend mint fpow(mint a, ll p) { // p >= 0
		mint r = 1;
		for (; p; p /= 2, a *= a) if (p & 1) r *= a;
		return r;
	}
	friend mint inverse(mint a) {
		assert(a.v); return fpow(a, mod - 2);
	}
	mint operator-() const { return mint(-v); }
	mint& operator++() { return *this += 1; }
	mint& operator--() { return *this -= 1; }
	mint operator++(signed) {
		mint r = *this; ++*this; return r;
	}
	mint operator--(signed) {
		mint r = *this; --*this; return r;
	}
	friend mint operator+(mint a, mint b) { return a += b; }
	friend mint operator-(mint a, mint b) { return a -= b; }
	friend mint operator*(mint a, mint b) { return a *= b; }
	friend mint operator/(mint a, mint b) { return a /= b; }
};
using mi = mint;
using vmi = vector<mi>;
