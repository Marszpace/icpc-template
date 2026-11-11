/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: DSU with undo (\texttt{rollback(time())}); skip \texttt{st}, \texttt{time}, \texttt{rollback} if not needed.
 * If \texttt{join} returns false and $\texttt{par(a)} \oplus \texttt{par(b)} \ne w$, the demand is contradictory.
 * Usage: int t = uf.time(); ...; uf.rollback(t);
 * Time: $O(\log(N))$
 * Status: tested as part of DirectedMST.h and DynCon.h
 */
#pragma once

struct RollbackUF {
	vi e, d; vector<pii> st;
	RollbackUF(int n) : e(n, -1), d(n) {}
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : find(e[x]); }
	int par(int x) { return e[x] < 0 ? 0 : d[x] ^ par(e[x]); }
	int time() { return sz(st); }
	void rollback(int t) {
		for (int i = time(); i --> t;)
			e[st[i].first] = st[i].second;
		st.resize(t);
	}
	bool join(int a, int b, int w = 0) { // par(a)^par(b) = w
		int x = par(a) ^ par(b) ^ w;
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		st.push_back({a, e[a]});
		st.push_back({b, e[b]});
		e[a] += e[b]; e[b] = a; d[b] = x;
		return true;
	}
};
