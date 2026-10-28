#include "../utilities/template.h"

#include "../../content/number-theory/LinearSieve.h"

int main() {
	const int N = 3000;
	linearSieve(N);
	rep(n,1,N+1) {
		// brute force by trial division
		int m = n, least = n == 1 ? 0 : -1, mu = 1, phi = n;
		bool sqfree = true;
		for (int p = 2; p <= m; p++) if (m % p == 0) {
			if (least < 0) least = p;
			int e = 0;
			while (m % p == 0) m /= p, e++;
			if (e > 1) sqfree = false;
			mu = -mu;
			phi = phi / p * (p - 1);
		}
		if (!sqfree) mu = 0;
		assert(lp[n] == least);
		assert(mob[n] == mu);
		assert(tot[n] == phi);
	}
	// classic identities
	rep(n,1,N+1) {
		int sm = 0, st = 0;
		rep(d,1,n+1) if (n % d == 0) sm += mob[d], st += tot[d];
		assert(sm == (n == 1));
		assert(st == n);
	}
	// big run: pi(10^7) = 664579, and speed
	primes.clear();
	linearSieve(10000000);
	assert(sz(primes) == 664579);
	assert(lp[9999991] == 9999991 && lp[10000000] == 2);
	cout << "Tests passed!" << endl;
}
