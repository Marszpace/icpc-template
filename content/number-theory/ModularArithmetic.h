/**
 * Author: NTU team (their template), Claude
 * Date: 2026-11-09
 * License: CC0
 * Source: the team's template
 * Description: Modular integers, \texttt{mint<mod>}: $+ - * /$, the compound
 * forms, \texttt{++}, \texttt{--}, unary minus, comparisons, input and output,
 * \texttt{fpow(a, p)} and \texttt{inverse(a)} (Fermat: needs a prime $mod$).
 * $mod < 2^{30}$ (e.g. $10^9 + 7$ or $998244353$) so that the sum of two values fits an \texttt{int};
 * \texttt{(int)a} is the value in $[0, mod)$.
 * Usage: mi a = 5, b = 7; cout << a / b << ' ' << fpow(a, 100); vmi v(n);
 * Time: O(\log p) for \texttt{fpow}
 * Status: stress-tested
 */
#pragma once

const int M = 1e9 + 7; // prime
template<int mod> struct mint {
	int v;
	explicit operator int() const { return v; }
	mint() : v(0) {}
	mint(ll x) : v((int)(x % mod)) { if (v < 0) v += mod; }
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
		if ((v += o.v) >= mod) v -= mod;
		return *this;
	}
	mint& operator-=(mint o) {
		if ((v -= o.v) < 0) v += mod;
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
using mi = mint<M>;
using vmi = vector<mi>;
