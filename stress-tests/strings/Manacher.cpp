#include "../utilities/template.h"

#include "../../content/strings/Manacher.h"

signed main() {
	srand(44);
	rep(it,0,200000) {
		int n = rand() % 14, k = 1 + rand() % 3;
		string s(n, 'a');
		for (char& c : s) c = (char)('a' + rand() % k);
		auto p = manacher(s);
		assert(sz(p[0]) == n + 1 && sz(p[1]) == n);
		auto isPal = [&](int l, int r) { // [l, r)
			if (l < 0 || r > n) return false;
			rep(i,0,(r-l)/2) if (s[l+i] != s[r-1-i]) return false;
			return true;
		};
		rep(i,0,n+1) { // even: s[i-k .. i+k) for the largest k
			int k2 = 0;
			while (isPal(i - k2 - 1, i + k2 + 1)) k2++;
			if (i < n) assert(p[0][i] == k2);
			else assert(p[0][i] == 0);
		}
		rep(i,0,n) { // odd: s[i-k .. i+k]
			int k2 = 0;
			while (isPal(i - k2 - 1, i + k2 + 2)) k2++;
			assert(p[1][i] == k2);
		}
	}
	// long input: all equal letters
	{
		int n = 2000000; string s(n, 'z'); // O(n^2) would time out
		auto p = manacher(s);
		rep(i,0,n) assert(p[1][i] == min(i, n - 1 - i) && p[0][i] == min(i, n - i));
	}
	cout << "Tests passed!" << endl;
}
