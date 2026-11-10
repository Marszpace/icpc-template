import csv, collections, sys
OUT = sys.argv[1]
ns = {}
exec(open(OUT + 'tools/tech20.py').read(), ns)
CATS, WILD, ESS = ns['CATS'], ns['WILD'], ns['ESSENTIAL']
AFTER = {'Advanced data structures': 'Data structures', 'Polynomials and algebra': 'Number theory'}
for cat, items in WILD:
    cs = [c for c, _ in CATS]
    if cat in cs: CATS[cs.index(cat)][1].extend(items)
    else: CATS.insert(cs.index(AFTER[cat]) + 1, (cat, list(items)))
def parse(path):
    out, head = [], None
    for line in open(path):
        if not line.strip(): continue
        if not line.startswith('\t'): head = line.strip(); continue
        out.append((head, line.strip().lstrip('* ').strip()))
    return out
cover = collections.defaultdict(lambda: ([], []))
dropped = collections.OrderedDict()
REASON = {'T': 'Out: in the template', 'B': 'Out: trivial / basic', 'out': 'Out: not an algorithm', 'N': 'Out: niche',
          'C': 'Out: sub-heading (its items are rows of their own)'}
srcs = (('K', 'content/appendix/techniques.txt'), ('W', OUT + 'tools/oiwiki-techniques.txt'))
for idx, (src, path) in enumerate(srcs):
    for head, item in parse(path):
        v = ns['KACTL'].get(item) if src == 'K' else ns['WIKI'].get(item, ns['WIKI_HEAD'].get(head))
        if v is None: v = 'B'
        code, _, t = v.partition(':')
        target = None
        if code in 'K?' and t: target = t
        elif code == 'N' and item in ns['WILD_MAP']: target = ns['WILD_MAP'][item]
        elif code == 'N' and item in ns['LEFT_OUT']: code = 'out'
        if target: cover[target][idx].append(item); continue
        r = dropped.setdefault(item, [head, REASON[code], False, False])
        r[2 + idx] = True
LV = {'A': 'Core', 'B': 'Maybe', 'C': 'Wild'}
rows = []
for cat, items in CATS:
    for n, h, l in items:
        k, wk = cover[n]
        src = 'current page + OI-wiki' if k and wk else 'current page' if k else 'OI-wiki' if wk else 'new'
        rows.append([cat, n, h, 'Essential' if n in ESS else LV[l], 'yes', src, '; '.join(k), '; '.join(wk)])
for item, (head, reason, ink, inw) in dropped.items():
    src = 'current page + OI-wiki' if ink and inw else 'current page' if ink else 'OI-wiki'
    rows.append([head, item, '', reason, 'no', src, '', ''])
with open(OUT + 'techniques/techniques.csv', 'w', newline='', encoding='utf-8') as fh:
    w = csv.writer(fh, quoting=csv.QUOTE_ALL)
    w.writerow(['Group', 'Technique', 'Hint', 'Level', 'In final copy', 'Source', 'Covers (current page)', 'Covers (OI-wiki list)'])
    w.writerows(rows)
print(len(rows), 'rows', dict(collections.Counter(r[3] for r in rows)))
nk = len(parse(srcs[0][1])); nw = len(parse(srcs[1][1]))
covered = sum(len(a) + len(b) for a, b in cover.values())
outlines = sum(int(v[2]) + int(v[3]) for v in dropped.values())
print('source lines', nk, '+', nw, '=', nk + nw, '| covered', covered, '+ out', outlines, '=', covered + outlines)
print('formula-like:', [r[1] for r in rows if any(x and x[0] in '=+-@' for x in r)])
