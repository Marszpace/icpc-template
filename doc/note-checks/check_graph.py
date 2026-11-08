"""Checks the formulas of the Graph notes: matrix-tree (undirected / directed), BEST theorem, LGV lemma.
Run: python3 doc/note-checks/check_graph.py"""
import itertools, random
from fractions import Fraction
from math import factorial

def det(M):
    n = len(M); A = [[Fraction(x) for x in r] for r in M]; d = Fraction(1)
    for i in range(n):
        p = next((r for r in range(i, n) if A[r][i] != 0), None)
        if p is None: return 0
        if p != i: A[i], A[p] = A[p], A[i]; d = -d
        d *= A[i][i]
        for r in range(i + 1, n):
            f = A[r][i] / A[i][i]
            for c in range(i, n): A[r][c] -= f * A[i][c]
    return int(d)

def minor(M, r): return [[M[i][j] for j in range(len(M)) if j != r] for i in range(len(M)) if i != r]

def laplacian(n, edges, kind):  # kind: 'out' (D_out - A), 'in' (D_in - A), 'und'
    L = [[0] * n for _ in range(n)]
    for a, b in edges:
        if a == b: continue
        if kind == 'und':
            L[a][a] += 1; L[b][b] += 1; L[a][b] -= 1; L[b][a] -= 1
        elif kind == 'out': L[a][a] += 1; L[a][b] -= 1
        else: L[b][b] += 1; L[a][b] -= 1
    return L

def brute_trees(n, edges, root, direction):  # direction: 'und', 'toward' (edges point to root), 'away'
    cnt = 0
    for sub in itertools.combinations(range(len(edges)), n - 1):
        es = [edges[i] for i in sub]
        if any(a == b for a, b in es): continue
        if direction == 'und':
            par = list(range(n))
            def f(x):
                while par[x] != x: par[x] = par[par[x]]; x = par[x]
                return x
            ok = True
            for a, b in es:
                if f(a) == f(b): ok = False; break
                par[f(a)] = f(b)
            cnt += ok
        else:
            # toward: every non-root has exactly one outgoing tree edge, following it reaches root; away: reversed
            e2 = es if direction == 'toward' else [(b, a) for a, b in es]
            nxt = {}
            ok = True
            for a, b in e2:
                if a == root or a in nxt: ok = False; break
                nxt[a] = b
            if not ok: continue
            for v in range(n):
                seen = set(); x = v
                while x != root and x in nxt and x not in seen: seen.add(x); x = nxt[x]
                if x != root: ok = False; break
            cnt += ok
    return cnt

random.seed(1)
for it in range(300):
    n = random.randint(2, 5)
    m = random.randint(1, 9)
    edges = [(random.randrange(n), random.randrange(n)) for _ in range(m)]
    r = random.randrange(n)
    assert det(minor(laplacian(n, edges, 'und'), r)) == brute_trees(n, edges, r, 'und'), ('und', edges)
    assert det(minor(laplacian(n, edges, 'out'), r)) == brute_trees(n, edges, r, 'toward'), ('toward', edges)
    assert det(minor(laplacian(n, edges, 'in'), r)) == brute_trees(n, edges, r, 'away'), ('away', edges)
print("matrix-tree: undirected cofactor, D_out - A = trees toward r, D_in - A = trees away from r: ok")

# BEST theorem on random Eulerian multi-digraphs (union of random closed walks keeps in = out)
def euler_circuits_from_first_edge(n, edges):
    m = len(edges); used = [False] * m; used[0] = True
    start = edges[0][0]
    def go(v, k):
        if k == m: return 1 if v == start else 0
        t = 0
        for i in range(m):
            if not used[i] and edges[i][0] == v:
                used[i] = True; t += go(edges[i][1], k + 1); used[i] = False
        return t
    return go(edges[0][1], 1)
