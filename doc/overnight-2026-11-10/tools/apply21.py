# usage: python3 apply21.py LEVEL   (cwd = a repo copy with content/); LEVEL in G, L, M
import re, sys, os
here = os.path.dirname(os.path.abspath(__file__))
exec(open(os.path.join(here, 'desc21.py')).read())
LV = sys.argv[1]
ORDER = ['G', 'L', 'M']

def pick(d, lv):
    """value for level lv with inheritance G -> L -> M; KeyError if never given"""
    v = None; found = False
    for l in ORDER[:ORDER.index(lv) + 1]:
        if l in d: v = d[l]; found = True
    if not found: raise KeyError
    return v

FIELDS = r'(Author|Date|License|Source|Description|Usage|Time|Status|Memory|Details)'

def parse_block(text):
    """list of [field, lines] where lines are the raw continuation lines (without ' * ')"""
    out = []
    for line in text.split('\n'):
        l = re.sub(r'^\s*\*\s?', '', line) if re.match(r'^\s*\*', line) else line
        m = re.match(FIELDS + r':(.*)$', l)
        if m: out.append([m.group(1), [m.group(2).strip()]])
        elif out: out[-1][1].append(l.rstrip())
    return out

def render(fields):
    res = []
    for name, lines in fields:
        lines = list(lines)
        while lines and not lines[-1].strip(): lines.pop()
        first = lines[0] if lines else ''
        res.append((' * %s: %s' % (name, first)).rstrip())
        for l in lines[1:]: res.append((' * ' + l).rstrip())
    return '\n'.join(res)

def fig_part(desc_lines):
    s = '\n'.join(desc_lines)
    m = re.search(r'\\end\{minipage\}\s*(\\begin\{minipage\}\{15mm\}.*?\\end\{minipage\})', s, re.S)
    return m.group(1) if m else None

changed = 0
for f, d in D.items():
    p = 'content/' + f
    s = open(p).read()
    m = re.search(r'/\*\*(.*?)\*/', s, re.S)
    fields = parse_block(m.group(1))
    names = [x[0] for x in fields]
    desc = pick(d, LV)
    if LV == 'M' and 'FOLDM' in d:
        desc = (desc + ' ' + d['FOLDM']).strip()
    i = names.index('Description')
    fig = fig_part(fields[i][1])
    if fig and desc:
        newd = ['\\\\', '\\begin{minipage}{75mm}'] + desc.split('\n') + ['\\end{minipage}'] + fig.split('\n')
    elif fig:  # empty text: keep only the figure
        newd = ['\\\\', '\\begin{minipage}{75mm}', '\\end{minipage}'] + fig.split('\n')
    else:
        newd = desc.split('\n') if desc else ['']
    fields[i][1] = newd
    for key, fname in (('U', 'Usage'), ('T', 'Time')):
        if key in d:
            try: v = pick(d[key], LV)
            except KeyError: continue
            if fname in names:
                j = [x[0] for x in fields].index(fname)
                if v == '': fields.pop(j)
                else: fields[j][1] = v.split('\n')
            elif v:
                j = [x[0] for x in fields].index('Description') + 1
                fields.insert(j, [fname, v.split('\n')])
    block = '/**\n' + render(fields) + '\n */'
    s = s[:m.start()] + block + s[m.end():]
    if LV in ('L', 'M'):
        for old, new in d.get('C', []):
            assert s.count(old + '\n') == 1, (f, old)
            assert len(new.expandtabs(2)) <= 63, (f, new, len(new.expandtabs(2)))
            s = s.replace(old + '\n', new + '\n')
    open(p, 'w').write(s)
    changed += 1

if LV == 'M':
    for f in FOLD:
        ch, name = f.split('/')
        p = 'content/%s/chapter.tex' % ch
        s = open(p).read()
        old = '\\kactlimport{%s}' % name
        assert s.count(old) == 1, f
        s = s.replace('\t' + old, '\t% ' + old + ' % folded into ' + FOLD[f].split('/')[1])
        if old in s and '% ' + old not in s: s = s.replace(old, '% ' + old)
        open(p, 'w').write(s)
print('level', LV, 'files', changed)

# header font: scale with the length so long page headers always fit (10pt up to 120 chars)
p = 'content/tex/preprocessor.py'
s = open(p).read()
old = """    font_size = 10
    if header_length > 120:
        font_size = 8
    if header_length > 150:
        font_size = 7
"""
new = """    font_size = max(5, min(10, 1200 // max(header_length, 1)))
"""
if old in s:
    open(p, 'w').write(s.replace(old, new))
