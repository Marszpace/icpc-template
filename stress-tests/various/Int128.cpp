#include "../utilities/template.h"

#include "../../content/various/Int128.h"

typedef unsigned __int128 u128;

// independent reference: parse the decimal string back with Horner
__int128 parse(const string& s) {
	bool neg = s[0] == '-';
	u128 v = 0;
	for (int i = neg; i < sz(s); i++) {
		assert('0' <= s[i] && s[i] <= '9');
		v = v * 10 + (u128)(s[i] - '0');
	}
	return neg ? (__int128)(-v) : (__int128)v;
}

signed main() {
	// known values, computed outside C++
	__int128 one = 1;
	assert(to_string((__int128)0) == "0");
	assert(to_string((__int128)-1) == "-1");
	assert(to_string(one << 100) == "1267650600228229401496703205376");
	assert(to_string(-(one << 100)) == "-1267650600228229401496703205376");
	__int128 mx = (__int128)(((u128)1 << 127) - 1), mn = -mx - 1;
	assert(to_string(mx) == "170141183460469231731687303715884105727");
	assert(to_string(mn) == "-170141183460469231731687303715884105728");
	__int128 p = 1;
	rep(i,0,38) p *= 10;
	assert(to_string(p) == "1" + string(38, '0'));
	assert(to_string(p - 1) == string(38, '9'));
	// operator<<
	ostringstream os;
	os << mn << ' ' << (__int128)0 << ' ' << mx;
	assert(os.str() == "-170141183460469231731687303715884105728 0 170141183460469231731687303715884105727");
	// random values: round trip through the parser, sign and length
	mt19937_64 rng(5);
	rep(it,0,200000) {
		u128 raw = ((u128)rng() << 64) | rng();
		int shift = (int)(rng() % 128);
		__int128 x = (__int128)(raw >> shift);
		if (rng() % 2) x = -x;
		string s = to_string(x);
		assert(parse(s) == x);
		assert((s[0] == '-') == (x < 0));
		assert(s == "0" || s[(s[0] == '-')] != '0'); // no leading zeros
		assert(s != "-0");
	}
	cout<<"Tests passed!"<<endl;
}
