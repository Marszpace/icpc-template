import re, os, sys
here = os.path.dirname(os.path.abspath(__file__))
exec(open(os.path.join(here, 'desc21.py')).read())
ROOT = '/home/user/icpc-template/content/'
ORDER = ['G', 'L', 'M']

def pick(d, lv):
    v = None; found = False
    for l in ORDER[:ORDER.index(lv) + 1]:
        if l in d: v = d[l]; found = True
    if not found: raise KeyError
    return v

def cur(f, field):
    s = open(ROOT + f).read()
    m = re.search(r'/\*\*(.*?)\*/', s, re.S)
    out = None
    for line in m.group(1).split('\n'):
        l = re.sub(r'^\s*\*\s?', '', line) if re.match(r'^\s*\*', line) else line
        mm = re.match(r'(Author|Date|License|Source|Description|Usage|Time|Status|Memory|Details):(.*)$', l)
        if mm:
            if out is not None: break
            if mm.group(1) == field: out = [mm.group(2).strip()]
        elif out is not None: out.append(l.strip())
    if out is None: return None
    t = ' '.join(x for x in out if x)
    t = re.sub(r'\\\\|\\begin\{minipage\}\{\d+mm\}|\\end\{minipage\}|\\vspace\{[^}]*\}|\\includegraphics\[[^]]*\]\{[^}]*\}', ' ', t)
    return re.sub(r'\s+', ' ', t).strip()

def one(t): return re.sub(r'\s+', ' ', t).strip() if t else '*(none)*'

o = []
o.append('# Item 21: description proposals (three levels)\n')
o.append('Raw LaTeX as it goes into the headers. **G** = gentle (readable, a few words of what it does), '
         '**L** = lean (only what you need to use it; the team rule), **M** = minimal. "= G" means the same as the level before. '
         'Code-comment moves (L and M) add a trailing comment to an existing code line, so no line is added and the hash does not change.\n')
chapter = None
for f, d in D.items():
    ch = f.split('/')[0]
    if ch != chapter:
        chapter = ch; o.append('\n## %s\n' % ch)
    o.append('### `%s`\n' % f.split('/')[1])
    o.append('- **Now:** %s' % one(cur(f, 'Description')))
    prev = None
    for lv in ORDER:
        v = pick(d, lv)
        if lv == 'M' and 'FOLDM' in d: v = (v + ' ' + d['FOLDM']).strip()
        txt = one(v)
        if prev is not None and txt == prev: o.append('- **%s:** = %s' % (lv, ORDER[ORDER.index(lv) - 1]))
        else: o.append('- **%s:** %s' % (lv, txt))
        prev = txt
    for key, name in (('U', 'Usage'), ('T', 'Time')):
        if key in d:
            c = cur(f, name)
            for lv in ORDER:
                if lv in d[key]:
                    v = d[key][lv]
                    o.append('- %s (%s and later): %s → %s' % (name, lv, '`' + one(c) + '`' if c else '*(none)*',
                             ('`' + one(v) + '`') if v else '*(dropped)*'))
    for old, new in d.get('C', []):
        o.append('- Code comment (L, M): `%s` → `%s`' % (old.replace('\t', '  ').strip(), new.replace('\t', '  ').strip()))
    if f in FOLD:
        o.append('- M: this file is no longer printed; its note moves into `%s`.' % FOLD[f].split('/')[1])
    o.append('')
open(sys.argv[1], 'w').write('\n'.join(o))
print('written', len(D))
