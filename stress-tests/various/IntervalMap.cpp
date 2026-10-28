#include "../utilities/template.h"

#include "../../content/various/IntervalMap.h"

// Checks structure invariants and compares against a plain array.
void check(IntervalMap<int>& im, const vi& a, int lo, int hi, bool merged) {
	assert(im.m.begin()->first == lo);
	assert(prev(im.m.end())->first == hi);
	int last = lo - 1, lastVal = -1;
	for (auto it = im.m.begin(); next(it) != im.m.end(); ++it) {
		assert(it->first > last);
		last = it->first;
		if (merged && it != im.m.begin()) assert(it->second != lastVal);
		lastVal = it->second;
		rep(i,it->first,next(it)->first) assert(a[i-lo] == it->second);
	}
	rep(i,lo,hi) assert(im.get(i) == a[i-lo]);
}

int main() {
	srand(12345);
	rep(test,0,3) {
		const int V = test == 0 ? 2 : 4;
		const int N = 1 + rand() % 14, lo = rand() % 5 - 2, hi = lo + N;
		IntervalMap<int> im(lo, hi, 0);
		vi a(N, 0);
		bool merged = true; // adjacent pieces differ unless `each` split one
		rep(it,0,300000) {
			int l = rand() % (N+1), r = rand() % (N+1);
			if (l > r) swap(l, r);
			l += lo; r += lo;
			int op = rand() % 3;
			if (op == 0 && l < r) {
				int v = rand() % V;
				im.assign(l, r, v);
				rep(i,l,r) a[i-lo] = v;
			}
			else if (op == 1 && l < r) {
				int d = 1 + rand() % 3, cnt = 0, len = 0;
				im.each(l, r, [&](int x, int y, int& val) {
					assert(l <= x && x < y && y <= r);
					val = (val + d) % V;
					cnt++, len += y - x;
				});
				assert(len == r - l && cnt >= 1);
				rep(i,l,r) a[i-lo] = (a[i-lo] + d) % V;
				merged = false;
			}
			else if (op == 2) {
				int v = rand() % V;
				im.assign(lo, hi, v);
				a.assign(N, v);
				merged = true;
			}
			check(im, a, lo, hi, merged);
			if (rand() % 50 == 0) merged = false;
		}
	}
	cout<<"Tests passed!"<<endl;
}
