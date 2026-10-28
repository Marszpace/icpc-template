#include "../utilities/template.h"

#include "../../content/data-structures/LiChao.h"

struct Line { ll k, m; int a, b; }; // active on x in [a, b)

int main() {
	srand(17);
	rep(it,0,6000) {
		int n = 1 + rand() % 40;
		LiChao t(n);
		vector<Line> lines;
		rep(step,0,25) {
			int op = rand() % 3;
			if (op == 0) {
				ll k = rand() % 41 - 20, m = rand() % 401 - 200;
				t.add(k, m);
				lines.push_back({k, m, 0, n});
			} else if (op == 1) {
				ll k = rand() % 41 - 20, m = rand() % 401 - 200;
				int a = rand() % (n + 1), b = rand() % (n + 1);
				if (a > b) swap(a, b);
				t.addSeg(k, m, a, b);
				lines.push_back({k, m, a, b});
			} else {
				int x = rand() % n;
				ll want = LiChao::INF;
				for (Line& l : lines) if (l.a <= x && x < l.b) want = min(want, l.k * x + l.m);
				assert(t.query(x) == want);
			}
		}
		rep(x,0,n) {
			ll want = LiChao::INF;
			for (Line& l : lines) if (l.a <= x && x < l.b) want = min(want, l.k * x + l.m);
			assert(t.query(x) == want);
		}
	}
	// large coordinates: lines with slopes up to 10^9 on x < 10^6
	{
		const int n = 1000000;
		LiChao t(n);
		vector<pair<ll, ll>> ls;
		rep(i,0,300) {
			ll k = rand() % 2000000001LL - 1000000000, m = rand() % 2000000001LL - 1000000000;
			ls.push_back({k, m});
			t.add(k, m);
		}
		rep(q,0,2000) {
			int x = rand() % n;
			ll want = LiChao::INF;
			for (auto& l : ls) want = min(want, l.first * x + l.second);
			assert(t.query(x) == want);
		}
	}
	cout << "Tests passed!" << endl;
}
