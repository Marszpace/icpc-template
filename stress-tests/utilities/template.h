#include <bits/stdc++.h>
#include <cassert> // not included by bits/stdc++.h since GCC 16
using namespace std;
#ifdef LLINT // run the whole suite with #define int long long
#define int long long
#endif
#include "../../content/contest/macros.cpp"

// Headers that need a modulus use a global `const ll mod` that the solution
// declares first (they never define it). Tests: -DTEST_MOD=<value> overrides.
#ifdef TEST_MOD
const ll mod = TEST_MOD;
#else
const ll mod = 998244353;
#endif
