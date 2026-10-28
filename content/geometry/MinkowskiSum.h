/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: https://cp-algorithms.com/geometry/minkowski.html
 * Description: Minkowski sum $\{p + q\}$ of two convex polygons given in
 * ccw order (at least 3 vertices, no three collinear). Returns a convex
 * polygon in ccw order. Two convex polygons $A, B$ intersect iff the
 * origin is in $A + (-B)$, and their distance is the distance from the
 * origin to it. With integer points, cross products must fit in 64 bits.
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
