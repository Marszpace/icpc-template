import os, re, sys
here = os.path.dirname(os.path.abspath(__file__))
exec(open(os.path.join(here, 'tech20.py')).read())
OUT = sys.argv[1]
os.makedirs(OUT, exist_ok=True)
names = {n for _, items in CATS for n, _, _ in items}
assert ESSENTIAL <= names, ESSENTIAL - names
lvl = {n: l for _, items in CATS for n, _, l in items}

def parse(path):
    out, head = [], None
    for line in open(path):
        if not line.strip(): continue
        if not line.startswith('\t'):
            head = line.strip(); out.append((head, None)); continue
        out.append((head, line.strip().lstrip('* ').strip()))
    return out

LEGEND = {'T': 'in the template', 'B': 'basic / trivial', 'N': 'niche', 'C': 'heading'}
def verdict(src, head, item):
    if item is None: return 'C', ''
    if src == 'K': v = KACTL.get(item)
    else: v = WIKI.get(item, WIKI_HEAD.get(head))
    if v is None: v = 'B'
    code, _, target = v.partition(':')
    if code in 'K?' and target:
        assert target in names, (src, item, target)
        code = 'keep' if (code == 'K' and lvl[target] == 'A') else 'maybe'
        return code, target
    return code, ''

w = []
w.append('# Item 20: techniques worksheet\n')
w.append('Rule (team, 2026-11-09): keep what is hard to see from the statement but clicks once someone names it; '
         'drop what is already in the template and what is trivial for us.\n')
w.append('Marks: **A** = keep, **B** = maybe (borderline trivial, or rare), **A*** = essential (the tightest list). Three levels: essential (A*), core (A), all (A and B); each as names only or with a hint (same number of lines).\n')
total = {'A': 0, 'B': 0}
w.append('## The proposed list\n')
for cat, items in CATS:
    w.append('### %s\n' % cat)
    w.append('| | Technique | Hint (printed in the hinted versions) |\n|---|---|---|')
    for n, h, l in items:
        total[l] += 1
        w.append('| %s | %s | %s |' % (l + ('*' if n in ESSENTIAL else ''), n, h))
    w.append('')
w.insert(3, 'Totals: %d A, %d B, in %d groups.\n' % (total['A'], total['B'], len(CATS)))

for src, path, title in (('K', os.path.join(here, '../../../content/appendix/techniques.txt'), 'Current techniques.txt (159 lines)'),
                         ('W', os.path.join(here, 'oiwiki-techniques.txt'), 'OI-wiki list (370 lines)')):
    rows = parse(path)
    cnt = {}
    body = []
    for head, item in rows:
        code, target = verdict(src, head, item)
        cnt[code] = cnt.get(code, 0) + 1
        if item is None: body.append('| **%s** | | |' % head); continue
        what = {'keep': 'kept', 'maybe': 'maybe'}.get(code, LEGEND.get(code, code))
        body.append('| %s | %s | %s |' % (item, what, ('as "%s"' % target) if target and target != item else ''))
    w.append('## %s, line by line\n' % title)
    w.append('Kept %d, maybe %d, in the template %d, trivial %d, niche %d (headings %d).\n' % (
        cnt.get('keep', 0), cnt.get('maybe', 0), cnt.get('T', 0), cnt.get('B', 0), cnt.get('N', 0), cnt.get('C', 0)))
    w.append('| Line | Verdict | |\n|---|---|---|')
    w += body
    w.append('')
open(OUT + '/techniques-worksheet.md', 'w').write('\n'.join(w))

def variant(levels, hints):
    lines = []
    for cat, items in CATS:
        its = [(n, h) for n, h, l in items if (l in levels if levels != 'S' else n in ESSENTIAL)]
        if not its: continue
        lines.append(cat)
        for n, h in its:
            s = '\t%s: %s' % (n, h) if hints else '\t%s' % n
            assert len(s.expandtabs(2)) <= 63, (s, len(s.expandtabs(2)))
            lines.append(s)
    return '\n'.join(lines) + '\n'
for name, levels, hints in (('essential-names', 'S', False), ('essential-hints', 'S', True), ('core-names', 'A', False), ('core-hints', 'A', True),
                            ('all-names', 'AB', False), ('all-hints', 'AB', True)):
    t = variant(levels, hints)
    open('%s/techniques-%s.txt' % (OUT, name), 'w').write(t)
    print(name, len(t.splitlines()), 'lines')
print(total)
