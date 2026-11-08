#include "../utilities/template.h"

#include "../../content/combinatorial/IntPerm.h"

signed main() {
	// exhaustive: the k-th permutation in next_permutation order has rank k
	rep(n,0,9) {
		vi p(n);
		iota(all(p), 0);
		ll k = 0;
		do {
			vi q = p;
			assert(permToInt(q) == k);
			assert(intToPerm(k, n) == p);
			k++;
		} while (next_permutation(all(p)));
	}
	// n <= 20: exact round trips, real permutations, order preserving
	mt19937_64 rng(3);
	rep(n,0,21) {
		ll fact = 1;
		rep(i,1,n+1) fact *= i;
		vi id(n), rev(n);
		iota(all(id), 0);
		rev = id;
		reverse(all(rev));
		assert(permToInt(id) == 0 && permToInt(rev) == fact - 1);
		assert(intToPerm(0, n) == id && intToPerm(fact - 1, n) == rev);
		rep(it,0,400) {
			ll a = (ll)(rng() % (unsigned long long)fact);
			ll b = (ll)(rng() % (unsigned long long)fact);
			vi pa = intToPerm(a, n), pb = intToPerm(b, n);
			vi qa = pa, qb = pb, s = pa;
			sort(all(s));
			assert(s == id);
			assert(permToInt(qa) == a && permToInt(qb) == b);
			assert((a < b) == (pa < pb)); // order preserving
		}
	}
	cout<<"Tests passed!"<<endl;
}
