#include "../utilities/template.h"

#include "../../content/combinatorial/multinomial.h"

typedef __int128 L;
signed main() {
	srand(50);
	vector<L> fact(34, 1);
	rep(i,1,34) fact[i] = fact[i-1] * i;
	rep(it,0,200000) {
		int k = rand() % 6;
		vi v(k);
		int tot = 0;
		for (int& x : v) x = rand() % 12, tot += x;
		if (tot > 33) continue;
		L want = fact[tot];
		for (int x : v) want /= fact[x];
		if (want > (L)LLONG_MAX / 34) continue; // intermediate c * m must fit
		assert((L)multinomial(v) == want);
	}
	vi e; assert(multinomial(e) == 1);
	vi one = {7}; assert(multinomial(one) == 1);
	// near the limit: 60! / (30! 30!) = C(60, 30) fits, intermediates too
	vi b = {30, 30}; assert(multinomial(b) == 118264581564861424LL);
	cout << "Tests passed!" << endl;
}
