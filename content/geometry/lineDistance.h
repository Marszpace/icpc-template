/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: Basic math
 * Description: \\
 * \begin{minipage}{75mm}
 * Signed distance from p to the line through a and b; a==b gives nan.
 * \end{minipage}
 * \begin{minipage}{15mm}
 * \includegraphics[width=\textwidth]{content/geometry/lineDistance}
 * \end{minipage}
 * Status: tested
 */
#pragma once

#include "Point.h"

template<class P>
double lineDist(P a, P b, P p) { // > 0: left of a -> b
	return (double)(b-a).cross(p-a)/(b-a).dist();
}
