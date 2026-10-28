/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: folklore
 * Description: Persistent segment tree over positions $[0, n)$ holding
 * sums. A version is identified by its root; version 0 is empty.
 * \texttt{upd} adds $x$ at position $p$ and returns the new root.
 * \texttt{query(v, l, r)} sums $[l, r)$ in version $v$.
 * \texttt{kth(a, b, k)} is the $k$-th smallest (0-indexed) position in the
 * multiset \texttt{b} $-$ \texttt{a} (all counts $\ge 0$), e.g. range
 * $k$-th element with $a_i$ added at position rank($a_i$) per version.
 * Usage: PST t(n); r[i+1] = t.upd(r[i], p, 1); t.kth(r[l], r[r], k);
 * Time: O(\log N) per operation, O(\log N) memory per update
 * Status: stress-tested
 */
#pragma once

struct PST {
	struct Nd { int l = 0, r = 0; ll s = 0; };
	vector<Nd> t{Nd()}; int n;
	PST(int n) : n(n) {}
	int upd(int v, int p, ll x, int lo = 0, int hi = -1) {
		if (hi < 0) hi = n;
		int c = sz(t), m = (lo + hi) / 2, ch;
		t.push_back(t[v]); t[c].s += x;
		if (hi - lo > 1) {
			if (p < m) ch = upd(t[v].l, p, x, lo, m), t[c].l = ch;
			else ch = upd(t[v].r, p, x, m, hi), t[c].r = ch;
		}
		return c;
	}
	ll query(int v, int l, int r, int lo = 0, int hi = -1) {
		if (hi < 0) hi = n;
		if (!v || r <= lo || hi <= l) return 0;
		if (l <= lo && hi <= r) return t[v].s;
		int m = (lo + hi) / 2;
		return query(t[v].l, l, r, lo, m) + query(t[v].r, l, r, m, hi);
	}
	int kth(int a, int b, ll k) {
		int lo = 0, hi = n;
		while (hi - lo > 1) {
			int m = (lo + hi) / 2; ll c = t[t[b].l].s - t[t[a].l].s;
			if (k < c) a = t[a].l, b = t[b].l, hi = m;
			else k -= c, a = t[a].r, b = t[b].r, lo = m;
		}
		return lo;
	}
};
