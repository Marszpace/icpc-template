#include "../utilities/template.h"

#include "../../content/graph/BlockCutTree.h"

// component labels of g ignoring vertex `skip` (-1 = none), by BFS
vi comps(vector<vi>& g, int skip) {
	int n = sz(g), c = 0;
	vi lab(n, -1);
	rep(s,0,n) if (s != skip && lab[s] < 0) {
		lab[s] = c; vi q = {s};
		rep(i,0,sz(q)) for (int u : g[q[i]]) if (u != skip && lab[u] < 0) lab[u] = c, q.push_back(u);
		c++;
	}
	return lab;
}

int main() {
	srand(40);
	rep(it,0,20000) {
		int n = 1 + rand() % 9, m = rand() % 14;
		vector<vi> g(n);
		rep(i,0,m) { // parallel edges and self loops allowed
			int a = rand() % n, b = rand() % n;
			g[a].push_back(b);
			if (a != b) g[b].push_back(a);
		}
		vector<vi> t = blockCut(g);
		int N = sz(t);
		assert(N >= n);
		// the result must be a forest on the vertex components plus blocks
		int edges = 0;
		rep(v,0,N) { edges += sz(t[v]); for (int u : t[v]) assert((v < n) != (u < n)); }
		edges /= 2;
		vi lab = comps(g, -1);
		int ncomp = *max_element(all(lab)) + 1;
		assert(edges == N - ncomp);
		vi tl = comps(t, -1);
		rep(u,0,n) rep(v,0,n) assert((lab[u] == lab[v]) == (tl[u] == tl[v]));
		// cut vertices: degree > 1 in the tree iff removing it splits its component
		rep(w,0,n) {
			vi l2 = comps(g, w);
			int comps2 = 0;
			rep(v,0,n) if (v != w) comps2 = max(comps2, l2[v] + 1);
			bool cut = comps2 > ncomp - (sz(g[w]) == 0 || all_of(all(g[w]), [&](int x) { return x == w; }));
			assert(cut == (sz(t[w]) > 1));
		}
		// separation: w separates u and v iff w is a cut vertex on their tree path
		rep(u,0,n) {
			vi par(N, -2); par[u] = -1; vi q = {u};
			rep(i,0,sz(q)) for (int x : t[q[i]]) if (par[x] == -2) par[x] = q[i], q.push_back(x);
			rep(v,0,n) if (v != u && par[v] != -2) {
				vector<char> onPath(N);
				for (int x = par[v]; x != -1 && x != u; x = par[x]) onPath[x] = 1;
				rep(w,0,n) if (w != u && w != v) {
					vi l2 = comps(g, w);
					bool separated = l2[u] != l2[v];
					assert(separated == (onPath[w] && sz(t[w]) > 1));
				}
			}
		}
	}
	// deep path (recursion)
	{
		const int n = 100000;
		vector<vi> g(n);
		rep(i,1,n) g[i-1].push_back(i), g[i].push_back(i-1);
		vector<vi> t = blockCut(g);
		assert(sz(t) == 2 * n - 1);
	}
	cout << "Tests passed!" << endl;
}
