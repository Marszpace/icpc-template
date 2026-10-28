#include "../utilities/template.h"

#include "../../content/data-structures/PersistentSegmentTree.h"

int main() {
	srand(99);
	// arbitrary versions with arbitrary (also negative) updates
	rep(it,0,2000) {
		int n = 1 + rand() % 12;
		PST t(n);
		vector<vector<ll>> ver = {vector<ll>(n, 0)};
		vi root = {0};
		rep(step,0,25) {
			int from = rand() % sz(root), p = rand() % n;
			ll x = rand() % 21 - 10;
			vector<ll> a = ver[from];
			a[p] += x;
			ver.push_back(a);
			root.push_back(t.upd(root[from], p, x));
			rep(q,0,6) {
				int v = rand() % sz(root), l = rand() % (n + 1), r = rand() % (n + 1);
				if (l > r) swap(l, r);
				ll s = 0;
				rep(i,l,r) s += ver[v][i];
				assert(t.query(root[v], l, r) == s);
			}
		}
	}
	// range k-th smallest via difference of prefix versions
	rep(it,0,2000) {
		int n = 1 + rand() % 12, m = 1 + rand() % 25;
		PST t(n);
		vi a(m), root(m + 1);
		rep(i,0,m) {
			a[i] = rand() % n;
			root[i + 1] = t.upd(root[i], a[i], 1);
		}
		rep(q,0,30) {
			int l = rand() % m, r = l + 1 + rand() % (m - l);
			vi b(a.begin() + l, a.begin() + r);
			sort(all(b));
			int k = rand() % sz(b);
			assert(t.kth(root[l], root[r], k) == b[k]);
		}
	}
	// performance: 2e5 updates and queries
	{
		const int n = 200000;
		PST t(n);
		vi root(n + 1);
		rep(i,0,n) root[i + 1] = t.upd(root[i], rand() % n, 1);
		ll tot = 0;
		rep(i,0,n) {
			int l = rand() % n, r = l + 1 + rand() % (n - l);
			tot += t.kth(root[l], root[r], rand() % (r - l));
		}
		assert(tot >= 0);
	}
	cout << "Tests passed!" << endl;
}
