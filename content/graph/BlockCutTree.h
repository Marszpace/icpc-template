/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: folklore
 * Description: Block-cut tree of an undirected graph (a forest if it is not connected).
 * Nodes $0..n-1$ are the vertices; every biconnected component (a bridge is a
 * component with 2 vertices) gets one more node, adjacent to its vertices.
 * A vertex is a cut vertex iff it has more than one neighbour in the tree.
 * Vertex $w$ separates $u$ and $v$ iff it is a cut vertex on the tree path $u \dots v$.
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
