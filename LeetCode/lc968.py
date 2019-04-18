# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

# need parent, no need parent, has camera itself.

def dfs(root):
    if root == None:
        return [0, 0, -1]
    l = dfs(root.left)
    r = dfs(root.right)
    s2 = 1 + l[0] + r[0]
    s0 = min(l[1] + r[1], s2)
    s1 = min(s0 + 1, s2)
    if l[2] != -1:
        s1 = min(s1, l[2] + r[1])
    if r[2] != -1:
        s1 = min(s1, l[1] + r[2])
    #print(root.val, [s0, s1, s2])
    return [s0, s1, s2]
class Solution(object):
    def minCameraCover(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        s = dfs(root)
        return min(s[1], s[2])
        
