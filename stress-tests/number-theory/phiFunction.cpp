#include "../utilities/template.h"

#include "../../content/number-theory/phiFunction.h"

signed main() {
	calculatePhi();
	rep(n,1,20001) {
		int c = 0;
		rep(k,1,n+1) c += __gcd(k, n) == 1;
		assert(phi[n] == c);
	}
	// phi(n) = n prod (1 - 1/p) for the rest, by trial division
	for (int n = 20001; n < LIM; n += 997) {
		int m = n; ll r = n;
		for (int p = 2; p * p <= m; p++) if (m % p == 0) { r = r / p * (p - 1); while (m % p == 0) m /= p; }
		if (m > 1) r = r / m * (m - 1);
		assert(phi[n] == r);
	}
	// sum_{d | n} phi(d) = n
	for (int n = 1; n < 3000; n++) {
		int s = 0;
		rep(d,1,n+1) if (n % d == 0) s += phi[d];
		assert(s == n);
	}
	assert(phi[LIM - 1] > 0 && phi[0] == 0);
	cout << "Tests passed!" << endl;
}
