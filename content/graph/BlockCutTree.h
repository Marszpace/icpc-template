/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: folklore
 * Description: Nodes $0..n-1$ are the vertices, then one node per biconnected component (a bridge is one with 2 vertices), adjacent to its vertices;
 * a forest. Cut vertex iff tree degree $> 1$; $w$ separates $u$, $v$ iff it is a cut vertex on their tree path.
 * Time: O(N + M)
 * Status: stress-tested
 */
#pragma once

vector<vi> blockCut(vector<vi>& g) {
	int n = sz(g), T = 0;
	vi num(n), low(n), st;
	vector<vi> t(n);
	auto dfs = [&](auto&& self, int v, int p) -> void {
		num[v] = low[v] = ++T; st.push_back(v);
		for (int u : g[v]) if (u != p) {
			if (num[u]) low[v] = min(low[v], num[u]);
			else {
				self(self, u, v);
				low[v] = min(low[v], low[u]);
				if (low[u] >= num[v]) {
					int b = sz(t); t.emplace_back();
					for (int x = -1; x != u;) {
						x = st.back(); st.pop_back();
						t[b].push_back(x); t[x].push_back(b);
					}
					t[b].push_back(v); t[v].push_back(b);
				}
			}
		}
	};
	rep(v,0,n) if (!num[v]) dfs(dfs, v, -1);
	return t;
}
