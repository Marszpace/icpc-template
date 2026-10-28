/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: folklore
 * Description: Centroid decomposition. \texttt{run(f)} calls \texttt{f(c)}
 * once per centroid $c$; at that moment a DFS from $c$ that skips
 * \texttt{dead} vertices visits exactly the component of $c$
 * (centroids of earlier calls are \texttt{dead}). \texttt{cpar} is the
 * centroid tree (root has $-1$). Each vertex is in $O(\log N)$ components.
 * Usage: Centroid C(g); C.run([\&](int c){ ... });
 * Time: O(N \log N) plus the work done in \texttt{f}
 * Status: stress-tested
 */
#pragma once

struct Centroid {
	vector<vi> g; vi sub, cpar; vector<char> dead;
	Centroid(vector<vi> g) : g(g), sub(sz(g)), cpar(sz(g), -1), dead(sz(g)) {}
	int calc(int v, int p) {
		sub[v] = 1;
		for (int u : g[v]) if (u != p && !dead[u]) sub[v] += calc(u, v);
		return sub[v];
	}
	int find(int v, int p, int n) {
		for (int u : g[v]) if (u != p && !dead[u] && sub[u]*2 > n)
			return find(u, v, n);
		return v;
	}
	template<class F> void run(F&& f, int v = 0, int p = -1) {
		int c = find(v, -1, calc(v, -1));
		cpar[c] = p; f(c); dead[c] = 1;
		for (int u : g[c]) if (!dead[u]) run(f, u, c);
	}
};
