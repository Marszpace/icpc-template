#include "../utilities/template.h"

#include "../../content/data-structures/LazySegTree.h"

// range affine update (x -> a*x + b), range sum: tags do not commute
struct Aff {
	typedef ll S; typedef pair<ll, ll> L;
	static constexpr ll P = 1000000007;
	static S e() { return 0; }
	static L id() { return {1, 0}; }
	static S op(S a, S b) { return (a + b) % P; }
	static S app(S s, L x, int len) { return (x.first * s + x.second * len) % P; }
	static L comp(L x, L y) { return {x.first * y.first % P, (x.first * y.second + x.second) % P}; }
};

int main() {
	srand(11);
	rep(it,0,3000) {
		int n = 1 + rand() % 17;
		// min and count of min with range add
		vi a(n);
		vector<pii> init(n);
		rep(i,0,n) a[i] = rand() % 4, init[i] = {a[i], 1};
		LazySeg<MinCnt> t(init);
		// affine tags with range sum
		vector<ll> b(n);
		vector<ll> binit(n);
		rep(i,0,n) b[i] = binit[i] = rand() % 100;
		LazySeg<Aff> u(binit);
		rep(q,0,60) {
			int l = rand() % (n + 1), r = rand() % (n + 1);
			if (l > r) swap(l, r);
			if (rand() % 2) {
				int x = rand() % 7 - 3;
				t.upd(l, r, x);
				rep(i,l,r) a[i] += x;
				ll mul = rand() % 5, add = rand() % 100;
				u.upd(l, r, {mul, add});
				rep(i,l,r) b[i] = (mul * b[i] + add) % Aff::P;
			} else {
				pii want = {INT_MAX, 0};
				ll sum = 0;
				rep(i,l,r) {
					if (a[i] < want.first) want = {a[i], 1};
					else if (a[i] == want.first) want.second++;
					sum = (sum + b[i]) % Aff::P;
				}
				assert(t.query(l, r) == want);
				assert(u.query(l, r) == sum);
			}
		}
	}
	// speed
	{
		const int n = 200000;
		LazySeg<MinCnt> t(vector<pii>(n, {0, 1}));
		rep(i,0,n) {
			int l = rand() % n, r = l + 1 + rand() % (n - l);
			t.upd(l, r, rand() % 5 - 2);
			t.query(rand() % n, n);
		}
	}
	cout << "Tests passed!" << endl;
}
