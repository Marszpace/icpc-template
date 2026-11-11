/**
 * Author: Håkan Terelius
 * Date: 2009-09-25
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Euler's_totient_function
 * Description: Sieve of Euler's $\phi$ below LIM. $\phi(n) = n \prod_{p \mid n} (1 - 1/p)$, $\sum_{d \mid n} \phi(d) = n$,
 * $\sum_{k \le n, \gcd(k, n) = 1} k = n\phi(n)/2$ ($n > 1$). Euler: $a^{\phi(n)} \equiv 1 \pmod n$ if $\gcd(a, n) = 1$.
 * Status: Tested; stress-tested
 */
#pragma once

const int LIM = 5000000;
int phi[LIM];

void calculatePhi() {
	rep(i,0,LIM) phi[i] = i&1 ? i : i/2;
	for (int i = 3; i < LIM; i += 2) if(phi[i] == i)
		for (int j = i; j < LIM; j += i) phi[j] -= phi[j] / i;
}
