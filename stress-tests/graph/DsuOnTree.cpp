#include "../utilities/template.h"

#include "../../content/graph/DsuOnTree.h"

vector<vi> randTree(int n, int mode) {
	vector<vi> g(n);
	rep(i,1,n) {
		int p = mode == 0 ? rand() % i : mode == 1 ? max(0, i - 1 - rand() % 2)
		                                            : rand() % min(i, 3);
		g[p].push_back(i), g[i].push_back(p);
	}
	return g;
}

// colors, id-sum and size of the subtree of v (parent p) by brute force
void subtreeBrute(vector<vi>& g, int v, int p, vi& col, set<int>& colors,
		ll& ids, int& cnt) {
	colors.insert(col[v]); ids += v; cnt++;
	for (int u : g[v]) if (u != p) subtreeBrute(g, u, v, col, colors, ids, cnt);
}

void check(int n, int mode, int K) {
	vector<vi> g = randTree(n, mode);
	// relabel randomly so the tree is not "increasing"
	vi perm(n); iota(all(perm), 0);
	shuffle(all(perm), mt19937(rand()));
	vector<vi> h(n);
	rep(v,0,n) for (int u : g[v]) h[perm[v]].push_back(perm[u]);
	g = h;
	int root = rand() % n;
	vi col(n);
	rep(i,0,n) col[i] = rand() % K;

	vi cnt(K), distinct(n, -1), size(n, -1);
	vector<ll> idsum(n, -1);
	int d = 0, sizeNow = 0;
	ll idNow = 0;
	DsuOnTree T(g, root);
	int queries = 0;
	T.run(
		[&](int v) { if (cnt[col[v]]++ == 0) d++; sizeNow++; idNow += v; },
		[&](int v) { if (--cnt[col[v]] == 0) d--; sizeNow--; idNow -= v; },
		[&](int v) {
			queries++;
			distinct[v] = d, size[v] = sizeNow, idsum[v] = idNow;
		});
	assert(queries == n);
	// brute force
	vi par(n, -2);
	par[root] = -1;
	vi q = {root};
	rep(i,0,n) {
		int v = q[i];
		for (int u : g[v]) if (par[u] == -2) par[u] = v, q.push_back(u);
	}
	// all vertices: size and id-sum by a linear DP over reverse BFS order
	vi sz2(n, 1);
	vector<ll> id2(n);
	rep(v,0,n) id2[v] = v;
	for (int i = n; i--;) {
		int v = q[i];
		if (par[v] >= 0) sz2[par[v]] += sz2[v], id2[par[v]] += id2[v];
		assert(size[v] == sz2[v] && idsum[v] == id2[v]);
	}
	// distinct colors by brute force (all vertices if small, else a sample)
	rep(it,0,n) {
		int v = n <= 100 ? it : rand() % n;
		if (n > 100 && it >= 100) break;
		set<int> colors; ll ids = 0; int c = 0;
		subtreeBrute(g, v, par[v], col, colors, ids, c);
		assert(distinct[v] == sz(colors));
		assert(size[v] == c && idsum[v] == ids);
	}
	// everything must have been removed again, except possibly the last
	// kept heavy path (the structure holds the root's subtree at the end)
	assert(sizeNow == n);
}

int main() {
	srand(77);
	rep(it,0,6000) check(1 + rand() % (it < 4000 ? 10 : 60), rand() % 3, 1 + rand() % 5);
	// deep paths, many light children
	check(50000, 1, 7);
	check(50000, 2, 50);
	check(50000, 0, 1000);
	cout << "Tests passed!" << endl;
}
