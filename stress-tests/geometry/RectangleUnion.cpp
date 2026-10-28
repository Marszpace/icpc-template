#include "../utilities/template.h"

#include "../../content/geometry/RectangleUnion.h"

// brute force: mark the cells of the coordinate-compressed grid
ll brute(vector<Rect>& r) {
	vector<ll> xs, ys;
	for (Rect& a : r) xs.push_back(a[0]), xs.push_back(a[2]), ys.push_back(a[1]), ys.push_back(a[3]);
	sort(all(xs)); xs.erase(unique(all(xs)), xs.end());
	sort(all(ys)); ys.erase(unique(all(ys)), ys.end());
	ll area = 0;
	rep(i,0,sz(xs)-1) rep(j,0,sz(ys)-1) {
		bool covered = false;
		for (Rect& a : r)
			covered |= a[0] <= xs[i] && xs[i+1] <= a[2] && a[1] <= ys[j] && ys[j+1] <= a[3];
		if (covered) area += (xs[i+1] - xs[i]) * (ys[j+1] - ys[j]);
	}
	return area;
}

int main() {
	srand(21);
	assert(rectUnion({}) == 0);
	rep(it,0,30000) {
		int n = rand() % 8, range = 1 + rand() % 12;
		ll scale = it % 3 == 0 ? 1 : 1 + rand() % 100000000;
		vector<ll> pos(range + 1);
		rep(i,1,range+1) pos[i] = pos[i-1] + 1 + (scale == 1 ? 0 : rand() % scale);
		vector<Rect> r;
		rep(i,0,n) {
			int x1 = rand() % (range + 1), x2 = rand() % (range + 1);
			int y1 = rand() % (range + 1), y2 = rand() % (range + 1);
			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2); // x1 == x2 or y1 == y2 gives empty rectangles
			r.push_back({pos[x1], pos[y1], pos[x2], pos[y2]});
		}
		assert(rectUnion(r) == brute(r));
	}
	// speed, and a known answer: two overlapping 10^9 squares
	assert(rectUnion({{0, 0, 1000000000, 1000000000}, {500000000, 500000000, 1500000000, 1500000000}})
		== 1000000000000000000LL * 2 - 250000000000000000LL);
	vector<Rect> big;
	rep(i,0,100000) {
		ll x = rand() % 1000000000, y = rand() % 1000000000;
		big.push_back({x, y, x + 1 + rand() % 1000000, y + 1 + rand() % 1000000});
	}
	assert(rectUnion(big) > 0);
	cout << "Tests passed!" << endl;
}
