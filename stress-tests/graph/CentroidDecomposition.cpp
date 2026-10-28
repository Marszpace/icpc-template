#include "../utilities/template.h"

#include "../../content/graph/CentroidDecomposition.h"

// mode 0: random recursive tree, 1: path-like, 2: star-like
vector<vi> randTree(int n, int mode) {
	vector<vi> g(n);
	rep(i,1,n) {
		int p = mode == 0 ? rand() % i : mode == 1 ? max(0, i - 1 - rand() % 2)
		                                            : rand() % min(i, 3);
		g[p].push_back(i), g[i].push_back(p);
	}
	return g;
}

int lg2(int n) { int l = 0; while ((1 << l) <= n) l++; return l; }

void check(vector<vi>& g) {
	int n = sz(g);
	Centroid C(g);
	vector<char> removed(n);
	vi cnt(n), order(n, -1);
	int calls = 0;
	C.run([&](int c) {
		assert(!removed[c]);
		rep(v,0,n) assert(C.dead[v] == removed[v]);
		// component of c among non-removed vertices
		vi comp, st = {c};
		vector<char> vis(n);
		vis[c] = 1;
		while (!st.empty()) {
			int v = st.back(); st.pop_back();
			comp.push_back(v);
			for (int u : g[v]) if (!removed[u] && !vis[u])
				vis[u] = 1, st.push_back(u);
		}
		int m = sz(comp);
		// c is a centroid: every piece of comp - {c} has size <= m/2
		for (int u : g[c]) if (!removed[u]) {
			int s = 0;
			vector<char> seen(n);
			seen[c] = seen[u] = 1;
			vi q = {u};
			while (!q.empty()) {
				int v = q.back(); q.pop_back(); s++;
				for (int w : g[v]) if (!removed[w] && !seen[w])
					seen[w] = 1, q.push_back(w);
			}
			assert(2 * s <= m);
		}
		for (int v : comp) cnt[v]++;
		order[c] = calls++;
		removed[c] = 1;
	});
	assert(calls == n);
	int roots = 0;
	rep(v,0,n) {
		assert(cnt[v] <= lg2(n));
		if (C.cpar[v] < 0) roots++;
		else assert(order[C.cpar[v]] < order[v]);
		int d = 0;
		for (int x = v; x >= 0; x = C.cpar[x]) d++;
		assert(d <= lg2(n));
	}
	assert(roots == 1);
}

int main() {
	srand(2024);
	rep(it,0,4000) {
		int n = 1 + rand() % (it < 3000 ? 12 : 70);
		auto g = randTree(n, rand() % 3);
		check(g);
	}
	// deep trees (recursion depth)
	rep(mode,0,3) {
		const int n = 50000;
		auto g = randTree(n, mode);
		Centroid C(g);
		int calls = 0;
		C.run([&](int) { calls++; });
		assert(calls == n);
		int d = 0;
		rep(v,0,n) {
			int x = 0;
			for (int y = v; y >= 0; y = C.cpar[y]) x++;
			d = max(d, x);
		}
		assert(d <= lg2(n));
	}
	cout << "Tests passed!" << endl;
}