checked = 0
for it in range(400):
    n = random.randint(1, 4)
    edges = []
    for _ in range(random.randint(1, 3)):
        L = random.randint(1, 4); walk = [random.randrange(n)]
        for _ in range(L - 1): walk.append(random.randrange(n))
        edges += [(walk[i], walk[(i + 1) % L]) for i in range(L)]
    if len(edges) > 9: continue
    deg = [0] * n
    for a, b in edges: deg[a] += 1
    touched = {a for a, b in edges} | {b for a, b in edges}
    # connected on the touched vertices (weakly) is required
    par = {v: v for v in touched}
    def f(x):
        while par[x] != x: x = par[x]
        return x
    for a, b in edges: par[f(a)] = f(b)
    if len({f(v) for v in touched}) > 1: continue
    idx = sorted(touched); mp = {v: i for i, v in enumerate(idx)}
    e2 = [(mp[a], mp[b]) for a, b in edges]; k = len(idx)
    ec = euler_circuits_from_first_edge(k, e2)
    d2 = [0] * k
    for a, b in e2: d2[a] += 1
    pred = det(minor(laplacian(k, e2, 'out'), 0)) if k > 1 else 1
    for v in range(k): pred *= factorial(d2[v] - 1)
    assert ec == pred, ('BEST', e2, ec, pred)
    # circuits written as edge sequences starting at a given vertex s: ec * deg(s)
    s0 = random.randrange(k); m2 = len(e2)
    def from_vertex(s0):
        used = [False] * m2
        def go(v, c):
            if c == m2: return 1 if v == s0 else 0
            return sum(go2 for go2 in [0]) + sum((lambda i: (used.__setitem__(i, True), go(e2[i][1], c + 1), used.__setitem__(i, False))[1])(i) for i in range(m2) if not used[i] and e2[i][0] == v)
        return go(s0, 0)
    assert from_vertex(s0) == ec * d2[s0], ('start vertex', e2, s0)
    # in-degree Laplacian gives the same t_w for Eulerian graphs
    if k > 1: assert det(minor(laplacian(k, e2, 'in'), 0)) == det(minor(laplacian(k, e2, 'out'), 0))
    checked += 1
print("BEST theorem: ec(G) = t_r(G) * prod (deg v - 1)! (cyclic sequences; times deg(s) when starting at vertex s):", checked, "graphs ok")

# LGV on random small DAGs (vertices 0..n-1, edges i->j only for i<j)
def lgv_check():
    for it in range(300):
        n = random.randint(4, 8)
        w = {}
        for i in range(n):
            for j in range(i + 1, n):
                if random.random() < 0.5: w[(i, j)] = random.randint(1, 3)
        k = random.randint(1, 3)
        if 2 * k > n: continue
        verts = random.sample(range(n), 2 * k)
        src, snk = verts[:k], verts[k:]
        def paths(a):  # all paths from a as (vertex tuple, weight)
            out = []
            def dfs(v, pth, wt):
                out.append((tuple(pth), wt))
                for (x, y), c in w.items():
                    if x == v: dfs(y, pth + [y], wt * c)
            dfs(a, [a], 1)
            return out
        P = {a: paths(a) for a in src}
        M = [[sum(wt for pth, wt in P[a] if pth[-1] == b) for b in snk] for a in src]
        total = 0
        for perm in itertools.permutations(range(k)):
            sign = 1
            for i in range(k):
                for j in range(i + 1, k):
                    if perm[i] > perm[j]: sign = -sign
            # vertex-disjoint systems with source i -> sink perm[i]
            cand = [[(pth, wt) for pth, wt in P[src[i]] if pth[-1] == snk[perm[i]]] for i in range(k)]
            for combo in itertools.product(*cand):
                vs = [v for pth, _ in combo for v in pth]
                if len(vs) == len(set(vs)):
                    wt = 1
                    for _, x in combo: wt *= x
                    total += sign * wt
        assert det(M) == total, ('LGV', w, src, snk)
    print("LGV: det of the path matrix = signed sum over vertex-disjoint path systems: ok")
lgv_check()
