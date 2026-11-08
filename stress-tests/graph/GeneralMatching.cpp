#include "../utilities/template.h"

#include "../../content/graph/GeneralMatching.h"

// maximum matching size by DP over vertex subsets
int brute(int n, vector<pii>& ed) {
	vector<vi> adj(n, vi(n));
	for (auto [a, b] : ed) adj[a][b] = adj[b][a] = 1;
	vi dp(1 << n);
	rep(mask,1,1 << n) {
		int v = __builtin_ctz((unsigned)mask), rest = mask & ~(1 << v);
		dp[mask] = dp[rest];
		rep(u,0,n) if ((rest >> u & 1) && adj[v][u])
			dp[mask] = max(dp[mask], 1 + dp[rest & ~(1 << u)]);
	}
	return dp[(1 << n) - 1];
}

void check(int n, vector<pii>& ed, int want) {
	set<pii> E;
	for (auto [a, b] : ed) E.insert(minmax(a, b));
	auto r = generalMatching(n, ed);
	vi used(n);
	for (auto [a, b] : r) {
		assert(0 <= a && a < n && 0 <= b && b < n);
		assert(E.count(minmax(a, b)));
		assert(!used[a]++ && !used[b]++);
	}
	assert(sz(r) == want);
}

signed main() {
	srand(43);
	rep(it,0,20000) {
		int n = 1 + rand() % 14, m = rand() % (n * n / 2 + 1);
		vector<pii> ed;
		set<pii> seen;
		rep(i,0,m) {
			int a = rand() % n, b = rand() % n;
			if (a == b || !seen.insert(minmax(a, b)).second) continue;
			ed.push_back({a, b});
		}
		check(n, ed, brute(n, ed));
	}
	// complete graphs, empty graphs, planted perfect matchings in bigger graphs
	rep(n,1,30) {
		vector<pii> ed, none;
		rep(i,0,n) rep(j,0,i) ed.push_back({i, j});
		check(n, ed, n / 2);
		check(n, none, 0);
	}
	rep(it,0,20) {
		int n = 2 * (1 + rand() % 60);
		vi p(n); iota(all(p), 0); shuffle(all(p), mt19937(it));
		vector<pii> ed;
		set<pii> seen;
		for (int i = 0; i < n; i += 2) ed.push_back({p[i], p[i+1]}), seen.insert(minmax(p[i], p[i+1]));
		rep(i,0,n) {
			int a = rand() % n, b = rand() % n;
			if (a != b && seen.insert(minmax(a, b)).second) ed.push_back({a, b});
		}
		shuffle(all(ed), mt19937(it + 99));
		check(n, ed, n / 2);
	}
	cout << "Tests passed!" << endl;
}
