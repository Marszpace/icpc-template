#include "../utilities/template.h"

#include "../../content/data-structures/LazySegTreeBlock.h"
#include "../../content/data-structures/LazySegTree.h"

// default block: range chmin / add, query sum / max / count of max
void testBrute() {
	rep(it,0,5000) {
		int n = 1 + rand() % 17;
		vector<ll> b(n); vector<S> v(n);
		rep(i,0,n) b[i] = rand() % 100, v[i] = {b[i], -INF, 1, b[i]};
		LazySeg t(v);
		rep(q,0,80) {
			int l = rand() % n, r = l + 1 + rand() % (n - l), ty = rand() % 4;
			ll x = rand() % 100;
			if (ty == 0) { t.upd(l, r, {x, 0}); rep(i,l,r) b[i] = min(b[i], x); }
			else if (ty == 1) { x -= 50; t.upd(l, r, {INF, x}); rep(i,l,r) b[i] += x; }
			else {
				ll s = 0, m = -INF, c = 0;
				rep(i,l,r) s += b[i], m = max(m, b[i]);
				rep(i,l,r) c += b[i] == m;
				S g = t.query(l, r);
				assert(g.sum == s && g.mx == m && g.cnt == c);
			}
		}
	}
}

// descent: largest r with f(query(l, r)), for a max predicate (any values) and a sum predicate (values >= 0)
void testMaxRight() {
	rep(it,0,5000) {
		int n = 1 + rand() % 20;
		bool nonneg = it % 2;
		vector<ll> b(n); vector<S> v(n);
		rep(i,0,n) b[i] = rand() % 50, v[i] = {b[i], -INF, 1, b[i]};
		LazySeg t(v);
		rep(q,0,60) {
			int l = rand() % n, r = l + 1 + rand() % (n - l), ty = rand() % 4;
			ll x = rand() % 50;
			if (ty == 0) { t.upd(l, r, {x, 0}); rep(i,l,r) b[i] = min(b[i], x); }
			else if (ty == 1) { if (!nonneg) x -= 25; t.upd(l, r, {INF, x}); rep(i,l,r) b[i] += x; }
			else {
				int L = rand() % (n + 1);
				ll X = rand() % 130 - 10;
				int w1 = L;
				while (w1 < n && b[w1] < X) w1++;
				assert(t.maxRight(L, [&](S s) { return s.mx < X; }) == w1);
				if (nonneg) {
					int w2 = L; ll s = 0;
					while (w2 < n && s + b[w2] <= 3 * X) s += b[w2++];
					assert(t.maxRight(L, [&](S s) { return s.sum <= 3 * X; }) == w2);
				}
			}
		}
	}
}

// chmax instead of chmin: store negated values
void testNegated() {
	rep(it,0,2000) {
		int n = 1 + rand() % 17;
		vector<ll> b(n); vector<S> v(n);
		rep(i,0,n) b[i] = rand() % 100, v[i] = {-b[i], -INF, 1, -b[i]};
		LazySeg t(v);
		rep(q,0,80) {
			int l = rand() % n, r = l + 1 + rand() % (n - l), ty = rand() % 4;
			ll x = rand() % 100;
			if (ty == 0) { t.upd(l, r, {-x, 0}); rep(i,l,r) b[i] = max(b[i], x); }
			else if (ty == 1) { x -= 50; t.upd(l, r, {INF, -x}); rep(i,l,r) b[i] += x; }
			else {
				ll s = 0, m = INF;
				rep(i,l,r) s += b[i], m = min(m, b[i]);
				S g = t.query(l, r);
				assert(-g.sum == s && -g.mx == m);
			}
		}
	}
}

// big input: must stay fast (a wrong second maximum makes chmin O(n))
void testSpeed() {
	int n = 200000;
	vector<S> v(n);
	rep(i,0,n) { ll x = rand() % 1000000000; v[i] = {x, -INF, 1, x}; }
	LazySeg t(v);
	clock_t st = clock();
	ll sink = 0;
	rep(q,0,200000) {
		int l = rand() % n, r = l + 1 + rand() % (n - l), ty = rand() % 3;
		if (ty == 0) t.upd(l, r, {rand() % 1000000000, 0});
		else if (ty == 1) t.upd(l, r, {INF, rand() % 2001 - 1000});
		else sink += t.query(l, r).sum;
	}
	double sec = double(clock() - st) / CLOCKS_PER_SEC;
	assert(sec < 10 && sink != 42);
}

signed main() {
	srand(4);
	testBrute();
	testMaxRight();
	testNegated();
	testSpeed();
	cout<<"Tests passed!"<<endl;
}
