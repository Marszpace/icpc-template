/**
 * Author: Claude
 * Date: 2026-11-15
 * License: CC0
 * Source: Lengauer, Tarjan (1979)
 * Description: Dominator tree of a digraph from root $r$: \texttt{idom[v]} is the last vertex
 * other than $v$ that every path $r \to v$ passes; $-1$ for $r$ and for vertices not reachable from $r$.
 * Time: O(M \log N)
 * Status: stress-tested
 */
#pragma once

vi dominators(vector<vi>& g, int r) {
	int n = sz(g), t = 0;
	vi num(n, -1), ord, par(n), sdom(n), dom(n), lab(n), dsu(n);
	vector<vi> rg(n), bk(n);
	auto dfs = [&](auto& f, int v) -> void {
		num[v] = t++; ord.push_back(v);
		for (int u : g[v])
			if (num[u] < 0) f(f, u), par[num[u]] = num[v];
	};
	dfs(dfs, r);
	rep(v,0,n) if (num[v] >= 0)
		for (int u : g[v]) rg[num[u]].push_back(num[v]);
	rep(i,0,t) sdom[i] = lab[i] = dsu[i] = i;
	// find: min-sdom vertex on the dsu path; compresses it
	auto find = [&](auto& f, int v, int x) -> int {
		if (dsu[v] == v) return x ? -1 : v;
		int p = f(f, dsu[v], x + 1);
		if (p < 0) return v;
		if (sdom[lab[dsu[v]]] < sdom[lab[v]]) lab[v] = lab[dsu[v]];
		dsu[v] = p;
		return x ? p : lab[v];
	};
	for (int i = t - 1; i >= 0; i--) {
		for (int j : rg[i])
			sdom[i] = min(sdom[i], sdom[find(find, j, 0)]);
		if (i) bk[sdom[i]].push_back(i);
		for (int w : bk[i]) {
			int v = find(find, w, 0);
			dom[w] = sdom[v] == sdom[w] ? sdom[w] : v;
		}
		if (i) dsu[i] = par[i];
	}
	vi res(n, -1);
	rep(i,1,t) {
		if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
		res[ord[i]] = ord[dom[i]];
	}
	return res;
}
