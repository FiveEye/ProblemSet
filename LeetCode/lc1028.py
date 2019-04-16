# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

import re

class Solution:
    def helper(self, vs, ds, i, cur):
        if i >= len(vs):
            return i, None
        #print(i, vs[i], ds[i], cur)
        if ds[i] != cur:
            return i, None
        tn = TreeNode(vs[i])
        i += 1
        i, tn.left = self.helper(vs, ds, i, cur+1)
        if i < len(vs):
            i, tn.right = self.helper(vs, ds, i, cur+1)
        return i, tn
    def recoverFromPreorder(self, S: str) -> TreeNode:
        vals = []
        dep = [0]
        for s in S.split('-'):
            if s != '':
                vals.append(int(s))
        #print(vals)
        for s in re.split('[0123456789]+', S):
            if s != '':
                dep.append(len(s))
        #print(dep)
        _, tn = self.helper(vals, dep, 0, 0)
        return tn
