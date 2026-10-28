/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: https://arxiv.org/abs/1506.04862 (Eertree)
 * Description: Palindromic tree (eertree). Node 0 has length $-1$, node 1 is the empty
 * palindrome, every other node is a distinct palindromic substring of the string
 * (so there are \texttt{sz(t) - 2} of them). \texttt{link} is the longest proper palindromic
 * suffix, \texttt{last} the node of the longest palindromic suffix of the current prefix.
 * After \texttt{count()}, \texttt{cnt[v]} is the number of occurrences of palindrome $v$.
 * Time: O(N) amortized for N characters over a fixed alphabet (26 letters)
 * Status: stress-tested
 */
#pragma once

struct PalTree {
	struct Nd {
		int len, link, cnt = 0; array<int, 26> nx;
		Nd(int len, int link) : len(len), link(link) { nx.fill(0); }
	};
	vector<Nd> t{Nd(-1, 0), Nd(0, 0)};
	string s; int last = 1;
	void add(char ch) {
		s += ch;
		int c = ch - 'a', i = sz(s) - 1;
		auto up = [&](int v) {
			while (i - t[v].len - 1 < 0 || s[i - t[v].len - 1] != ch) v = t[v].link;
			return v;
		};
		int cur = up(last);
		if (!t[cur].nx[c]) {
			int nw = sz(t), lk = t[cur].len < 0 ? 1 : t[up(t[cur].link)].nx[c];
			t.emplace_back(t[cur].len + 2, lk);
			t[cur].nx[c] = nw;
		}
		last = t[cur].nx[c]; t[last].cnt++;
	}
	void count() { for (int v = sz(t); v-- > 2;) t[t[v].link].cnt += t[v].cnt; }
};
