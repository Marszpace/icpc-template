#include "../utilities/template.h"

#include "../../content/number-theory/PrimitiveRoot.h"

bool isPrime(ull p) {
	if (p < 2) return false;
	for (ull d = 2; d * d <= p; d++) if (p % d == 0) return false;
	return true;
}

int main() {
	// all primes below 3000: compare with the definition (order exactly p-1)
	for (ull p = 2; p < 3000; p++) if (isPrime(p)) {
		ull want = 0;
		for (ull g = 1; g < p && !want; g++) {
			ull x = 1, ord = 0;
			do x = x * g % p, ord++; while (x != 1);
			if (ord == p - 1) want = g;
		}
		assert(primitiveRoot(p) == want);
	}
	assert(primitiveRoot(998244353) == 3);
	assert(primitiveRoot(1000000007) == 5);
	// a large prime: check order directly with a separate factorization
	ull p = 999999999989ULL;
	assert(isPrime(p));
	ull g = primitiveRoot(p);
	vector<ull> f;
	ull m = p - 1;
	for (ull d = 2; d * d <= m; d++) if (m % d == 0) { f.push_back(d); while (m % d == 0) m /= d; }
	if (m > 1) f.push_back(m);
	auto isRoot = [&](ull h) {
		for (ull q : f) if (modpow(h, (p - 1) / q, p) == 1) return false;
		return true;
	};
	assert(isRoot(g));
	for (ull h = 2; h < g; h++) assert(!isRoot(h));
	cout << "Tests passed!" << endl;
}
