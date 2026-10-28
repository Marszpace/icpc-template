#include "../utilities/template.h"

#include "../../content/strings/SuffixAutomaton.h"

int walk(SuffixAutomaton& sa, const string& w) {
	int v = 0;
	for (char c : w) {
		v = sa.t[v].nx[c - 'a'];
		if (v < 0) return -1;
	}
	return v;
}

int occurrences(const string& s, const string& w) {
	int c = 0;
	for (size_t i = s.find(w); i != string::npos; i = s.find(w, i + 1)) c++;
	return c;
}

int main() {
	srand(5);
	rep(it,0,4000) {
		int n = 1 + rand() % 25, k = 1 + rand() % 3;
		string s;
		rep(i,0,n) s += char('a' + rand() % k);
		SuffixAutomaton sa;
		for (char c : s) sa.extend(c);
		sa.count();
		assert(sz(sa.t) <= 2 * n);

		set<string> subs;
		rep(i,0,n) rep(j,i+1,n+1) subs.insert(s.substr(i, j - i));
		// number of distinct substrings
		ll distinct = 0;
		rep(v,1,sz(sa.t)) {
			assert(sa.t[sa.t[v].link].len < sa.t[v].len);
			distinct += sa.t[v].len - sa.t[sa.t[v].link].len;
		}
		assert(distinct == sz(subs));
		// every substring is accepted, with the right occurrence count and
		// the state's length range containing its length
		for (auto& w : subs) {
			int v = walk(sa, w);
			assert(v >= 0);
			assert(sa.t[v].cnt == occurrences(s, w));
			assert(sa.t[sa.t[v].link].len < sz(w) && sz(w) <= sa.t[v].len);
		}
		// nothing else is accepted: all strings up to length 6 over the alphabet
		rep(len,1,7) {
			int total = 1;
			rep(i,0,len) total *= k;
			rep(x,0,total) {
				string w; int y = x;
				rep(i,0,len) w += char('a' + y % k), y /= k;
				assert((walk(sa, w) >= 0) == (subs.count(w) > 0));
			}
		}
	}
	// speed: 2e5 characters over 26 letters
	{
		SuffixAutomaton sa;
		rep(i,0,200000) sa.extend(char('a' + rand() % 26));
		sa.count();
		assert(sz(sa.t) <= 400000);
	}
	cout << "Tests passed!" << endl;
}
