import random
# import ipdb
from tqdm import tqdm
import numpy as np
import functools
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
    minimum_distances = [[-1]*len(weights)]
    for i in range(1,len(weights)-1):
        minimum_distances.append(dijkstra_multi(mask,i,len(weights)))
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
    while (c := find_min_and_remove(to_explore,weights)) is not None:
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
    # print_ary(weights)
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
# 3rd stage
class cache:
    def __init__(self,n):
        self.n = n
        self.c = self.get_none()
        self.hitcount = 0
        self.lookcount = 0
    def get_none(self):
        return [None]*self.n
    def lookup(self, k, method, arg):
        self.lookcount += 1
        # print(method(arg))
        k = sorted(list(k))
        current = self.c
        for p in k:
            if current[p] == None:
                current[p] = self.get_none()
            current = current[p]
        if current[0] == None:
            current[0] = method(arg)
        else:
            self.hitcount += 1
        return current[0]
    def hash(k):
        return str(k)
    def size(c):
        count = 0
        for i in c:
            if type(i) == list:
                count += cache.size(i)
            elif i != None:
                count += 1
        return count
    def len(self):
        return cache.size(self.c)
class most_efficient_path:
    def __init__(self, node_weights, edge_weights):
        self.edge = edge_weights
        self.node = node_weights
        self.n = len(node_weights)
        self.cache = cache(self.n)
    def price_between(self, node_a, node_b):
        if node_a == node_b:
            return 0
        if node_a < node_b:
            node_t = node_a
            node_a = node_b
            node_b = node_t
        res = self.edge[node_b][node_a]
        if res == -1:
            return None
        return res
    def most_efficient_start(self):
        possible = [0]
        new_array = tuple([False]*self.n)
        for n in tqdm(range(1,self.n)):
            nau = most_efficient_path.update_tuple(new_array,n)
            potential = self.most_efficient_path(nau)
            if potential != None:
                possible.append(potential + self.node[n])
        return max(possible)
    def most_efficient_c(self, prev):
        return self.cache.lookup(prev, self.most_efficient, prev)
    def most_efficient(self, prev):
        possible = [0]
        for s in range(1,self.n):
            for e in range(1,self.n):
                if s in prev and e not in prev:
                    if (price := self.price_between(s, e)) and (potential := self.most_efficient_c(prev | {e}))==0:
                        possible.append(potential + self.node[e] - price)
        return max(possible)
    @functools.cache
    def most_efficient_path(self, prev):
        possible = [0]
        for s in range(1,self.n):
            for e in range(1,self.n):
                if prev[s] and not prev[e] and (price := self.price_between(s, e)) and (potential := self.most_efficient_path(most_efficient_path.update_tuple(prev,e)))==0:
                    possible.append(potential + self.node[e] - price)
        return max(possible)
    def update_tuple(tup, i):
        n = list(tup)
        n[i] = True
        return tuple(n)
iary = rand_int_ary(20)
# iary = [[-18, 73, 10, -8], [76, 67, 25, 11], [-42, -30, -56, -5], [83, -86, 1, -19]]
# iary = [[22, -60, -50, 18, 26, -62, 61, 72, -33, -91, -42, 100], [-13, 24, 73, 93, -80, -95, -46, 12, 84, -14, 85, -56], [27, 73, -53, -7, -84, 80, 42, 80, -91, -28, -50, 92], [-60, -81, -21, 15, -4, 2, -100, -84, -12, -7, -83, 1], [-69, 85, 41, -71, -85, -93, 28, 90, 84, -91, -54, -50], [27, 66, 44, 8, -66, -81, -13, -75, 96, -97, 79, -69], [-50, -62, 70, 25, -98, 17, 96, -46, -1, 69, -25, 52], [-85, 91, -86, 87, 40, -98, -37, 95, 85, -69, -86, 23], [-64, -27, -99, -38, 2, 15, -48, -77, 6, 51, -69, -65], [95, 4, 59, 6, 1, -67, -51, 38, 2, -33, -14, -5], [45, 91, 11, 13, -45, -31, 6, -3, 47, 76, 59, 75], [-4, -22, 70, -75, -55, -54, 24, -50, -56, 40, -99, -29]]
print(iary)
print_ary(iary)
map_array, node_weights = divide_up(iary)
print_ary(map_array)
print(node_weights)

edge_weights = find_distances(map_array,node_weights)
print_ary(edge_weights)

mfp = most_efficient_path(node_weights,edge_weights)
result = mfp.most_efficient_start()
print(mfp.cache.len())
print(result)
# print(mfp.cache.hitcount)
# print(mfp.cache.lookcount)