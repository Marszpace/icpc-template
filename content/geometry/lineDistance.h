/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: Basic math
 * Description:\\
\begin{minipage}{75mm}
Returns the signed distance between point p and the line containing points a and b.
Positive value on left side and negative on right as seen from a towards b. a==b gives nan.
P is supposed to be Point<T> where T is e.g. double or long long.
It uses products in intermediate steps so watch out for overflow if using int or long long.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * Status: tested
 */
#pragma once

#include "Point.h"

template<class P>
double lineDist(P a, P b, P p) {
	return (double)(b-a).cross(p-a)/(b-a).dist();
}
