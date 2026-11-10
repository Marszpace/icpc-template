# Writes descriptions-21.csv: the printed files (Section, File, G, L, M, code comments),
# then a blank row and the files that are not printed, with their current description.
import csv, re, os, glob, sys
OUT = sys.argv[1] if len(sys.argv) > 1 else 'doc/overnight-2026-11-10/'
ns = {}
exec(open(OUT + 'tools/desc21.py').read(), ns)
exec(open(OUT + 'tools/hyb21.py').read(), ns)
H = ns['H']
D, FOLD = ns['D'], ns['FOLD']
title = {}
for p in glob.glob('content/*/chapter.tex'):
    m = re.search(r'\\chapter\{([^}]*)\}', open(p).read())
    if m: title[p.split('/')[1]] = m.group(1)
ORDER = ['G', 'L', 'M']
def pick(d, lv):
    v = None
    for l in ORDER[:ORDER.index(lv) + 1]:
        if l in d: v = d[l]
    return v
def flat(t): return re.sub(r'\s+', ' ', t).strip() if t else '(none)'
def current(path):
    s = open(path, errors='replace').read()
    m = re.search(r'/\*\*(.*?)\*/', s, re.S)
    if not m: return '(no description)'
    out = None
    for line in m.group(1).split('\n'):
        l = re.sub(r'^\s*\*\s?', '', line) if re.match(r'^\s*\*', line) else line
        mm = re.match(r'(Author|Date|License|Source|Description|Usage|Time|Status|Memory|Details):(.*)$', l)
        if mm:
            if out is not None: break
            if mm.group(1) == 'Description': out = [mm.group(2).strip()]
        elif out is not None: out.append(l.strip())
    if not out: return '(no description)'
    t = ' '.join(x for x in out if x)
    t = re.sub(r'\\\\|\\begin\{minipage\}\{\d+mm\}|\\end\{minipage\}|\\vspace\{[^}]*\}|\\includegraphics\[[^]]*\]\{[^}]*\}', ' ', t)
    return re.sub(r'\s+', ' ', t).strip() or '(no description)'
printed = set()
for p in glob.glob('content/*/chapter.tex'):
    d = p.split('/')[1]
    for line in open(p):
        if line.lstrip().startswith('%'): continue
        for m in re.finditer(r'\\kactlimport(?:\[[^]]*\])?\{([^}]*)\}', line): printed.add('%s/%s' % (d, m.group(1)))
others = sorted(f[len('content/'):] for f in glob.glob('content/*/*') + glob.glob('content/*/.*')
                if os.path.isfile(f) and '/tex/' not in f and not f.endswith(('chapter.tex', '.pdf', '.png', '.svg', '.tex', '.md'))
                and f[len('content/'):] not in printed)
others += sorted(f for f in FOLD)  # printed today, not printed in M
with open(OUT + 'descriptions-21.csv', 'w', newline='', encoding='utf-8') as fh:
    w = csv.writer(fh, quoting=csv.QUOTE_ALL)
    w.writerow(['Section', 'File', 'G (gentle)', 'L (lean)', 'M (minimal)', 'Code comments added in L and M',
                'H (hybrid: G + code comments)', 'Code comments added in H'])
    for f, d in D.items():
        ch, name = f.split('/')
        g, l, m = (pick(d, x) for x in ORDER)
        if 'FOLDM' in d: m = ((m or '') + ' ' + d['FOLDM']).strip()
        mcell = '(not printed: folded into %s)' % FOLD[f].split('/')[1] if f in FOLD else flat(m)
        com = ' | '.join(new.strip().replace('\t', '') for old, new in d.get('C', []))
        h = H.get(f)
        hdesc = flat(h['desc']) if h else flat(g)
        hcom = ' | '.join('%s // %s' % (pat, c) for pat, c in h.get('C', [])) if h else ''
        w.writerow([title[ch], name, flat(g), flat(l), mcell, com, hdesc, hcom])
    w.writerow([])
    w.writerow(['Section', 'File', 'Current description (file is in the repository but not printed in the book)'])
    n = 0
    for f in others:
        if f in FOLD: continue
        ch, name = f.split('/')
        w.writerow([title.get(ch, ch), name, current('content/' + f)])
        n += 1
print(len(D), 'printed,', n, 'not printed')
