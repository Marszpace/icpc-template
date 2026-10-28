/**
 * Author: Claude
 * Date: 2026-10-29
 * License: CC0
 * Source: https://cp-algorithms.com/algebra/prime-sieve-linear.html
 * Description: Sieve that gives, for every $i \le n$, the least prime
 * factor \texttt{lp[i]}, the Moebius function \texttt{mob[i]} and Euler's
 * totient \texttt{tot[i]}, plus the list of primes. Factorize in
 * $O(\log n)$ by repeatedly dividing by \texttt{lp}. Use
 * \texttt{FastEratosthenes} instead if only primes up to $10^8$ or more
 * are needed.
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

vi lp, primes, mob, tot;
void linearSieve(int n) {
	lp.assign(n+1, 0); mob = tot = lp; mob[1] = tot[1] = 1;
	rep(i,2,n+1) {
		if (!lp[i]) lp[i] = i, primes.push_back(i), mob[i] = -1, tot[i] = i-1;
		for (int p : primes) {
			if (p > lp[i] || (ll)i*p > n) break;
			lp[i*p] = p;
			if (i % p) mob[i*p] = -mob[i], tot[i*p] = tot[i] * (p-1);
			else mob[i*p] = 0, tot[i*p] = tot[i] * p;
		}
	}
}
