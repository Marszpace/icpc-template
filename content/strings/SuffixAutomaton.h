/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: https://cp-algorithms.com/string/suffix-automaton.html
 * Description: Minimal DFA accepting exactly the suffixes of the string
 * (so every substring is a path from state 0). State $v$ stands for all
 * substrings that end at the same set of positions, with lengths
 * $(\texttt{len[link[v]]}, \texttt{len[v]}]$. Number of distinct
 * substrings is $\sum_{v \ne 0} \texttt{len[v]} - \texttt{len[link[v]]}$.
 * After \texttt{count()}, \texttt{cnt[v]} is the number of occurrences
 * of the strings of $v$. Append characters with \texttt{extend}.
 * Time: O(N) states, O(N \cdot 26) memory, \texttt{count} in $O(N \log N)$
 * Status: stress-tested
 */
#pragma once

struct SuffixAutomaton {
	struct S {
		int len, link = -1, cnt = 0; array<int, 26> nx;
		S(int len) : len(len) { nx.fill(-1); }
	};
	vector<S> t{S(0)}; int last = 0;
	void extend(char ch) {
		int c = ch - 'a', cur = sz(t), p = last;
		t.emplace_back(t[last].len + 1); t[cur].cnt = 1;
		for (; p >= 0 && t[p].nx[c] < 0; p = t[p].link) t[p].nx[c] = cur;
		if (p < 0) t[cur].link = 0;
		else {
			int q = t[p].nx[c];
			if (t[p].len + 1 == t[q].len) t[cur].link = q;
			else {
				int cl = sz(t);
				t.push_back(t[q]); t[cl].len = t[p].len + 1; t[cl].cnt = 0;
				for (; p >= 0 && t[p].nx[c] == q; p = t[p].link)
					t[p].nx[c] = cl;
				t[q].link = t[cur].link = cl;
			}
		}
		last = cur;
	}
	void count() {
		vi o(sz(t)); iota(all(o), 0);
		sort(all(o), [&](int a, int b) { return t[a].len > t[b].len; });
		for (int v : o) if (t[v].link >= 0) t[t[v].link].cnt += t[v].cnt;
	}
};
