/**
 * Author: Claude
 * Date: 2026-11-09
 * License: CC0
 * Source: folklore
 * Description: Output for \texttt{\_\_int128}, which the standard library
 * cannot print: \texttt{to\_string} and \texttt{operator<<}. Correct for the smallest
 * value too. Input: read a string and do $x = 10x + d$.
 * Usage: __int128 x = (__int128)1 << 100; cout << x << ' ' << to_string(-x);
 * Time: O(\text{digits})
 * Status: stress-tested
 */
#pragma once

string to_string(__int128 x) {
	bool neg = x < 0;
	unsigned __int128 u = neg ? -(unsigned __int128)x : x;
	string s;
	do s += char('0' + u % 10), u /= 10; while (u);
	if (neg) s += '-';
	return string(s.rbegin(), s.rend());
}
ostream& operator<<(ostream& os, __int128 x) {
	return os << to_string(x);
}
