#include "../utilities/template.h"

#include "../../content/data-structures/DynCon.h"

struct E { int l, r, a, b; };

// components and bipartiteness of the graph on n vertices by BFS
void brute(int n, vector<pii>& edges, vi& comp, bool& bip) {
	vector<vi> g(n);
	for (auto [a, b] : edges) g[a].push_back(b), g[b].push_back(a);
	comp.assign(n, -1);
	vi color(n, -1);
	bip = true;
	int c = 0;
	rep(s,0,n) if (comp[s] < 0) {
		comp[s] = c; color[s] = 0;
		vi q = {s};
		rep(i,0,sz(q)) {
			int v = q[i];
			for (int u : g[v]) {
				if (comp[u] < 0) comp[u] = c, color[u] = color[v] ^ 1, q.push_back(u);
				else if (color[u] == color[v]) bip = false;
			}
		}
		c++;
	}
}

int main() {
	srand(31337);
	rep(it,0,6000) {
		int n = 1 + rand() % 7, T = 1 + rand() % 9, m = rand() % 14;
		vector<E> es;
		rep(i,0,m) {
			int l = rand() % (T + 1), r = rand() % (T + 1);
			if (l > r) swap(l, r);
			// self loops and multi-edges are allowed
			es.push_back({l, r, rand() % n, rand() % n});
		}
		DynCon dc(n, T);
		for (E& e : es) dc.add(e.l, e.r, e.a, e.b);
		int expect = 0;
		dc.run([&](int t) {
			assert(t == expect++);
			vector<pii> edges;
			for (E& e : es) if (e.l <= t && t < e.r) edges.push_back({e.a, e.b});
			vi comp; bool bip;
			brute(n, edges, comp, bip);
			assert((dc.bad == 0) == bip);
			rep(x,0,n) {
				int sizeBrute = 0;
				rep(y,0,n) sizeBrute += comp[y] == comp[x];
				assert(dc.uf.size(x) == sizeBrute);
				rep(y,0,n) assert((dc.uf.find(x) == dc.uf.find(y)) == (comp[x] == comp[y]));
			}
		});
		assert(expect == T);
		// everything is rolled back and reusable state is clean
		assert(dc.bad == 0 && dc.uf.time() == 0);
		rep(x,0,n) assert(dc.uf.find(x) == x);
	}
	// larger run for speed
	{
		const int n = 2000, T = 100000, m = 200000;
		DynCon dc(n, T);
		rep(i,0,m) {
			int l = rand() % T, r = l + 1 + rand() % (T - l);
			dc.add(l, r, rand() % n, rand() % n);
		}
		int cnt = 0;
		dc.run([&](int) { cnt++; });
		assert(cnt == T);
	}
	cout << "Tests passed!" << endl;
}
