// The team's own ModInt, pasted by the team on 2026-11-08 as the target for the
// "Edit ModInt" item in TODO.md (adapt content/number-theory/ModularArithmetic.h to it).
// Needs M defined before the two `using` lines.
template <int mod> struct mint {
    int v;
    explicit operator int() const { return v; } // explicit -> don't silently convert to int
    mint() : v(0) {}
    mint(ll _v) {
        v = _v % mod;
        if (v < 0) v += mod;
    }
    bool operator==(const mint &o) const { return v == o.v; }
    friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
    friend bool operator<(const mint &a, const mint &b) { return a.v < b.v; }
    friend istream &operator>>(istream &is, mint &a) {
        ll x;
        is >> x;
        a = mint(x);
        return is;
    }
    friend ostream &operator<<(ostream &os, mint a) {
        os << int(a);
        return os;
    }

    mint &operator+=(const mint &o) {
        if ((v += o.v) >= mod) v -= mod;
        return *this;
    }
    mint &operator-=(const mint &o) {
        if ((v -= o.v) < 0) v += mod;
        return *this;
    }
    mint &operator*=(const mint &o) {
        v = int((ll)v * o.v % mod);
        return *this;
    }
    mint &operator/=(const mint &o) { return (*this) *= inverse(o); }
    friend mint fpow(mint a, ll p) {
        mint ans = 1;
        assert(p >= 0);
        for (; p; p /= 2, a *= a)
            if (p & 1) ans *= a;
        return ans;
    }
    friend mint inverse(const mint &a) {
        assert(a.v != 0);
        return fpow(a, mod - 2);
    }

    mint operator-() const { return mint(-v); }
    mint &operator++() { return *this += 1; }
    mint &operator--() { return *this -= 1; }
    mint operator++(int) { mint ret = *this; ++*this; return ret; }
    mint operator--(int) { mint ret = *this; --*this; return ret; }
    friend mint operator+(mint a, const mint &b) { return a += b; }
    friend mint operator-(mint a, const mint &b) { return a -= b; }
    friend mint operator*(mint a, const mint &b) { return a *= b; }
    friend mint operator/(mint a, const mint &b) { return a /= b; }
};
using mi = mint<M>;
using vmi = vector<mi>;
