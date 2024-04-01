import random
import ipdb
# helper
def rand_int_ary(n):
    ary = []
    for i in range(n):
        ary.append([])
        for ii in range(n):
            ary[-1].append(random.randint(-100,100))
    return ary
def make_empty(n,default=0):
    ary = []
    for i in range(n):
        ary.append([default]*n)
    return ary
def print_ary(a):
    for r in a:
        for e in r:
            print(e,end="")
            for v in range(5-len(str(e))):
                print(" ",end="")
        print("")
    print("")
# first stage
def divide_up(ary):
    n = len(ary)
    mask = make_empty(n)
    current = 1
    current_corro = [0]
    for i in range(n):
        for j in range(n):
            if mask[i][j] == 0:
                r = explore(i,j,n,current,ary,mask)
                if r != 0:
                    current_corro.append(r)
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
    else:
        mask[i][j] = ary[i][j]
    return sum
# second stage
def find_distances(mask,weights):
    minimum_distances = []
    for i in range(1,len(weights)-1):
        minimum_distances.append(dijkstra_multi(mask,i,len(weights)))
        break
    return minimum_distances
def dijkstra_multi(mask,bound,n_chunks):
    min_dists = [-1]*n_chunks
    n = len(mask)
    weights = make_empty(n,default=-2)
    to_explore = []
    starting = []
    for i in range(n):
        for j in range(n):
            if mask[i][j] == bound:
                weights[i][j] = 0
                to_explore.append((i,j))
            if mask[i][j] > bound or mask[i][j] < 0:
                weights[i][j] = -1
                to_explore.append((i,j))
    # while len(to_explore) != 0:
    while (c := find_min_and_remove(to_explore,weights)) is not None:
        # c = find_min_and_remove(to_explore,weights)
        # ipdb.set_trace()
        for d in [[0,1],[0,-1],[1,0],[-1,0]]:
            p = (c[0]+d[0],c[1]+d[1])
            if p[0] < 0 or p[1] < 0 or p[0] == n or p[1] == n or weights[p[0]][p[1]] == -2 or weights[p[0]][p[1]] == 0:
                continue
            if mask[p[0]][p[1]] > 0:
                pdist = weights[c[0]][c[1]]
                if pdist < min_dists[mask[p[0]][p[1]]] or min_dists[mask[p[0]][p[1]]]==-1:
                    min_dists[mask[p[0]][p[1]]] = pdist
            else:
                pdist = weights[c[0]][c[1]] + (-1*mask[p[0]][p[1]])
                if pdist < weights[p[0]][p[1]] or weights[p[0]][p[1]] == -1:
                    weights[p[0]][p[1]] = pdist
    print_ary(weights)
    return min_dists
def find_min_and_remove(to_explore,mask):
    min = 1000000000000
    min_i = -1
    for e in range(len(to_explore)):
        p_e = to_explore[e]
        p_min = mask[p_e[0]][p_e[1]]
        if p_min == -1:
            continue
        if min > p_min:
            min_i = e
            min = p_min
    if min == 1000000000000:
        return None
    return to_explore.pop(min_i)
    
iary = rand_int_ary(4)
# iary = [[-13, 97, -13, -89], [97, -69, 56, 86], [-75, 14, 21, -45], [-85, 67, -3, -78]]
print(iary)
print_ary(iary)
mary, cc = divide_up(iary)
print_ary(mary)
print(cc)

rslt = find_distances(mary,cc)
print(rslt)