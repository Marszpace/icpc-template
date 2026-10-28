/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: https://cp-algorithms.com/geometry/convex_hull_trick.html
 * Description: Li Chao tree: minimum of lines $kx + m$ at integer points $x \in [0, n)$.
 * \texttt{add} inserts a line everywhere, \texttt{addSeg} only for $x \in [a, b)$,
 * in any order. For maximum, negate $k$, $m$ and the answer.
 * \texttt{query} returns \texttt{INF} if no line covers $x$.
 * Time: O(\log N) per operation ($O(\log^2 N)$ for \texttt{addSeg})
 * Status: stress-tested
 */
#pragma once

struct LiChao {
	static const ll INF = 4e18;
	struct Ln { ll k = 0, m = INF; ll at(ll x) { return k * x + m; } };
	int n; vector<Ln> t;
	LiChao(int n) : n(n), t(4*n) {}
	void ins(Ln ln, int o, int lo, int hi) {
		int mid = (lo + hi) / 2;
		bool l = ln.at(lo) < t[o].at(lo), m = ln.at(mid) < t[o].at(mid);
		if (m) swap(t[o], ln);
		if (hi - lo == 1) return;
		if (l != m) ins(ln, 2*o, lo, mid); else ins(ln, 2*o+1, mid, hi);
	}
	void addSeg(ll k, ll m, int a, int b, int o = 1, int lo = 0, int hi = -1) {
		if (hi < 0) hi = n;
		if (b <= lo || hi <= a) return;
		if (a <= lo && hi <= b) return ins({k, m}, o, lo, hi);
		int mid = (lo + hi) / 2;
		addSeg(k, m, a, b, 2*o, lo, mid); addSeg(k, m, a, b, 2*o+1, mid, hi);
	}
	void add(ll k, ll m) { addSeg(k, m, 0, n); }
	ll query(int x) {
		ll r = INF;
		for (int o = 1, lo = 0, hi = n; ; ) {
			r = min(r, t[o].at(x));
			if (hi - lo == 1) return r;
			int mid = (lo + hi) / 2;
			if (x < mid) o = 2*o, hi = mid; else o = 2*o+1, lo = mid;
		}
	}
};
