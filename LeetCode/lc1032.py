import queue 

class Node:
    def __init__(self, s=''):
        self.s = s
        self.end = False
        self.fail = None
        self.children = None
    def get(self, index):
        if self.children == None:
            return None
        return self.children[index]
    def set(self, index, node):
        if self.children == None:
            self.children = [None for _ in range(26)]
        self.children[index] = node
    def add(self, index):
        if self.children == None:
            self.children = [None for _ in range(26)]
        if self.children[index] == None: 
            self.children[index] = Node(self.s + chr(ord('a') + index))
        return self.children[index]
    def next(self, index):
        p = self
        while p.get(index) == None:
            #print("fail", p, p.fail)
            p = p.fail
        #print(p, p.get(index))
        return p.get(index)

def buildFail(root):
    q = queue.Queue()
    q.put(root)
    while not q.empty():
        node = q.get()
        #print("node", node.s)
        if node.children == None:
            continue
        for i in range(26):
            cnode = node.get(i)
            if cnode == None:
                continue
            #print("cnode:", cnode.s)
            if node == root:
                cnode.fail = root
            else:
                p = node.fail
                while p != None:
                    if p.get(i) == None:
                        p = p.fail
                    else:
                        break
                if p == None:
                    cnode.fail = root
                else:
                    cnode.fail = p.get(i)
            #print("cnode fail:", cnode.s, cnode.fail.s)
            if cnode.end == False and cnode.fail.end == True:
                cnode.end = True
            q.put(cnode)
    for i in range(26):
        if root.get(i) == None:
            root.set(i, root)
    root.fail = root
        
    
def c2i(c):
    return ord(c) - ord('a')

class StreamChecker:
    def __init__(self, words: List[str]):
        self.words = words
        root = Node()
        for i in range(len(words)):
            p = root
            for j in range(len(words[i])):
                p = p.add(c2i(words[i][j]))
            p.end = True
        #print(root)
        buildFail(root)
        self.cur = root
    def query(self, letter: str) -> bool:
        #print('cur', self.cur, letter)
        self.cur = self.cur.next(c2i(letter))
        #print("end", self.cur.end)
        return self.cur.end


# Your StreamChecker object will be instantiated and called as such:
# obj = StreamChecker(words)
# param_1 = obj.query(letter)
