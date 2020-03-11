# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

def dfs(p):
    if p.left == None and p.right == None:
        if p.val > 0:
            return (True, p.val, p.val, p.val, p.val)
        else:
            return (True, p.val, p.val, p.val, 0)
    if p.left != None:
        lok, ls, ll, lr, lans = dfs(p.left)
    else:
        lok = True
        ls = 0
        ll = p.val
        lr = p.val - 1
        lans = 0
    if p.right != None:
        rok, rs, rl, rr, rans = dfs(p.right)
    else:
        rok = True
        rs = 0
        rl = p.val + 1
        rr = p.val
        rans = 0
    if lok and rok and lr < p.val and p.val < rl:
        ret =  (True, ls + p.val + rs, ll, rr, max(lans, rans, ls + p.val + rs))
    else:
        ret = (False, None, None, None, max(lans, rans))
    #print(p.val, ret)
    return ret
    
class Solution:
    def maxSumBST(self, root: TreeNode) -> int:
        ans = dfs(root)[4]
        # if ans < 0:
        #     ans = 0
        return ans
        
