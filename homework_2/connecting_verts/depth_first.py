import random

class path:
    def __init__(self, src, dest):
        self.src = src
        self.dest = dest
class graph:
    def __init__(self,amnt=0):
        self.vertices = []
        self.goal = -1
        self.start = -1
        if amnt != 0:
            self.fill_random(amnt)
    def fill_random(self,amnt):
        for i in range(amnt):
            paths = []
            for i in range(random.randint(0,5)):
                paths.append(path(random.randint(0,amnt-1),random.randint(0,amnt-1)))
            self.vertices.append(paths)
        self.goal = random.randint(0,amnt-1)
        self.start = random.randint(0,amnt-1)
G = graph(amnt=20)