import random

# class path:
#     def __init__(self, src, dest):
#         self.src = src
#         self.dest = dest
class graph:
    def __init__(self,amnt=0):
        self.vertices = []
        self.goal = -1
        self.start = -1
        self.size = 0
        if amnt != 0:
            self.fill_random(amnt)
            self.goal = amnt-1
            self.start = 0
    def __str__(self):
        output = "GRAPH\n"
        c = 0
        for vertices in self.vertices:
            output += "{} -> {}\n".format(c,str(vertices))
            c += 1
        return output
    def fill_random(self,amnt):
        for i in range(amnt):
            paths = []
            for i in range(random.randint(0,3)):
                paths.append(random.randint(0,amnt-1))
            self.vertices.append(paths)
        self.size = amnt
class accepted_edges:
    def __init__(self, graph):
        self.graph = graph
        self.to_explore = list(range(graph.size))
        self.to_explore.remove(graph.goal)
        self.accepting = [graph.goal]
        self.denying = []
        self.locked = []
    def find_accepting(self):
        while self.find_accepting_r() != None:
            pass
    def find_accepting_r(self,start=None):
        # print(self.to_explore)
        if start in self.denying or start in self.locked:
            return False
        elif start in self.accepting:
            return True
        if start == None:
            if len(self.to_explore) == 0:
                return
            start = self.to_explore[0]
        self.to_explore.remove(start)
        self.locked.append(start)
        for v in self.graph.vertices[start]:
            if self.find_accepting_r(start=v):
                self.locked.remove(start)
                self.accepting.append(start)
                return True
        self.locked.remove(start)
        self.denying.append(start)
        return False
        
G = graph(amnt=5)
print(G)
AE = accepted_edges(G)
AE.find_accepting()
print("ACCEPTING")
print(AE.accepting)
print("DENYING")
print(AE.denying)