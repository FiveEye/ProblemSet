import Queue
 
q = Queue.Queue()
 
s = set()

def initS(blocked):
    global s
    s = set()
    for b in blocked:
            s.add((b[0],b[1]))
        
def bfs(src, t):
    global s
    q = Queue.Queue()
    v = set()
    
    q.put(src)
    v.add(src)
    cnt = 1
    
    while not q.empty():
        x,y = q.get()
        #print(x,y)
        for dx, dy in [(0,1),(0,-1),(1,0),(-1,0)]:
            nx, ny = x+dx, y+dy
            if nx == t[0] and ny == t[1]:
                return 2
            if nx < 0 or nx > 1000000 or ny < 0 or ny > 1000000:
                continue
            nxy = (nx, ny)
            if nxy in v or nxy in s:
                continue
            q.put(nxy)
            v.add(nxy)
            cnt += 1
            if cnt > 4000:
                return 1
    return 0
        
class Solution(object):
    def isEscapePossible(self, blocked, source, target):
        """
        :type blocked: List[List[int]]
        :type source: List[int]
        :type target: List[int]
        :rtype: bool
        """
        initS(blocked)
        ans = bfs((source[0],source[1]), (target[0],target[1]))
        if ans == 0:
            return False
        if ans == 2:
            return True
        ans = bfs((target[0],target[1]), (source[0],source[1]))
        if ans == 0:
            return False
        return True
        
