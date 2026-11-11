/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: folklore
 * Description: \texttt{run(f)} calls \texttt{f(c)} per centroid $c$; a DFS from $c$ skipping \texttt{dead} then visits exactly its component.
 * Usage: Centroid C(g); C.run([\&](int c){ ... });
 * Time: O(N \log N) plus the work done in \texttt{f}
 * Status: stress-tested
 */
#pragma once

struct Centroid { // cpar: centroid tree, root -1
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
