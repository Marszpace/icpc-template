/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: folklore
 * Description: Lazy segment tree over any monoid with lazy tags.
 * The policy \texttt{M} gives the value type \texttt{S} (with identity \texttt{e()}),
 * the tag type \texttt{L} (identity \texttt{id()}), \texttt{op(a, b)} to merge two values,
 * \texttt{app(s, x, len)} to apply tag $x$ to the value $s$ of a segment of length \texttt{len},
 * and \texttt{comp(x, y)} for the tag "$y$ first, then $x$".
 * The example policy does range add and asks for (minimum, how many times).
 * Usage: LazySeg<MinCnt> t(vector<pii>(n, {0, 1})); t.upd(l, r, 5); t.query(l, r); // [l, r)
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

struct MinCnt {
	typedef pii S; typedef int L;
	static S e() { return {INT_MAX, 0}; }
	static L id() { return 0; }
	static S op(S a, S b) {
		return a.first != b.first ? min(a, b) : S(a.first, a.second + b.second); }
	static S app(S s, L x, int) { return {s.first + x, s.second}; }
	static L comp(L x, L y) { return x + y; }
};
template<class M> struct LazySeg {
	typedef typename M::S S; typedef typename M::L L;
	int n; vector<S> t; vector<L> z;
	LazySeg(vector<S> v) : n(sz(v)), t(4*n), z(4*n, M::id()) { build(v, 1, 0, n); }
	void build(vector<S>& v, int o, int lo, int hi) {
		if (hi - lo == 1) { t[o] = v[lo]; return; }
		int m = (lo + hi) / 2;
		build(v, 2*o, lo, m); build(v, 2*o+1, m, hi);
		t[o] = M::op(t[2*o], t[2*o+1]);
	}
	void ap(int o, int len, L x) { t[o] = M::app(t[o], x, len); z[o] = M::comp(x, z[o]); }
	void push(int o, int lo, int hi) {
		int m = (lo + hi) / 2;
		ap(2*o, m - lo, z[o]); ap(2*o+1, hi - m, z[o]); z[o] = M::id();
	}
	void upd(int l, int r, L x, int o = 1, int lo = 0, int hi = -1) {
		if (hi < 0) hi = n;
		if (r <= lo || hi <= l) return;
		if (l <= lo && hi <= r) return ap(o, hi - lo, x);
		push(o, lo, hi); int m = (lo + hi) / 2;
		upd(l, r, x, 2*o, lo, m); upd(l, r, x, 2*o+1, m, hi);
		t[o] = M::op(t[2*o], t[2*o+1]);
	}
	S query(int l, int r, int o = 1, int lo = 0, int hi = -1) {
		if (hi < 0) hi = n;
		if (r <= lo || hi <= l) return M::e();
		if (l <= lo && hi <= r) return t[o];
		push(o, lo, hi); int m = (lo + hi) / 2;
		return M::op(query(l, r, 2*o, lo, m), query(l, r, 2*o+1, m, hi));
	}
};
