/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data. Here each node
 *  keeps the sum of its subtree, with lazy range add and
 *  range reverse: \texttt{go(t, l, r, f)} runs \texttt{f} on the
 *  subtree holding positions $[l, r)$ (see the comment above it).
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once

struct Node {
	Node *l = 0, *r = 0;
	ll val, sum, add = 0;
	int y, c = 1;
	bool rev = 0;
	Node(ll val) : val(val), sum(val), y(rand()) {}
	void recalc(), push();
	void app(ll a, bool f) { // add a to all values, reverse if f
		val += a, sum += a * c, add += a;
		if (f) rev ^= 1, swap(l, r);
	}
};

int cnt(Node* n) { return n ? n->c : 0; }
ll sm(Node* n) { return n ? n->sum : 0; }
void Node::recalc() {
	c = cnt(l) + cnt(r) + 1, sum = sm(l) + sm(r) + val;
}
void Node::push() {
	if (l) l->app(add, rev);
	if (r) r->app(add, rev);
	add = rev = 0;
}

template<class F> void each(Node* n, F f) {
	if (n) {
		n->push(); each(n->l, f); f(n->val); each(n->r, f);
	}
}

pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
	n->push();
	if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
		auto [L,R] = split(n->l, k);
		n->l = R;
		n->recalc();
		return {L, n};
	} else {
		auto [L,R] = split(n->r,k - cnt(n->l) - 1); // and just "k"
		n->r = L;
		n->recalc();
		return {n, R};
	}
}

Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
	if (l->y > r->y) {
		l->push();
		l->r = merge(l->r, r);
		return l->recalc(), l;
	} else {
		r->push();
		r->l = merge(l, r->l);
		return r->recalc(), r;
	}
}

Node* ins(Node* t, Node* n, int pos) {
	auto [l,r] = split(t, pos);
	return merge(merge(l, n), r);
}

// Run f on the subtree of positions [l, r), e.g.
// go(t, l, r, [&](Node* n) { n->app(5, 0); }); // add 5
// app(0, 1) reverses, n->sum is the sum (f skipped if empty).
template<class F> void go(Node*& t, int l, int r, F f) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
	if (b) f(b);
	t = merge(merge(a, b), c);
}

// Example application: move the range [l, r) to index k
void move(Node*& t, int l, int r, int k) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
	if (k <= l) t = merge(ins(a, b, k), c);
	else t = merge(a, ins(c, b, k - r));
}
