#include "../utilities/template.h"

// TEST_MODS: 3
const int nmax = 4, mmax = 4, nmmax = 10;

const int lut[9] = {-4,-2,-3,-1,-100,1,3,2,4};

int modinv(int x) {
	assert(x);
	return x;
	// return lut[x+4];
}

typedef vector<int> vd;

int solveLinear(vector<vd>& A, vd& b, vd& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m);
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		int v, bv = -1;
		rep(r,i,n) rep(c,i,m)
			if ((v = A[r][c])) {
				br = r, bc = c, bv = v;
				goto found;
			}
		rep(j,i,n) if (b[j]) return -1;
		break;
found:
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		bv = modinv(A[i][i]);
		rep(j,i+1,n) {
			int fac = A[j][i] * bv % mod;
			b[j] = (b[j] - fac * b[i]) % mod;
			rep(k,i+1,m) A[j][k] = (A[j][k] - fac*A[i][k]) % mod;
		}
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] = ((b[i] * modinv(A[i][i]) % mod) + mod) % mod;
		x[col[i]] = b[i];
		rep(j,0,i)
			b[j] = (b[j] - A[j][i] * b[i]);
	}
	return rank;
}

template<class F>
void rec(int i, int j, vector<vd>& A, F f) {
	if (i == sz(A)) {
		f();
	}
	else if (j == sz(A[i])) {
		rec(i+1, 0, A, f);
	}
	else {
		rep(v,0,mod) {
			A[i][j] = v;
			rec(i, j+1, A, f);
		}
	}
}

template<class F>
void rec2(int i, vd& A, F f) {
	if (i == sz(A)) f();
	else {
		rep(v,0,mod) {
			A[i] = v;
			rec2(i+1, A, f);
		}
	}
}

// The real header (double version), checked against exact ranks computed mod a big prime.
namespace hdr {
#include "../../content/numerical/SolveLinear.h"
}
mt19937 rng(4);
int rnd(int n) { return (int)(rng() % (unsigned)n); }
int rankP(vector<vector<ll>> a) {
	const ll p = 1000000007;
	auto pw = [&](ll b, ll e) { ll x = 1; for (; e; e /= 2, b = b * b % p) if (e & 1) x = x * b % p; return x; };
	int n = sz(a), m = n ? sz(a[0]) : 0, r = 0;
	for (auto& row : a) for (ll& v : row) v = (v % p + p) % p;
	rep(c,0,m) {
		int piv = -1;
		rep(i,r,n) if (a[i][c]) { piv = i; break; }
		if (piv < 0) continue;
		swap(a[r], a[piv]);
		ll inv = pw(a[r][c], p - 2);
		rep(i,0,n) if (i != r && a[i][c]) {
			ll f = a[i][c] * inv % p;
			rep(k,0,m) a[i][k] = ((a[i][k] - f * a[r][k]) % p + p) % p;
		}
		r++;
	}
	return r;
}
void testHeader() {
	rep(it,0,100000) {
		int n = rnd(7), m = rnd(7), K = rnd(5) + 1;
		vector<vector<ll>> a(n, vector<ll>(m));
		int k = rnd(min(n, m) + 1);
		if (rnd(2)) { // rank <= k
			vector<vector<ll>> u(n, vector<ll>(k)), v(k, vector<ll>(m));
			for (auto& r : u) for (ll& x : r) x = rnd(2*K+1) - K;
			for (auto& r : v) for (ll& x : r) x = rnd(2*K+1) - K;
			rep(i,0,n) rep(j,0,m) rep(t,0,k) a[i][j] += u[i][t] * v[t][j];
		} else for (auto& r : a) for (ll& x : r) x = rnd(2*K+1) - K;
		vector<ll> b(n);
		if (rnd(2)) { // consistent
			vector<ll> x0(m);
			for (ll& x : x0) x = rnd(2*K+1) - K;
			rep(i,0,n) rep(j,0,m) b[i] += a[i][j] * x0[j];
		} else for (ll& x : b) x = rnd(2*K+1) - K;
		int rk = rankP(a);
		auto ab = a;
		rep(i,0,n) ab[i].push_back(b[i]);
		bool consistent = rankP(ab) == rk;
		vector<hdr::vd> A(n, hdr::vd(m));
		hdr::vd B(n), X(m);
		rep(i,0,n) { B[i] = (double)b[i]; rep(j,0,m) A[i][j] = (double)a[i][j]; }
		int r = hdr::solveLinear(A, B, X);
		if (!consistent) { assert(r == -1); continue; }
		assert(r == rk);
		assert(sz(X) == m);
		rep(i,0,n) {
			double s = 0;
			rep(j,0,m) s += (double)a[i][j] * X[j];
			assert(fabs(s - (double)b[i]) < 1e-6);
		}
	}
}

signed main() {
	testHeader();
	rep(n,0,nmax+1) rep(m,0,mmax+1) {
		int nm = n*m;
		if (nm > nmmax) continue;
		vector<vd> A(n, vd(m));
		vd b(n), x(m), theX(m);
		rec(0, 0, A, [&]() {
			rec2(0, b, [&]() {
				int sols = 0;
				rec2(0, x, [&]() {
					rep(i,0,n) {
						int v = 0;
						rep(j,0,m) v += A[i][j] * x[j];
						if (v % mod != b[i]) return;
					}
					sols++;
					if (sols == 1) theX = x;
				});
				vector<vd> A2 = A;
				vd x2 = x, b2 = b;
				int r = solveLinear(A2, b2, x2);
				if (sols == 0) assert(r == -1);
				else if (sols == 1) assert(r == m);
				else assert(r < m);
				if (sols == 1) assert(x2 == theX);
			});
		});
	}
	cout<<"Tests passed!"<<endl;
}
