#include "../utilities/template.h"

#include "../../content/combinatorial/Binomial.h"

int main() {
	const int N = 1500;
	initFact(N);
	vector<vector<ll>> pas(N + 1, vector<ll>(N + 1));
	rep(n,0,N+1) {
		pas[n][0] = 1;
		rep(k,1,n+1) pas[n][k] = (pas[n-1][k-1] + (k <= n - 1 ? pas[n-1][k] : 0)) % mod;
	}
	rep(n,0,N+1) {
		rep(k,0,n+1) assert(nCr(n, k) == pas[n][k]);
		assert(nCr(n, -1) == 0 && nCr(n, n + 1) == 0);
	}
	assert(fact[0] == 1 && ifact[0] == 1);
	initFact(1000000);
	assert(nCr(1000000, 500000) == 996692777); // C(10^6, 5*10^5) mod 10^9+7, from Python big integers
	cout << "Tests passed!" << endl;
}
