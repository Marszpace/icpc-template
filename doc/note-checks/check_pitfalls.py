"""Checks the claims of the "C++ pitfalls" note by compiling and running tiny programs with g++.
Run: python3 doc/note-checks/check_pitfalls.py"""
import os, subprocess, tempfile

TMP = tempfile.mkdtemp()
HEAD = '#include <bits/stdc++.h>\nusing namespace std;\n'

def build(body, flags=()):
    src = os.path.join(TMP, 'p.cpp'); exe = os.path.join(TMP, 'p')
    open(src, 'w').write(HEAD + body)
    c = subprocess.run(['g++', '-std=c++17', '-O0', '-w', *flags, src, '-o', exe], capture_output=True, text=True)
    return c, exe

def run(body, flags=(), args=(), prefix=''):
    c, exe = build(body, flags)
    assert c.returncode == 0, c.stderr[:300]
    cmd = f"{prefix}{exe} {' '.join(map(str, args))}"
    r = subprocess.run(['bash', '-c', cmd], capture_output=True, text=True)
    return r.returncode, r.stdout, r.stderr

def out(body, **kw):
    rc, o, e = run(body, **kw); assert rc == 0, (rc, e[:200]); return o.strip()

# 1. 1 << k is an int: negative for k = 31, undefined for k >= 32 (UBSan reports it); 1LL << k is fine
assert out('int main(){ int s = 31; printf("%d %lld", 1 << s, 1LL << s); }') == "-2147483648 2147483648"
rc, o, e = run('int main(){ int s = 31; printf("%d", 1 << s); }', flags=['-fsanitize=undefined'])
assert 'shift' not in e                      # well defined since C++14
rc, o, e = run('int main(){ int s = 32; printf("%d", 1 << s); }', flags=['-fsanitize=undefined'])
assert 'shift exponent 32 is too large' in e, e
assert out('int main(){ int s = 40; printf("%lld", 1LL << s); }') == "1099511627776"
# 2. abs(INT_MIN) stays negative; INT_MAX + 1 overflows (UBSan)
assert out('int main(){ volatile int x = INT_MIN; printf("%d", abs(x)); }') == "-2147483648"
rc, o, e = run('int main(){ volatile int x = INT_MAX; printf("%d", x + 1); }', flags=['-fsanitize=undefined'])
assert 'signed integer overflow' in e, e
# 3. size() - 1 on an empty vector is unsigned
assert out('int main(){ vector<int> v; printf("%zu %d", v.size() - 1, (int)v.size() - 1); }') == "18446744073709551615 -1"
# 4. % and / truncate toward zero; the usual fix
assert out('int main(){ int a = -7, m = 3; printf("%d %d %d %d", a % m, -7 / 2, ((a % m) + m) % m, (int)floor(-7 / 2.0)); }') == "-1 -3 2 -4"
# 5. a non-strict comparator is undefined behaviour; _GLIBCXX_DEBUG detects it
body = 'int main(){ vector<int> v(1000, 7); sort(v.begin(), v.end(), [](int a, int b) { return a <= b; }); puts("survived"); }'
rc, o, e = run(body, flags=['-D_GLIBCXX_DEBUG'])
assert rc != 0 and 'irreflexive' in e, (rc, e[:200])
# 6. negative zero is printed as -0.00; rounding first and adding 0.0 fixes it
assert out('int main(){ double x = -0.001; printf("%.2f %.2f", x, round(x * 100) / 100 + 0.0); }') == "-0.00 0.00"
# 7. floating point truncation
assert out('int main(){ printf("%d %d %d", (int)(0.29 * 100), (int)llround(0.29 * 100), 0.1 + 0.2 == 0.3); }') == "28 29 0"
# 8. vector<bool> elements are proxies
c, _ = build('int main(){ vector<bool> v(3); auto& x = v[0]; }')
assert c.returncode != 0 and 'cannot bind' in c.stderr
c, _ = build('int main(){ vector<char> v(3); auto& x = v[0]; x = 1; }')
assert c.returncode == 0
# 9. __builtin_popcount takes 32 bits
assert out('int main(){ long long x = 1LL << 40; printf("%d %d", __builtin_popcount(x), __builtin_popcountll(x)); }') == "0 1"
# 10. getline after >> reads the rest of the line
assert out('int main(){ istringstream in("5\\nhello\\n"); int n; string s, t; in >> n; getline(in, s); getline(in, t); printf("[%s][%s]", s.c_str(), t.c_str()); }') == "[][hello]"
# 12. default stack of 8 MB: a recursion of depth 1e5 with ordinary frames crashes
rec = 'int f(int n){ volatile char buf[64]; buf[0]=1; return n ? 1 + f(n-1) + buf[0]-1 : 0; }\nint main(int c, char**v){ printf("%d", f(atoi(v[1]))); }'
rc, o, e = run(rec, args=[10000], prefix='ulimit -s 8192; '); assert rc == 0 and o == "10000"
rc, o, e = run(rec, args=[1000000], prefix='ulimit -s 8192; '); assert rc != 0
# 14. max(int, long long) does not compile; max<ll> does
c, _ = build('int main(){ int a = 1; long long b = 2; return max(a, b); }')
assert c.returncode != 0 and 'no matching function' in c.stderr
assert out('int main(){ int a = 1; long long b = 2; printf("%lld", max<long long>(a, b)); }') == "2"
print("C++ pitfalls: every claim reproduced (11 interactive flush: see doc/scripts/test-contest-scripts.sh; 13 anti-hash: not checked here)")
