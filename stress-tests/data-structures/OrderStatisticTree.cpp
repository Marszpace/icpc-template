#include "../utilities/template.h"

#include "../../content/data-structures/OrderStatisticTree.h"

signed main() {
	example();
	srand(48);
	rep(it,0,2000) {
		Tree<int> t;
		vi ref; // sorted, distinct
		rep(op,0,200) {
			int x = rand() % 50 - 25, o = rand() % 5;
			auto pos = lower_bound(all(ref), x) - ref.begin();
			if (o == 0) {
				bool ins = t.insert(x).second;
				assert(ins == (pos == sz(ref) || ref[pos] != x));
				if (ins) ref.insert(ref.begin() + pos, x);
			} else if (o == 1) {
				int er = (int)t.erase(x);
				assert(er == (pos < sz(ref) && ref[pos] == x));
				if (er) ref.erase(ref.begin() + pos);
			} else if (o == 2) {
				assert((int)t.order_of_key(x) == pos);
			} else if (o == 3) {
				int k = rand() % (sz(ref) + 1);
				auto f = t.find_by_order(k);
				if (k == sz(ref)) assert(f == t.end());
				else assert(*f == ref[k]);
			} else {
				auto lb = t.lower_bound(x);
				if (pos == sz(ref)) assert(lb == t.end());
				else assert(*lb == ref[pos]);
			}
			assert(sz(t) == sz(ref));
		}
		// join: all keys of t2 above those of t
		Tree<int> t2; vi r2;
		int mx = ref.empty() ? 0 : ref.back() + 1;
		rep(i,0,rand() % 20) { int x = mx + rand() % 100; if (t2.insert(x).second) r2.push_back(x); }
		t.join(t2);
		sort(all(r2)); ref.insert(ref.end(), all(r2));
		assert(sz(t2) == 0 && sz(t) == sz(ref));
		int i = 0; for (int x : t) assert(x == ref[i++]);
	}
	// map version and pairs for a multiset
	{
		tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update> m;
		m[5] = 1; m[3] = 2;
		assert(m.find_by_order(0)->second == 2 && m.order_of_key(4) == 1);
		Tree<pii> ms; // multiset via (value, unique id)
		rep(i,0,10) ms.insert({i % 3, i});
		assert(ms.order_of_key({1, -1}) == 4 && ms.find_by_order(9)->first == 2);
	}
	cout << "Tests passed!" << endl;
}
