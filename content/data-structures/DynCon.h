/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: folklore (segment tree on time + rollback DSU)
 * Description: Offline dynamic connectivity. \texttt{add(l, r, a, b)}: edge $a$--$b$ during times $[l, r)$. \texttt{run(f)} calls \texttt{f(t)} for $t = 0..T-1$
 * with \texttt{uf} = the graph at time $t$. Toggles: map of start times.
 * Usage: DynCon dc(n, T); dc.add(l, r, a, b);
 *  dc.run([\&](int t){ ... dc.uf.find(x) ... });
 * Time: O((N + E \log T) \log N)
 * Status: stress-tested
 */
#pragma once

#include "UnionFindRollback.h"

struct DynCon { // bad: odd-cycle edges, 0 = bipartite
	int T, bad = 0; RollbackUF uf; vector<vector<pii>> seg;
	DynCon(int n, int T) : T(T), uf(n), seg(4*T + 4) {}
	void add(int l, int r, int a, int b, int o = 1, int lo = 0, int hi = -1) {
		if (hi < 0) hi = T;
		if (r <= lo || hi <= l) return;
		if (l<=lo && hi<=r) { seg[o].push_back({a, b}); return; }
		int m = (lo + hi) / 2;
		add(l, r, a, b, 2*o, lo, m); add(l, r, a, b, 2*o+1, m, hi);
	}
	template<class F> void run(F&& f, int o = 1, int lo = 0, int hi = -1) {
		if (hi < 0) hi = T;
		if (lo >= hi) return;
		int t = uf.time(), b0 = bad;
		for (auto [a, b] : seg[o])
			if (!uf.join(a, b, 1) && uf.par(a) == uf.par(b)) bad++;
		if (hi - lo == 1) f(lo);
		else {
			int m = (lo + hi) / 2;
			run(f, 2*o, lo, m); run(f, 2*o+1, m, hi);
		}
		uf.rollback(t); bad = b0;
	}
};
