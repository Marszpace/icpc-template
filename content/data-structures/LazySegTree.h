/**
 * Author: Claude
 * Date: 2026-10-30
 * License: CC0
 * Source: folklore
 * Description: Lazy segment tree; edit only \texttt{LazySegTreeBlock.h}. \texttt{app(s, x, len)} applies tag $x$ to a segment of length \texttt{len};
 * \texttt{comp(x, y)} = $y$ first, then $x$. Ranges $[l, r)$. \texttt{maxRight(l, f)}: largest $r$ with \texttt{f(query(l, r))}, for monotone $f$ with \texttt{f(e())} true.
 * Usage: vector<S> v(n); LazySeg t(v); t.upd(l, r, {5, 0}); t.query(l, r).sum;
 * t.maxRight(l, [\&](S s) { return s.mx < x; }); // first index >= l with value >= x
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

struct LazySeg {
	int n; vector<S> t; vector<L> z;
	LazySeg(vector<S> v) : n(sz(v)), t(4*n), z(4*n, id()) { build(v, 1, 0, n); }
	void build(vector<S>& v, int o, int lo, int hi) {
		if (hi - lo == 1) { t[o] = v[lo]; return; }
		int m = (lo + hi) / 2;
		build(v, 2*o, lo, m); build(v, 2*o+1, m, hi);
		t[o] = op(t[2*o], t[2*o+1]);
	}
	void ap(int o, int len, L x) { t[o] = app(t[o], x, len); z[o] = comp(x, z[o]); }
	void push(int o, int lo, int hi) {
		int m = (lo + hi) / 2;
		ap(2*o, m-lo, z[o]); ap(2*o+1, hi-m, z[o]); z[o] = id();
	}
	void upd(int l, int r, L x, int o=1, int lo=0, int hi=-1) {
		if (hi < 0) hi = n;
		if (r <= lo || hi <= l) return;
		if (l<=lo && hi<=r && ok(t[o], x)) return ap(o, hi-lo, x);
		push(o, lo, hi); int m = (lo + hi) / 2;
		upd(l, r, x, 2*o, lo, m); upd(l, r, x, 2*o+1, m, hi);
		t[o] = op(t[2*o], t[2*o+1]);
	}
	S query(int l, int r, int o = 1, int lo = 0, int hi = -1) {
		if (hi < 0) hi = n;
		if (r <= lo || hi <= l) return e();
		if (l <= lo && hi <= r) return t[o];
		push(o, lo, hi); int m = (lo + hi) / 2;
		return op(query(l,r,2*o,lo,m), query(l,r,2*o+1,m,hi));
	}
	template<class F> int maxRight(int l, F f) {
		S a = e();
		auto go = [&](auto&& go, int o, int lo, int hi) -> int {
			if (hi <= l) return hi;
			if (l<=lo && f(op(a, t[o]))) return a = op(a, t[o]), hi;
			if (hi - lo == 1) return lo;
			push(o, lo, hi); int m = (lo + hi) / 2;
			int r = go(go, 2*o, lo, m);
			return r < m ? r : go(go, 2*o+1, m, hi);
		};
		return go(go, 1, 0, n);
	}
};
