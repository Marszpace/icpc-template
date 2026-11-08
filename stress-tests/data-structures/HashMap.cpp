#include "../utilities/template.h"

#include "../../content/data-structures/HashMap.h"

signed main() {
	mt19937_64 rng(47);
	unordered_map<ll, int> ref;
	rep(it,0,2000000) {
		int op = (int)(rng() % 4);
		ll k;
		switch (rng() % 4) {
			case 0: k = (ll)(rng() % 1000); break;
			case 1: k = -(ll)(rng() % 1000); break;
			case 2: k = (ll)(rng() % 1000) << 32; break; // same low bits
			default: k = (ll)rng(); break;
		}
		if (op == 0) { int v = (int)(rng() % 1000); h[k] = v; ref[k] = v; }
		else if (op == 1) { assert((h.find(k) != h.end()) == ref.count(k)); if (ref.count(k)) assert(h.find(k)->second == ref[k]); }
		else if (op == 2) { h.erase(k); ref.erase(k); }
		else { h[k] += 1; ref[k] += 1; }
		if (it % 100000 == 0) {
			assert(sz(h) == sz(ref));
			for (auto [a, b] : h) assert(ref.at(a) == b);
		}
	}
	cout << "Tests passed!" << endl;
}
