#include "../utilities/template.h"

#include "../../content/combinatorial/RadixConversion.h"

// all sequences over [0, a) in (length, lexicographic) order, first K
vector<vi> shortlex(int a, int K) {
	vector<vi> res = {{}};
	for (int i = 0; sz(res) < K; i++) rep(d,0,a) {
		vi s = res[i];
		s.push_back(d);
		res.push_back(s);
	}
	res.resize(K);
	return res;
}

// the k-th sequence in base a must go to the k-th sequence in base b
void testOrder(int a, int b) {
	int K = 3000;
	vector<vector<int>> A = shortlex(a, K), B = shortlex(b, K);
	rep(k,0,K) {
		assert(radixconv(A[k], a, b) == B[k]);
		assert(radixconv(B[k], b, a) == A[k]);
	}
}

void testRoundTrip(int n, int a, int b) {
	vi x(n);
	for (int& d : x) d = (int)(((ll)rand() * 32768 + rand()) % a);
	vi y = radixconv(x, a, b);
	for (int d : y) assert(0 <= d && d < b);
	assert(radixconv(y, b, a) == x);
	// about n * log_b(a) digits: m = n log_b a + log_b((b-1)/(a-1)) + [0, log_b a] + O(1)
	double lb = log((double)b), m = (double)sz(y);
	double want = (double)n * log((double)a) / lb + log(((double)b - 1) / ((double)a - 1)) / lb;
	assert(m >= want - 2 && m <= want + log((double)a) / lb + 2);
}

// all permutations of all sizes in (size, lexicographic) order, first K
vector<vi> allPerms(int K) {
	vector<vi> res;
	for (int n = 0; sz(res) < K; n++) {
		vi p(n);
		iota(all(p), 0);
		do res.push_back(p); while (sz(res) < K && next_permutation(all(p)));
	}
	return res;
}

// the k-th digit sequence goes to the k-th permutation, and back
void testPerm(int a) {
	int K = 2500;
	vector<vi> X = shortlex(a, K), P = allPerms(K);
	rep(k,0,K) {
		assert(radixToPerm(X[k], a) == P[k]);
		assert(permToRadix(P[k], a) == X[k]);
	}
}

void testPermRandom(int n, int a, mt19937& rng) {
	vi x(n);
	for (int& d : x) d = (int)(rng() % (unsigned)a);
	vi p = radixToPerm(x, a), s = p;
	sort(all(s));
	rep(i,0,sz(s)) assert(s[i] == i); // a real permutation
	assert(permToRadix(p, a) == x);
	if (sz(p) > 1) { // and the other way round
		int i = (int)(rng() % (unsigned)(sz(p) - 1));
		swap(p[i], p[i + 1]);
		assert(radixToPerm(permToRadix(p, a), a) == p);
	}
}

signed main() {
	srand(3);
	vector<pii> bases = {{2,2},{2,3},{3,2},{2,10},{10,2},{5,7},{7,5},{3,3},{2,16},{16,2},{4,6},{6,4}};
	for (pii p : bases) testOrder((int)p.first, (int)p.second);
	assert(radixconv({}, 2, 10).empty() && radixconv({}, 10, 2).empty());
	int big = 2147483647;
	vi bs = {2, 3, 7, 10, 255, 1000000007, big};
	for (int a : bs) for (int b : bs) rep(it,0,4) testRoundTrip(1 + rand() % 150, a, b);
	testRoundTrip(2000, 2, 10);
	testRoundTrip(2000, big, 2);
	vi tbs = {2, 3, 5, 10, 100};
	for (int a : tbs) testPerm(a);
	mt19937 prng(4);
	assert(radixToPerm({}, 7).empty() && permToRadix({}, 7).empty());
	vi pbs = {2, 3, 7, 10, 1000, big};
	for (int a : pbs) rep(it,0,60)
		testPermRandom((int)(prng() % 300), a, prng);
	rep(it,0,3000) { // (length, lexicographic) goes to (size, lexicographic)
		int a = 2 + (int)(prng() % 9), n = (int)(prng() % 12);
		vi x(n), y(n);
		for (int& d : x) d = (int)(prng() % (unsigned)a);
		for (int& d : y) d = (int)(prng() % (unsigned)a);
		vi p = radixToPerm(x, a), q = radixToPerm(y, a);
		assert((x < y) == (make_pair(sz(p), p) < make_pair(sz(q), q)));
	}
	assert(sz(radixToPerm(vi(2000, 1), 2)) == 296);
	cout<<"Tests passed!"<<endl;
}
