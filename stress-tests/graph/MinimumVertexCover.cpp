#include "../utilities/template.h"

#include "../../content/graph/MinimumVertexCover.h"
// DFSMatching.h is cut from the book; it stays here as an independent oracle
#include "../../content/graph/DFSMatching.h"

signed main() {
	const int MAXN = 20;
	mt19937 rng(17);
	rep(it,0,300'000) {
		int N = rand() % MAXN, M = rand() % MAXN;
		vector<vi> gr(N);
		int co = rand() % 128 < 10 ? 2 : 1;
		rep(_,0,co) {
			int prop = rand();
			if (max(N, M) >= 5 && rand() % 128 < 90) {
				prop /= max(N, M);
				prop *= 2;
			}
			rep(i,0,N) rep(j,0,M) if (rand() < prop) {
				gr[i].push_back(j);
			}
		}
		if (rand() % 128 < 20 && N && M) {
			int paths = rand() % min(N, M);
			vi left(N), right(M);
			rep(i,0,N) left[i] = i;
			rep(i,0,M) right[i] = i;
			rep(_,0,paths) {
				shuffle(all(left), rng);
				shuffle(all(right), rng);
				int len = rand() % min(N, M) + 1;
				if (rand() & 128) gr[left[0]].push_back(right[0]);
				rep(i,1,len-1) {
					gr[left[i]].push_back(right[i-1]);
					gr[left[i]].push_back(right[i]);
				}
				if (len > 1 && (rand() & 128)) gr[left.back()].push_back(right.back());
			}
		}
		rep(i,0,N) {
			// Duplicate edges are okay
			// sort(all(gr[i]));
			// gr[i].erase(unique(all(gr[i])), gr[i].end());
			shuffle(all(gr[i]), rng);
		}
		auto verify = [&](vi& cover) {
			vi left(N), right(M);
			for(auto &x: cover) {
				if (x < N) left[x] = 1;
				else right[x - N] = 1;
			}
			rep(i,0,N) if (!left[i]) for(auto &j:gr[i]) {
				assert(right[j]);
				/* if (!right[j]) {
					cout << N << ' ' << M << endl;
					rep(i,0,N) for(auto &j: gr[i]) cout << i << " - " << j << endl;
					cout << "yields " << sz(cover) << endl;
					for(auto &x: cover) cout << x << endl;
					abort();
				} */
			}
		};
		vi cover1 = cover(gr, N, M);
		vi match(M, -1);
		assert(sz(cover1) == dfsMatching(gr, match)); // size of a maximum matching
		verify(cover1);
		// cout << '.' << endl;
	}
	cout<<"Tests passed!"<<endl;
}
