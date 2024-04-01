import random

def rand_int_ary(n):
    ary = []
    for i in range(n):
        ary.append([])
        for ii in range(n):
            ary[-1].append(random.randint(-100,100))
    return ary
ary = rand_int_ary(10)
for r in ary:
    print(r)
