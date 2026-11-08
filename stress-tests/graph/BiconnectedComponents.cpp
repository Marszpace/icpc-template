#include "../utilities/template.h"

#include "../../content/graph/BiconnectedComponents.h"

struct UF {
	vi p; UF(int n) : p(n) { iota(all(p), 0); }
	int f(int x) { return p[x] == x ? x : p[x] = f(p[x]); }
	void u(int a, int b) { p[f(a)] = f(b); }
};

signed main() {
	srand(41);
	rep(it,0,30000) {
		int n = 1 + rand() % 9, m = rand() % 14;
		vector<pii> E;
		rep(i,0,m) { // parallel edges allowed, no self loops
			int a = rand() % n, b = rand() % n;
			if (a != b) E.push_back({a, b});
		}
		m = sz(E);
		ed.assign(n, {});
		int eid = 0;
		for (auto [a, b] : E) {
			ed[a].emplace_back(b, eid);
			ed[b].emplace_back(a, eid++);
		}
		vector<vi> got;
		bicomps([&](const vi& edgelist) { got.push_back(edgelist); });
		for (vi& c : got) sort(all(c));
		sort(all(got));
		// brute: edges (v,a), (v,b) are in one block iff a == b or a, b are connected without v
		UF uf(m);
		rep(v,0,n) {
			// connectivity of the graph without v
			UF g(n);
			for (auto [a, b] : E) if (a != v && b != v) g.u(a, b);
			rep(e,0,m) rep(f,e+1,m) {
				auto [a1, b1] = E[e]; auto [a2, b2] = E[f];
				if (a1 != v && b1 != v) continue;
				if (a2 != v && b2 != v) continue;
				int x = a1 ^ b1 ^ v, y = a2 ^ b2 ^ v;
				if (x == y || g.f(x) == g.f(y)) uf.u(e, f);
			}
		}
		map<int, vi> cls;
		rep(e,0,m) cls[uf.f(e)].push_back(e);
		vector<vi> want;
		for (auto& [r, c] : cls) if (sz(c) > 1) want.push_back(c); // size 1 = bridge
		sort(all(want));
		assert(got == want);
	}
	cout << "Tests passed!" << endl;
}
