import random
import numpy as np
def rnd(n):
    return str(random.randint(1,pow(10,n)))

def find_shortest_subseq(a,b):
    ary = []
    for v in range(len(a)):
        ary.append([-1] * len(b))
    for i in range(len(a)):
        for ii in range(len(b)):
            if i == 0 or ii == 0:
                ary[i][ii] = 0
            elif a[i-1] == b[ii-1]:
                ary[i][ii] = ary[i-1][ii-1] + 1
            else:
                ary[i][ii] = max(ary[i-1][ii],ary[i][ii-1])
    for r in ary:
        print(r)
    return ary[-1][-1]
a = rnd(10)
b = rnd(10)
print(a)
print(b)
r = find_shortest_subseq(a,b)
print(r)