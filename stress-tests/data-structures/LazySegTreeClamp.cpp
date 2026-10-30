#include "../utilities/template.h"

// block from the description of LazySegTreeBlock.h:
// add, set, chmin, chmax, query max;  x -> min(max(x + a, lo), hi)
const ll INF = 1e18;
typedef ll S; struct L { ll a, lo, hi; };
S e() { return -INF; }
L id() { return {0, -INF, INF}; }
S op(S a, S b) { return max(a, b); }
bool ok(S, L) { return 1; }
S app(S s, L x, int) { return min(max(s + x.a, x.lo), x.hi); }
L comp(L x, L y) {
	return {x.a + y.a, min(max(y.lo + x.a, x.lo), x.hi), min(max(y.hi + x.a, x.lo), x.hi)};
}

#include "../../content/data-structures/LazySegTree.h"

int main() {
	srand(2);
	rep(it,0,3000) {
		int n = 1 + rand() % 17;
		vector<ll> b(n);
		rep(i,0,n) b[i] = rand() % 100;
		LazySeg t(b);
		rep(q,0,60) {
			int l = rand() % n, r = l + 1 + rand() % (n - l), ty = rand() % 5;
			ll v = rand() % 100;
			if (ty == 4) {
				ll s = -INF;
				rep(i,l,r) s = max(s, b[i]);
				assert(s == t.query(l, r));
				continue;
			}
			L x = ty == 0 ? L{v - 50, -INF, INF} : ty == 1 ? L{0, v, v}
				: ty == 2 ? L{0, -INF, v} : L{0, v, INF};
			t.upd(l, r, x);
			rep(i,l,r) b[i] = app(b[i], x, 1);
		}
	}
	cout<<"Tests passed!"<<endl;
}
