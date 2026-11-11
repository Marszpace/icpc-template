/**
 * Author: Claude
 * Date: 2026-10-30
 * License: CC0
 * Source: folklore (segment tree beats, Ji Driver)
 * Description: The part of \texttt{LazySeg} you edit. Default: range chmin and add; sum / max / count of max (beats).
 * chmin $v$ = \texttt{\{v, 0\}}, add $v$ = \texttt{\{INF, v\}}; \texttt{S()} is a leaf with value 0.
 * \texttt{comp} must keep tags closed, \texttt{app} must act on the aggregate as the tag acts on each element.
 * \textbf{Add only:} \texttt{ok} = 1, drop \texttt{se, cnt}.
 * \textbf{Min query:} add \texttt{mn}, \texttt{op} takes min, \texttt{app}: \texttt{mn = min(mn, x.c) + x.a}.
 * \textbf{Chmax:} store $-a_i$, negate updates and answers.
 * \textbf{Set, add, mul:} \texttt{L} = $(a, b)$: $x \mapsto ax + b$, \texttt{id} = \texttt{\{1, 0\}}, set $v$ = \texttt{\{0, v\}}, add = \texttt{\{1, v\}}, mul = \texttt{\{v, 0\}},
 * \texttt{app}: \texttt{a*s + b*len} (sum) or \texttt{a*s + b} (max, $a \ge 0$), \texttt{comp(x, y)} = \texttt{\{x.a*y.a, x.a*y.b + x.b\}}, \texttt{ok} = 1.
 * \textbf{Chmin, chmax, add, set; max / min only:} \texttt{L} = $(a, lo, hi)$: $x \mapsto \min(\max(x + a, lo), hi)$, set $v$ = \texttt{\{0, v, v\}},
 * \texttt{comp(x, y)}: $a$ = \texttt{x.a + y.a}, \texttt{lo, hi} = \texttt{y.lo, y.hi} plus \texttt{x.a}, clamped to \texttt{[x.lo, x.hi]}.
 * Status: stress-tested
 */
#pragma once

const ll INF = 1e18;
struct S { ll mx = 0, se = -INF, cnt = 1, sum = 0; };
struct L { ll c, a; }; // tag x -> min(x, c) + a
S e() { return {-INF, -INF, 0, 0}; }
L id() { return {INF, 0}; }
S op(S a, S b) {
	if (a.mx < b.mx) swap(a, b);
	if (a.mx == b.mx) return {a.mx, max(a.se, b.se), a.cnt + b.cnt, a.sum + b.sum};
	return {a.mx, max(a.se, b.mx), a.cnt, a.sum + b.sum};
}
bool ok(S s, L x) { return x.c > s.se; } // x on all of s?
S app(S s, L x, int len) {
	if (x.c < s.mx) s.sum -= (s.mx - x.c) * s.cnt, s.mx = x.c;
	s.sum += x.a * len; s.mx += x.a;
	if (s.se > -INF / 2) s.se += x.a;
	return s;
}
L comp(L x, L y) { return {min(y.c, x.c - y.a), x.a + y.a}; }
