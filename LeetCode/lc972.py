def f(si, sn, sr):
    i = int(si)
    if len(sn) > 0:
        n = int(sn)
    else:
        n = 0
    if len(sr) > 0:
        r = int(sr)
        lr = len(sr)
    else:
        r = 0
        lr = 1
    a = (10 ** len(sn))
    b = (10 ** lr)
    c = a * b
    x = (i * c + n * b + r) - (i * a + n)
    y = (c - a)
    z = gcd(x, y)
    return x // z, y // z

def gcd(x, y):
    while x != 0:
        z = x
        x = y % x
        y = z
    return y

def solve(s):
    ss = s.split('.')
    si = ss[0]
    if len(ss) <= 1:
        return f(si, '', '')
    snr = ss[1]
    if snr == '':
        return f(si, '', '')
    snrs = snr.split('(')
    sn = snrs[0]
    if len(snrs) > 1:
        sr = snrs[1].split(')')[0]
    else:
        sr = ''
    return f(si, sn, sr)
    
    
class Solution(object):
    def isRationalEqual(self, S, T):
        sx, sy = solve(S)
        tx, ty = solve(T)
        if sx == tx and sy == ty:
            return True
        return False
