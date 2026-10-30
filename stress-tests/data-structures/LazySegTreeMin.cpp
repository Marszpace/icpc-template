#include "../utilities/template.h"

// default block extended with a min query, as in the description of LazySegTreeBlock.h
const ll INF = 1e18;
struct S { ll mx = 0, se = -INF, cnt = 1, sum = 0, mn = 0; };
struct L { ll c, a; };
S e() { return {-INF, -INF, 0, 0, INF}; }
L id() { return {INF, 0}; }
S op(S a, S b) {
	ll mn = min(a.mn, b.mn);
	if (a.mx < b.mx) swap(a, b);
	if (a.mx == b.mx) return {a.mx, max(a.se, b.se), a.cnt + b.cnt, a.sum + b.sum, mn};
	return {a.mx, max(a.se, b.mx), a.cnt, a.sum + b.sum, mn};
}
bool ok(S s, L x) { return x.c > s.se; }
S app(S s, L x, int len) {
	if (x.c < s.mx) s.sum -= (s.mx - x.c) * s.cnt, s.mx = x.c;
	s.sum += x.a * len; s.mx += x.a;
	if (s.se > -INF / 2) s.se += x.a;
	s.mn = min(s.mn, x.c) + x.a;
	return s;
}
L comp(L x, L y) { return {min(y.c, x.c - y.a), x.a + y.a}; }

#include "../../content/data-structures/LazySegTree.h"

int main() {
	srand(3);
	rep(it,0,3000) {
		int n = 1 + rand() % 17;
		vector<ll> b(n); vector<S> v(n);
		rep(i,0,n) b[i] = rand() % 100, v[i] = {b[i], -INF, 1, b[i], b[i]};
		LazySeg t(v);
		rep(q,0,80) {
			int l = rand() % n, r = l + 1 + rand() % (n - l), ty = rand() % 3;
			ll x = rand() % 100;
			if (ty == 0) { t.upd(l, r, {x, 0}); rep(i,l,r) b[i] = min(b[i], x); }
			else if (ty == 1) { x -= 50; t.upd(l, r, {INF, x}); rep(i,l,r) b[i] += x; }
			else {
				ll m = INF, M = -INF;
				rep(i,l,r) m = min(m, b[i]), M = max(M, b[i]);
				S g = t.query(l, r);
				assert(g.mn == m && g.mx == M);
			}
		}
	}
	cout<<"Tests passed!"<<endl;
}
