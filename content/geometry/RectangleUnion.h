/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: folklore (sweep line + segment tree)
 * Description: Area of the union of axis-aligned rectangles.
 * A rectangle is $\{x_1, y_1, x_2, y_2\}$ and covers $[x_1, x_2) \times [y_1, y_2)$.
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

typedef array<ll, 4> Rect;
ll rectUnion(vector<Rect> r) {
	vector<ll> ys;
	for (Rect& a : r) ys.push_back(a[1]), ys.push_back(a[3]);
	sort(all(ys)); ys.erase(unique(all(ys)), ys.end());
	int m = sz(ys) - 1;
	if (m < 1) return 0;
	vi c(4*m); vector<ll> cov(4*m);
	auto upd = [&](auto&& self, int o, int lo, int hi, int l, int r, int d) {
		if (r <= lo || hi <= l) return;
		if (l <= lo && hi <= r) c[o] += d;
		else {
			int mid = (lo + hi) / 2;
			self(self, 2*o, lo, mid, l, r, d); self(self, 2*o+1, mid, hi, l, r, d);
		}
		cov[o] = c[o] ? ys[hi] - ys[lo] : hi - lo == 1 ? 0 : cov[2*o] + cov[2*o+1];
	};
	vector<array<ll, 4>> ev; // x, -delta, y1, y2
	for (Rect& a : r) if (a[0] < a[2] && a[1] < a[3]) {
		ev.push_back({a[0], -1, a[1], a[3]});
		ev.push_back({a[2], 1, a[1], a[3]});
	}
	sort(all(ev));
	ll ans = 0, px = 0;
	for (auto& e : ev) {
		ans += cov[1] * (e[0] - px); px = e[0];
		int l = int(lower_bound(all(ys), e[2]) - ys.begin());
		int h = int(lower_bound(all(ys), e[3]) - ys.begin());
		upd(upd, 1, 0, m, l, h, int(-e[1]));
	}
	return ans;
}
