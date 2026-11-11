#include "../utilities/template.h"

// TEST_MODS: 998244353 1000000007

#include "../../content/data-structures/Matrix.h"
#include "../../content/number-theory/ModularArithmetic.h"

template<class T, int N> array<array<T, N>, N> mul(const array<array<T, N>, N>& a, const array<array<T, N>, N>& b) {
	array<array<T, N>, N> c{};
	rep(i,0,N) rep(j,0,N) rep(k,0,N) c[i][j] += a[i][k] * b[k][j];
	return c;
}

signed main() {
	srand(49);
	// with ll: A^p by repeated multiplication, and the vector product
	rep(it,0,2000) {
		Matrix<ll, 3> A;
		for (auto& r : A.d) for (ll& x : r) x = rand() % 5 - 2;
		int p = rand() % 12;
		auto want = array<array<ll, 3>, 3>{};
		rep(i,0,3) want[i][i] = 1;
		rep(i,0,p) want = mul<ll, 3>(want, A.d);
		assert((A ^ p).d == want);
		array<ll, 3> v = {rand() % 9 - 4, rand() % 9 - 4, rand() % 9 - 4}, w{};
		rep(i,0,3) rep(j,0,3) w[i] += want[i][j] * v[j];
		assert((A ^ p) * v == w);
		Matrix<ll, 3> B; for (auto& r : B.d) for (ll& x : r) x = rand() % 5 - 2;
		assert((A * B).d == (mul<ll, 3>(A.d, B.d)));
	}
	// with the team's mint: Fibonacci mod mod at a huge index
	{
		Matrix<mi, 2> F;
		F.d = {{{{1, 1}}, {{1, 0}}}};
		auto r = F ^ (ll)1e18;
		// F(1e18) mod mod by fast doubling
		auto fib = [&](auto&& self, ll n) -> pair<ll, ll> {
			if (!n) return {0, 1};
			auto [a, b] = self(self, n / 2);
			ll c = a * ((2 * b - a + mod) % mod) % mod, d = (a * a + b * b) % mod;
			return n & 1 ? make_pair(d, (c + d) % mod) : make_pair(c, d);
		};
		assert(r.d[0][1].v == fib(fib, (ll)1e18).first);
		Matrix<mi, 2> I = F ^ 0;
		assert(I.d[0][0].v == 1 && I.d[0][1].v == 0);
	}
	cout << "Tests passed!" << endl;
}
