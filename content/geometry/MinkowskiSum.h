/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: https://cp-algorithms.com/geometry/minkowski.html
 * Description: Of two ccw convex polygons ($\ge 3$ vertices, no 3 collinear), ccw. $A$ and $B$ intersect iff $0 \in A + (-B)$;
 * their distance is the distance from 0 to it.
 * Time: O(n + m)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

template<class P> vector<P> minkowski(vector<P> a, vector<P> b) {
	auto low = [](P p, P q) { return tie(p.y, p.x) < tie(q.y, q.x); };
	rotate(a.begin(), min_element(all(a), low), a.end());
	rotate(b.begin(), min_element(all(b), low), b.end());
	int n = sz(a), m = sz(b);
	a.push_back(a[0]), a.push_back(a[1]);
	b.push_back(b[0]), b.push_back(b[1]);
	vector<P> r;
	for (int i = 0, j = 0; i < n || j < m;) {
		r.push_back(a[i] + b[j]);
		auto c = (a[i+1] - a[i]).cross(b[j+1] - b[j]);
		if (c >= 0 && i < n) i++;
		if (c <= 0 && j < m) j++;
	}
	return r;
}
