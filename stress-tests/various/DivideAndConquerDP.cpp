#include "../utilities/template.h"

// What the "Modify at will" part refers to: dp is the cost table, res the output.
vector<vector<ll>> dp;
vector<pii> res;
#include "../../content/various/DivideAndConquerDP.h"

signed main() {
	srand(45);
	rep(it,0,3000) {
		int n = 1 + rand() % 40;
		// f(i, k) = A[k] + (S[i] - S[k])^2 with S increasing: Monge, so the minimal optimal k is monotone
		vector<ll> A(n), S(n);
		rep(i,0,n) A[i] = rand() % 2000, S[i] = (i ? S[i-1] : 0) + rand() % 30;
		dp.assign(n, vector<ll>(n));
		rep(i,0,n) rep(k,0,n) dp[i][k] = A[k] + (S[i] - S[k]) * (S[i] - S[k]);
		res.assign(n, pii(-1, -1));
		int L = rand() % n, R = L + rand() % (n - L + 1);
		L = max<int>(L, 1); // lo(i) = 0, hi(i) = i: i = 0 has no k
		DP().solve(L, R);
		rep(i,0,n) {
			if (i < L || i >= R) { assert(res[i] == pii(-1, -1)); continue; }
			pair<ll, int> best(LLONG_MAX, -1);
			rep(k,0,i) best = min(best, make_pair(dp[i][k], k));
			assert(res[i].second == best.first && res[i].first == best.second);
		}
	}
	cout << "Tests passed!" << endl;
}
