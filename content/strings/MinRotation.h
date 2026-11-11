/**
 * Author: Stjepan Glavina
 * License: Unlicense
 * Source: https://github.com/stjepang/snippets/blob/master/min_rotation.cpp
 * Description: Start of the lexicographically smallest rotation.
 * Time: O(N)
 * Usage:
 *  rotate(v.begin(), v.begin()+minRotation(v), v.end());
 * Status: Stress-tested
 */
#pragma once

int minRotation(string s) {
	int a=0, N=sz(s); s += s;
	rep(b,0,N) rep(k,0,N) {
		if (a+k==b || s[a+k]<s[b+k]) {b += max<int>(0,k-1); break;}
		if (s[a+k] > s[b+k]) { a = b; break; }
	}
	return a;
}
