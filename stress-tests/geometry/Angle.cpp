#include "../utilities/template.h"

#include "../../content/geometry/Angle.h"

typedef long double D;
const D PI = acosl(-1);
// the real angle an Angle stands for: direction in [0, 2pi) plus 2pi per turn
D val(Angle a) {
	D b = atan2l((D)a.y, (D)a.x);
	if (b < 0) b += 2 * PI;
	return b + 2 * PI * (D)a.t;
}
bool same(D a, D b) { return fabsl(a - b) < 1e-12; }

mt19937 rng(53);
int rnd(int n) { return (int)(rng() % (unsigned)n); }
Angle randA(int R, int T) {
	int x, y;
	do x = rnd(2*R+1) - R, y = rnd(2*R+1) - R; while (!x && !y);
	return Angle(x, y, rnd(2*T+1) - T);
}

signed main() {
	rep(it,0,300000) {
		int R = it % 2 ? 3 : 1000;
		Angle a = randA(R, 2), b = randA(R, 2);
		D va = val(a), vb = val(b);
		// order
		if (same(va, vb)) assert(!(a < b) && !(b < a));
		else assert((a < b) == (va < vb));
		// a - b is a vector that keeps the turn count of a
		Angle df = a - b;
		assert(df.x == a.x - b.x && df.y == a.y - b.y && df.t == a.t);
		// rotations
		assert(same(val(a.t90()), va + PI / 2));
		assert(same(val(a.t180()), va + PI));
		assert(same(val(a.t360()), va + 2 * PI));
		// angleDiff: angle b - angle a (a rotated vector at the difference)
		Angle d = angleDiff(a, b);
		assert(same(val(d), vb - va));
		// segmentAngles: the smaller angular interval covering the segment a b (both t = 0)
		Angle a0(a.x, a.y), b0(b.x, b.y);
		D cr = (D)a0.x * b0.y - (D)a0.y * b0.x;
		if (cr != 0 || (D)a0.x * b0.x + (D)a0.y * b0.y > 0) { // not through the origin
			auto [s, e] = segmentAngles(a0, b0);
			D w = val(e) - val(s);
			assert(w >= -1e-12 && w < PI);
			D ds = fmodl(val(s), 2 * PI), de = fmodl(val(e), 2 * PI);
			D x = val(a0), y = val(b0);
			assert((same(ds, x) && same(de, y)) || (same(ds, y) && same(de, x)));
		}
		// point a + vector b: the turn count follows the point continuously
		Angle v(b.x, b.y);
		if (a.x + v.x || a.y + v.y) { // a + v must not be the origin
			Angle r = a + v;
			D c2 = (D)a.x * r.y - (D)a.y * r.x, dt = (D)a.x * r.x + (D)a.y * r.y;
			if (c2 != 0 || dt > 0) { // not exactly opposite
				D diff = val(r) - va;
				assert(fabsl(diff) < PI);
				assert(same(fmodl(val(r) - 2 * PI * (D)r.t, 2 * PI), fmodl(atan2l((D)r.y, (D)r.x) + 2 * PI, 2 * PI)));
			}
		}
	}
	// the Usage sweep: count pairs (i, j) with 0 < angle(j) - angle(i) < pi
	rep(it,0,300) {
		int n = 1 + rnd(30);
		vector<Angle> w;
		rep(i,0,n) w.push_back(randA(10, 0));
		sort(all(w));
		vector<Angle> v = w;
		for (Angle x : w) v.push_back(x.t360());
		ll cnt = 0; int j = 0;
		rep(i,0,n) {
			while (v[j] < v[i].t180()) ++j;
			// v[i] itself and the equal ones are before j too; count strictly between
			int k = i; while (k < sz(v) && !(v[i] < v[k])) k++;
			cnt += j - k;
		}
		ll want = 0;
		rep(i,0,n) rep(k,0,n) if ((ll)w[i].x * w[k].y - (ll)w[i].y * w[k].x > 0) want++;
		assert(cnt == want);
	}
	cout << "Tests passed!" << endl;
}
