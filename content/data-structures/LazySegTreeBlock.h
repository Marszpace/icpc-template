/**
 * Author: Claude
 * Date: 2026-10-30
 * License: CC0
 * Source: folklore (segment tree beats, Ji Driver)
 * Description: The part of \texttt{LazySeg} you edit. Range chmin and range add, queries sum / max / count of max (segment tree beats).
 * A tag is $x \mapsto \min(x, c) + a$: chmin $v$ is \texttt{\{v, 0\}}, add $v$ is \texttt{\{INF, v\}}. \texttt{S()} is a leaf with value 0.
 * To change it, \texttt{L} must stay closed under \texttt{comp}, and \texttt{app} must act on the aggregate like the tag acts on every element.
 * \texttt{ok(s, x)} says whether $x$ can be applied to the whole segment $s$ without looking inside (else it recurses).
 * \textbf{Add only:} \texttt{ok} returns 1, drop \texttt{se, cnt}.
 * \textbf{Min query:} add \texttt{mn}, \texttt{op} takes min, \texttt{app}: \texttt{mn = min(mn, x.c) + x.a}.
 * \textbf{Chmax instead of chmin:} store $-a_i$ (chmax $v$ = chmin $-v$, add $v$ = add $-v$), negate the answers.
 * \textbf{Set, add, mul:} \texttt{L} = $(a, b)$, $x \mapsto ax + b$, \texttt{id} = \texttt{\{1, 0\}}, set $v$ = \texttt{\{0, v\}}, add = \texttt{\{1, v\}}, mul = \texttt{\{v, 0\}},
 * \texttt{app} = \texttt{a * s + b * len} (sum) or \texttt{a * s + b} (max, $a \ge 0$), \texttt{comp(x, y)} = \texttt{\{x.a * y.a, x.a * y.b + x.b\}}, \texttt{ok} returns 1.
 * \textbf{Chmin, chmax, add, set with only max / min queries:} \texttt{L} = $(a, lo, hi)$, $x \mapsto \min(\max(x + a, lo), hi)$, set $v$ = \texttt{\{0, v, v\}},
 * \texttt{comp(x, y)}: $a$ = \texttt{x.a + y.a}, and \texttt{lo, hi} = \texttt{y.lo, y.hi} each shifted by \texttt{x.a}, then clamped to \texttt{[x.lo, x.hi]}.
 * Status: stress-tested
 */
#pragma once

const ll INF = 1e18;
struct S { ll mx = 0, se = -INF, cnt = 1, sum = 0; };
struct L { ll c, a; };
S e() { return {-INF, -INF, 0, 0}; }
L id() { return {INF, 0}; }
S op(S a, S b) {
	if (a.mx < b.mx) swap(a, b);
	if (a.mx == b.mx) return {a.mx, max(a.se, b.se), a.cnt + b.cnt, a.sum + b.sum};
	return {a.mx, max(a.se, b.mx), a.cnt, a.sum + b.sum};
}
bool ok(S s, L x) { return x.c > s.se; }
S app(S s, L x, int len) {
	if (x.c < s.mx) s.sum -= (s.mx - x.c) * s.cnt, s.mx = x.c;
	s.sum += x.a * len; s.mx += x.a;
	if (s.se > -INF / 2) s.se += x.a;
	return s;
}
L comp(L x, L y) { return {min(y.c, x.c - y.a), x.a + y.a}; }
