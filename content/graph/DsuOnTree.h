/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: folklore (small-to-large / sack)
 * Description: Answers a question about every subtree using one global
 * structure. \texttt{add(v)} / \texttt{rem(v)} insert / remove vertex $v$
 * (and only $v$) from it; \texttt{query(v)} is called when the structure
 * holds exactly the vertices of the subtree of $v$.
 * Usage: DsuOnTree T(g, root);
 *  T.run([\&](int v){...}, [\&](int v){...}, [\&](int v){...});
 * Time: O(N \log N) calls to add/rem
 * Status: stress-tested
 */
#pragma once

struct DsuOnTree {
	vector<vi> g; vi sub, big, tin, tout, ord; int tim = 0, root;
	DsuOnTree(vector<vi> g, int r = 0) : g(g), sub(sz(g)), big(sz(g), -1),
		tin(sz(g)), tout(sz(g)), ord(sz(g)), root(r) { init(r, -1); }
	void init(int v, int p) {
		sub[v] = 1; ord[tin[v] = tim++] = v;
		for (int u : g[v]) if (u != p) {
			init(u, v); sub[v] += sub[u];
			if (big[v] < 0 || sub[u] > sub[big[v]]) big[v] = u;
		}
		tout[v] = tim;
	}
	template<class A, class R, class Q>
	void go(int v, int p, bool keep, A& add, R& rem, Q& query) {
		for (int u : g[v]) if (u != p && u != big[v])
			go(u, v, 0, add, rem, query);
		if (big[v] >= 0) go(big[v], v, 1, add, rem, query);
		add(v);
		for (int u : g[v]) if (u != p && u != big[v])
			rep(i,tin[u],tout[u]) add(ord[i]);
		query(v);
		if (!keep) rep(i,tin[v],tout[v]) rem(ord[i]);
	}
	template<class A, class R, class Q> void run(A add, R rem, Q query) {
		go(root, -1, 1, add, rem, query);
	}
};
