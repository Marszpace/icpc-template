/**
 * Author: Mattias de Zalenski, Fredrik Niemelä, Per Austrin, Simon Lindholm
 * Date: 2002-09-26
 * Source: Max Bennedich
 * Description: Exact while it fits in \texttt{ll}.
 * Status: Tested on kattis:lexicography; stress-tested
 */
#pragma once

ll multinomial(vi& v) { // (sum k)! / prod k!
	ll c = 1, m = v.empty() ? 1 : v[0];
	rep(i,1,sz(v)) rep(j,0,v[i]) c = c * ++m / (j+1);
	return c;
}
