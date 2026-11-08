#include "../utilities/template.h"

#include "../../content/data-structures/Treap.h"

// random range add / reverse / sum, insert and move against a plain vector
void testAgainstVector(int n0, int ops, int iters) {
	rep(it,0,iters) {
		int n = rand() % (n0 + 1);
		vector<Node> nodes;
		nodes.reserve(n + ops);
		vector<ll> b;
		Node* t = 0;
		auto push = [&](ll v, int pos) {
			nodes.emplace_back(v);
			t = ins(t, &nodes.back(), pos);
			b.insert(b.begin() + pos, v);
		};
		rep(i,0,n) push(rand() % 100 - 30, i);
		rep(q,0,ops) {
			int m = sz(b), l = rand() % (m + 1), r = l + rand() % (m - l + 1), ty = rand() % 6;
			if (ty == 0) {
				ll x = rand() % 40 - 20;
				go(t, l, r, [&](Node* v) { v->app(x, 0); });
				rep(i,l,r) b[i] += x;
			} else if (ty == 1) {
				go(t, l, r, [&](Node* v) { v->app(0, 1); });
				reverse(b.begin() + l, b.begin() + r);
			} else if (ty == 2) {
				ll s = 0, w = 0;
				go(t, l, r, [&](Node* v) { s = v->sum; });
				rep(i,l,r) w += b[i];
				assert(s == w);
			} else if (ty == 3) {
				ll x = rand() % 40 - 20;
				go(t, l, r, [&](Node* v) { v->app(x, 1); }); // both at once
				rep(i,l,r) b[i] += x;
				reverse(b.begin() + l, b.begin() + r);
			} else if (ty == 4) {
				push(rand() % 100, rand() % (m + 1));
			} else if (m) {
				int i = rand() % m, j = rand() % m, k = rand() % (m + 1);
				if (i > j) swap(i, j);
				j++;
				if (i < k && k < j) continue;
				move(t, i, j, k);
				vector<ll> c(b.begin() + i, b.begin() + j);
				b.erase(b.begin() + i, b.begin() + j);
				b.insert(b.begin() + (k >= j ? k - (j - i) : k), all(c));
			}
			assert(cnt(t) == sz(b));
			// each() pushes every tag down, so look at the contents only now and then:
			// tags have to stay pending across several operations
			if (rand() % 8 == 0 || q == ops - 1) {
				vector<ll> got;
				each(t, [&](ll v) { got.push_back(v); });
				assert(got == b);
			}
		}
	}
}

// a big treap stays fast (depth is logarithmic, no quadratic pushes)
void testSpeed() {
	int n = 200000;
	vector<Node> nodes;
	nodes.reserve(n);
	Node* t = 0;
	rep(i,0,n) {
		nodes.emplace_back(i);
		t = merge(t, &nodes.back());
	}
	clock_t st = clock();
	ll sink = 0;
	rep(q,0,200000) {
		int l = rand() % n, r = l + rand() % (n - l) + 1;
		int ty = rand() % 3;
		if (ty == 0) go(t, l, r, [&](Node* v) { v->app(1, 0); });
		else if (ty == 1) go(t, l, r, [&](Node* v) { v->app(0, 1); });
		else go(t, l, r, [&](Node* v) { sink += v->sum; });
	}
	assert((double)(clock() - st) / CLOCKS_PER_SEC < 10 && sink != 42);
}

signed main() {
	srand(7);
	testAgainstVector(25, 60, 3000);
	testAgainstVector(300, 200, 100);
	testSpeed();
	cout<<"Tests passed!"<<endl;
}
