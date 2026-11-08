// Checks the facts of the Strings note against the repo's own SuffixArray.h / SuffixAutomaton.h.
// Run with doc/note-checks/run-all.sh (compiled after doc/scripts/prelude.h).
#include "../scripts/prelude.h"
#include "../../content/strings/SuffixArray.h"
#include "../../content/strings/SuffixAutomaton.h"

string rnd(int n, int k) { string s; rep(i,0,n) s += (char)('a' + rand() % k); return s; }
set<string> substrings(const string& s) { set<string> r; rep(i,0,sz(s)) rep(j,i+1,sz(s)+1) r.insert(s.substr(i, j - i)); return r; }

signed main() {
	srand(5);
	rep(it,0,3000) {
		int n = 1 + rand() % 12, k = 1 + rand() % 3;
		string s = rnd(n, k);
		set<string> all = substrings(s);
		// suffix array: distinct substrings = sum over suffixes of (length - lcp with the previous one)
		SuffixArray A(s);
		ll cnt = 0, sumlcp = 0;
		rep(i,1,sz(A.sa)) cnt += n - A.sa[i] - A.lcp[i], sumlcp += A.lcp[i];
		assert(cnt == sz(all) && sz(all) == (ll)n * (n + 1) / 2 - sumlcp);
		// lcp of two arbitrary suffixes = range minimum of lcp between their ranks
		vi rk(n + 1);
		rep(i,0,sz(A.sa)) rk[A.sa[i]] = i;
		rep(q,0,20) {
			int i = rand() % n, j = rand() % n;
			if (i == j) continue;
			int l = min(rk[i], rk[j]) + 1, r = max(rk[i], rk[j]), mn = INT_MAX;
			rep(x,l,r+1) mn = min(mn, (int)A.lcp[x]);
			int w = 0;
			while (i + w < n && j + w < n && s[i + w] == s[j + w]) w++;
			assert(mn == w);
		}
		// k-th distinct substring in lexicographic order: walk the suffix array
		vector<string> sorted(all.begin(), all.end());
		rep(q,0,5) {
			int kth = rand() % sz(sorted), left = kth;
			string got;
			rep(i,1,sz(A.sa)) {
				int fresh = n - A.sa[i] - (int)A.lcp[i];
				if (left < fresh) { got = s.substr(A.sa[i], A.lcp[i] + left + 1); break; }
				left -= fresh;
			}
			assert(got == sorted[kth]);
		}
		// suffix automaton: distinct substrings, occurrences, longest common substring with another string
		SuffixAutomaton M;
		for (char c : s) M.extend(c);
		M.count();
		ll d = 0;
		rep(v,1,sz(M.t)) d += M.t[v].len - M.t[M.t[v].link].len;
		assert(d == sz(all));
		string u = rnd(1 + rand() % 12, k);
		int v = 0, len = 0, best = 0;
		for (char c : u) {
			int ci = c - 'a';
			while (v && M.t[v].nx[ci] < 0) v = M.t[v].link, len = M.t[v].len;
			if (M.t[v].nx[ci] >= 0) v = M.t[v].nx[ci], len++;
			best = max(best, len);
		}
		int want = 0;
		for (auto& x : substrings(u)) if (all.count(x)) want = max(want, sz(x));
		assert(best == want);
		// generalized automaton: just resetting last = 0 for every string
		vector<string> set_ = {s, rnd(1 + rand() % 12, k), rnd(1 + rand() % 12, k)};
		set<string> uni;
		for (auto& x : set_) for (auto& y : substrings(x)) uni.insert(y);
		SuffixAutomaton G;
		for (auto& x : set_) { G.last = 0; for (char c : x) G.extend(c); }
		ll gd = 0;
		rep(v2,1,sz(G.t)) gd += G.t[v2].len - G.t[G.t[v2].link].len;
		assert(gd == sz(uni));
		// ... and it accepts exactly the substrings (all strings up to length 6)
		function<void(string)> gen = [&](string x) {
			if (!x.empty()) {
				int w = 0;
				for (char c : x) { w = w < 0 ? w : G.t[w].nx[c - 'a']; }
				assert((w >= 0) == (bool)uni.count(x));
			}
			if (sz(x) < 6) rep(c,0,k) gen(x + (char)('a' + c));
		};
		gen("");
	}
	cout << "suffix array / automaton facts, and the generalized automaton (just reset last = 0 per string): ok\n";
}
