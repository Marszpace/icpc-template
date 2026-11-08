#include "../utilities/template.h"
#include "../utilities/genTree.h"

#include "../../content/graph/CompressTree.h"

signed main() {
	srand(42);
	rep(it,0,20000) {
		int n = 2 + rand() % 15;
		vector<vi> C(n);
		vi par(n, -1), dep(n);
		for (auto [a, b] : genRandomTree(n)) C[a].push_back(b), C[b].push_back(a);
		{ // parents and depths, rooted at 0
			vi q = {0}; vector<bool> vis(n); vis[0] = 1;
			rep(i,0,sz(q)) for (int y : C[q[i]]) if (!vis[y]) vis[y] = 1, par[y] = q[i], dep[y] = dep[q[i]] + 1, q.push_back(y);
		}
		auto lcaB = [&](int a, int b) {
			while (a != b) { if (dep[a] < dep[b]) swap(a, b); a = par[a]; }
			return a;
		};
		LCA lca(C);
		int k = 1 + rand() % n;
		vi S(k);
		for (int& x : S) x = rand() % n; // duplicates allowed
		vpi r = compressTree(lca, S);
		set<int> K(all(S));
		for (int a : S) for (int b : S) K.insert(lcaB(a, b));
		set<int> nodes;
		for (auto [p, v] : r) nodes.insert(v);
		assert(sz(nodes) == sz(r) && nodes == K);
		assert(r[0].first == 0);
		rep(i,1,sz(r)) { // parent must be the nearest proper ancestor in K
			int v = r[i].second, p = par[v];
			while (p >= 0 && !K.count(p)) p = par[p];
			assert(p >= 0 && r[r[i].first].second == p);
		}
		int root = r[0].second; // the root is the LCA of everything
		for (int v : K) assert(lcaB(root, v) == root);
	}
	cout << "Tests passed!" << endl;
}
