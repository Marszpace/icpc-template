#include "../utilities/template.h"

#include "../../content/strings/PalindromicTree.h"

bool isPal(const string& s) { return equal(s.begin(), s.end(), s.rbegin()); }

int main() {
	srand(9);
	rep(it,0,6000) {
		int n = 1 + rand() % 25, k = 1 + rand() % 3;
		string s;
		rep(i,0,n) s += char('a' + rand() % k);
		PalTree pt;
		rep(i,0,n) {
			pt.add(s[i]);
			// longest palindromic suffix of the prefix
			int best = 0;
			rep(len,1,i+2) if (isPal(s.substr(i + 1 - len, len))) best = len;
			assert(pt.t[pt.last].len == best);
		}
		pt.count();
		// brute force: every palindromic substring with its number of occurrences
		map<string, int> occ;
		rep(i,0,n) rep(len,1,n-i+1) if (isPal(s.substr(i, len))) occ[s.substr(i, len)]++;
		assert(sz(pt.t) - 2 == sz(occ));
		// read the strings off the tree
		map<string, int> got;
		vector<string> str(sz(pt.t));
		auto dfs = [&](auto&& self, int v) -> void {
			if (v >= 2) got[str[v]] = pt.t[v].cnt;
			rep(c,0,26) if (pt.t[v].nx[c]) {
				string ch(1, char('a' + c));
				str[pt.t[v].nx[c]] = v == 0 ? ch : ch + str[v] + ch;
				self(self, pt.t[v].nx[c]);
			}
		};
		dfs(dfs, 0);
		dfs(dfs, 1);
		assert(got == occ);
		// each suffix link is the longest proper palindromic suffix
		rep(v,2,sz(pt.t)) {
			int best = 0;
			rep(len,1,sz(str[v])) if (isPal(str[v].substr(sz(str[v]) - len))) best = len;
			assert(pt.t[pt.t[v].link].len == best);
		}
	}
	// speed
	{
		PalTree pt;
		rep(i,0,300000) pt.add(char('a' + rand() % 2));
		pt.count();
		assert(sz(pt.t) <= 300002);
		PalTree same;
		rep(i,0,300000) same.add('a');
		assert(sz(same.t) == 300002);
	}
	cout << "Tests passed!" << endl;
}
