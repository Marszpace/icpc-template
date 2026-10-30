#include "../utilities/template.h"

// block from the description of LazySegTreeBlock.h: set / add / mul, query sum
const ll P = 1000000007;
typedef ll S; struct L { ll a, b; };
S e() { return 0; }
L id() { return {1, 0}; }
S op(S a, S b) { return (a + b) % P; }
bool ok(S, L) { return 1; }
S app(S s, L x, int len) { return (x.a * s + x.b * len) % P; }
L comp(L x, L y) { return {x.a * y.a % P, (x.a * y.b + x.b) % P}; }

#include "../../content/data-structures/LazySegTree.h"

int main() {
	srand(1);
	rep(it,0,3000) {
		int n = 1 + rand() % 17;
		vector<ll> b(n);
		rep(i,0,n) b[i] = rand() % 100;
		LazySeg t(b);
		rep(q,0,60) {
			int l = rand() % n, r = l + 1 + rand() % (n - l), ty = rand() % 4;
			ll v = rand() % 50;
			if (ty == 3) {
				ll s = 0;
				rep(i,l,r) s = (s + b[i]) % P;
				assert(s == t.query(l, r));
				continue;
			}
			L x = ty == 0 ? L{1, v} : ty == 1 ? L{0, v} : L{v, 0};
			t.upd(l, r, x);
			rep(i,l,r) b[i] = (x.a * b[i] + x.b) % P;
		}
	}
	cout<<"Tests passed!"<<endl;
}
