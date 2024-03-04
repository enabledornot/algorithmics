import random
def rand():
    return random.randomint(0,1000)

class bst:
    def __init__(self):
        self.base = None
    def insert(self, data):
        current = self.base
        while current != None:
            if current.data < data:
                current = current.right
            else:
                current = current.left
        new = bst_node(data)
        if data <= current.data:
            current.left = new
        else:
            current.right = new
    def delete(self,data):
        current = self.base
        while current != None and current.data != data:
            if current.data < data:
                history.push(current.right)
            else:
                history.push(current.left)

        if current == None:
            return None
        else:
            if current.left = None:
                if history[-2].left = current:
                    history[-2].left = current.right
                else:
                    history[-2].right = history[-2].right
            elif current.right = None:
                if history[-2].left = current:
                    history[-2].left = current.left
                else:
                    history[-2].right = current.left
            else:

            return current.data
    def getMin(node,element):


    

class bst_node:
    def __init__(self, new_element):
        self.right = None
        self.left = None
        self.data = new_element

            


if __name__ == "__main__":
    tree = bst()
    for i in range(100):
        tree.insert()