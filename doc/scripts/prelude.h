// What the contest file macros.cpp assumes comes before it.
// Compile with -DLLINT to also test the library with #define int long long.
#include <bits/stdc++.h>
using namespace std;
#ifdef LLINT
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
