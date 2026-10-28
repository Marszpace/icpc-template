/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: https://cp-algorithms.com/geometry/halfplane-intersection.html
 * Description: Intersection of half-planes. Each half-plane is a pair
 * $(s, e)$: the points on the left of the directed line $s \to e$.
 * Returns the vertices of the intersection in ccw order, or an empty
 * vector if it is empty. Use \texttt{Point<double>}, and add a large
 * bounding box (4 half-planes) if the intersection may be unbounded.
 * Touching or degenerate results may come back either empty or with
 * (almost) zero area.
 * Usage: vector<pair<P,P>> h = {{s1, e1}, {s2, e2}, ...};
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

#include "lineIntersection.h"

template<class P> vector<P> halfPlanes(vector<pair<P, P>> h) {
	typedef pair<P, P> H;
	const double eps = 1e-9;
	auto dir = [](H& l) { return l.second - l.first; };
	auto out = [&](H& l, P p) { return dir(l).cross(p - l.first) < -eps; };
	auto inter = [](H& a, H& b) {
		return lineInter(a.first, a.second, b.first, b.second).second; };
	sort(all(h), [&](H a, H b) { return dir(a).angle() < dir(b).angle(); });
	vector<H> q(sz(h));
	int a = 0, b = 0;
	for (H& l : h) {
		for (; b - a > 1 && out(l, inter(q[b-1], q[b-2])); b--);
		for (; b - a > 1 && out(l, inter(q[a], q[a+1])); a++);
		if (b > a && fabs(dir(l).cross(dir(q[b-1]))) < eps) {
			if (dir(l).dot(dir(q[b-1])) < 0) return {};
			if (out(l, q[b-1].first)) b--; // same direction, l tighter
			else continue;
		}
		q[b++] = l;
	}
	for (; b - a > 2 && out(q[a], inter(q[b-1], q[b-2])); b--);
	for (; b - a > 2 && out(q[b-1], inter(q[a], q[a+1])); a++);
	if (b - a < 3) return {};
	rep(i,a,b) // a bounded polygon turns left by < pi at each corner
		if (dir(q[i]).cross(dir(q[i+1 == b ? a : i+1])) < eps) return {};
	vector<P> r;
	rep(i,a,b) r.push_back(inter(q[i], q[i+1 == b ? a : i+1]));
	return r;
}
