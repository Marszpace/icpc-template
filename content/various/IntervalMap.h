/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: folklore (Chtholly tree / ODT)
 * Description: Partitions $[lo, hi)$ into intervals that each hold a value.
 * \texttt{assign} overwrites a range and merges equal neighbours.
 * \texttt{each} calls \texttt{f(a, b, T\& val)} on the pieces of $[l, r)$
 * and lets \texttt{f} modify the values (e.g. range add, range count).
 * With only \texttt{assign}, also replaces a set of disjoint intervals:
 * \texttt{T = bool}, \texttt{m.assign(l, r, 1)} adds, \texttt{0} removes.
 * Usage: IntervalMap<int> m(0, n, 0); m.assign(l, r, v);
 *  m.each(l, r, [\&](int a, int b, int\& x){ ... }); m.get(i);
 * Time: amortized $O(\log N)$ per assign, plus pieces visited by each
 * Status: stress-tested
 */
#pragma once

template<class T> struct IntervalMap {
	map<int, T> m; int hi; // m[x] = value on [x, next key)
	typedef typename map<int, T>::iterator It;
	IntervalMap(int lo, int hi, T v) : hi(hi) { m[lo] = v; m[hi]; }
	It split(int x) { // makes x a key
		It it = m.lower_bound(x);
		return it->first == x ? it :
			m.emplace_hint(it, x, prev(it)->second);
	}
	T get(int x) { return prev(m.upper_bound(x))->second; }
	template<class F> void each(int l, int r, F f) {
		It it = split(l), e = split(r);
		for (; it != e; ++it) f(it->first, next(it)->first, it->second);
	}
	void assign(int l, int r, T v) { // l < r
		It it = split(l), e = split(r);
		it->second = v; m.erase(next(it), e);
		if (e->first != hi && e->second == v) m.erase(e);
		if (it != m.begin() && prev(it)->second == v) m.erase(it);
	}
};
