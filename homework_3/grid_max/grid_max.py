import random

def rand_int_ary(n):
    ary = []
    for i in range(n):
        ary.append([])
        for ii in range(n):
            ary[-1].append(random.randint(-100,100))
    return ary
def make_empty(n):
    ary = []
    for i in range(n):
        ary.append([0]*n)
    return ary
def divide_up(ary):
    n = len(ary)
    mask = make_empty(n)
    current = 1
    current_corro = [0]
    for i in range(n):
        for j in range(n):
            if ary[i][j] >= 0:
                if mask[i][j] == 0:
                    current_corro.append(explore(i,j,n,current,ary,mask))
                    current+=1
    return mask,current_corro
def explore(i,j,n,current,ary,mask):
    sum = 0
    if i < 0 or j < 0 or i == n or j == n or mask[i][j] != 0:
        return sum
    if ary[i][j] >= 0:
        mask[i][j] = current
        sum += ary[i][j]
        for d in [[0,-1],[0,1],[-1,0],[1,0]]:
            sum += explore(i+d[0],j+d[1],n,current,ary,mask)
    return sum
def print_ary(a):
    for r in a:
        print(r)
    print("")
iary = rand_int_ary(5)
print_ary(iary)
mary, cc = divide_up(iary)
print_ary(mary)
print(cc)