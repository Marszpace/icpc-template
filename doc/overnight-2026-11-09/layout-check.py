#!/usr/bin/env python3
"""Layout checks for kactl.pdf (3 columns, A4 landscape).

usage: python3 layout-check.py [kactl.pdf]

Prints
  - words whose boxes overlap (text drawn on top of other text),
  - page headers that run into "NTU" or the page number,
  - file titles left alone at the bottom of a column (orphans),
  - empty space at the bottom of each column above 15pt.
Needs pdftotext (poppler-utils). Big operators, accents and the labels
inside the geometry figures can give a few false positives.
"""
import collections, html, re, subprocess, sys

pdf = sys.argv[1] if len(sys.argv) > 1 else 'kactl.pdf'
t = subprocess.run(['pdftotext', '-bbox-layout', pdf, '-'], capture_output=True, text=True).stdout
pages = t.split('<page ')[1:]
W = float(re.search(r'width="([\d.]+)"', pages[0]).group(1))
starts = [13, 287, 562]  # left edges of the 3 columns
col = lambda x: max(i for i in range(3) if x >= starts[i] - 6)
LINE = r'<line xMin="([\d.]+)" yMin="([\d.]+)" xMax="([\d.]+)" yMax="([\d.]+)">(.*?)</line>'
WORD = r'<word xMin="([\d.]+)" yMin="([\d.]+)" xMax="([\d.]+)" yMax="([\d.]+)">(.*?)</word>'

print('== overlapping words')
for pi, pg in enumerate(pages, 1):
    ws = sorted((float(a), float(b), float(c), float(d), html.unescape(w)) for a, b, c, d, w in re.findall(WORD, pg))
    for i, a in enumerate(ws):
        for b in ws[i + 1:]:
            if b[0] >= a[2]:
                break
            hx = min(a[2], b[2]) - max(a[0], b[0]); hy = min(a[3], b[3]) - max(a[1], b[1])
            if hx <= 0 or hy <= 0:
                continue
            small = lambda w: len(w) <= 1 or any(c in w for c in '√∑∏∫')
            if hy > .35 * min(a[3] - a[1], b[3] - b[1]) and hx > .35 * min(a[2] - a[0], b[2] - b[0]) and not small(a[4]) and not small(b[4]):
                print(f'  page {pi}: {a[4][:30]!r} / {b[4][:30]!r}')

print('== lines closer than their text height (sub/superscripts can trigger this)')
for pi, pg in enumerate(pages, 1):
    C = collections.defaultdict(list)
    for m in re.finditer(LINE, pg, re.S):
        x0, y0, x1, y1 = map(float, m.groups()[:4])
        ws = re.findall(WORD, m.group(5))
        if y0 < 20 or not ws:
            continue
        tops = sorted(float(w[1]) for w in ws); bots = sorted(float(w[3]) for w in ws)
        C[col(x0)].append((tops[len(tops) // 2], bots[len(bots) // 2], x0, x1, html.unescape(' '.join(w[4] for w in ws))))
    for c, ls in C.items():
        ls.sort()
        for i, a in enumerate(ls):
            for b in ls[i + 1:]:
                if b[0] > a[1]:
                    break
                if a[1] - b[0] > 1.0 and min(a[3], b[3]) - max(a[2], b[2]) > 15 and len(a[4]) > 3 and len(b[4]) > 3:
                    print(f'  page {pi} col {c + 1}: {a[4][:30]!r} / {b[4][:30]!r} ({a[1] - b[0]:.1f}pt)')

print('== page headers')
for pi, pg in enumerate(pages, 1):
    ws = sorted((float(a), float(c), html.unescape(w)) for a, b, c, d, w in re.findall(WORD, pg) if float(b) < 18)
    names = [w for w in ws if w[2] != 'NTU' and not w[2].isdigit()]
    if not names:
        continue
    left = max([w[1] for w in ws if w[2] == 'NTU'] or [0]); right = min([w[0] for w in ws if w[2].isdigit()] or [W])
    if names[0][0] - left < 3 or right - names[-1][1] < 3:
        print(f'  page {pi}: header too wide ({names[-1][1] - names[0][0]:.0f}pt)')

print('== orphan titles and free space at column bottoms (>15pt)')
for pi, pg in enumerate(pages, 1):
    H = float(re.search(r'height="([\d.]+)"', pg).group(1))
    C = collections.defaultdict(list)
    for m in re.finditer(LINE, pg, re.S):
        x0, y0, x1, y1 = map(float, m.groups()[:4])
        if y0 < 20:
            continue
        C[col(x0)].append((y1, html.unescape(' '.join(re.findall(r'<word[^>]*>(.*?)</word>', m.group(5))))))
    for c in sorted(C):
        y, last = max(C[c])
        free = H - 12 - y
        orphan = re.search(r'\.(h|cpp|sh|py|txt|java)$', last) or re.match(r'^\d+(\.\d+)+$', last)
        if orphan or free > 15:
            print(f'  page {pi} col {c + 1}: {free:.0f}pt free, last line {last[:40]!r}' + ('  <-- ORPHAN' if orphan else ''))
