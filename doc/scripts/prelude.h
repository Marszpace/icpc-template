// What the contest file macros.cpp assumes comes before it.
// Compile with -DLLINT to also test the library with #define int long long.
#include <bits/stdc++.h>
using namespace std;
#ifdef LLINT
#define int long long
#endif
#include "../../content/contest/macros.cpp"
