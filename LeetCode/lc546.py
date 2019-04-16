def createArray(dims) :
	if len(dims) == 1:
		return [-1 for _ in range(dims[0])]
	return [createArray(dims[1:]) for _ in range(dims[0])]
	
def redoboxes(boxes):
	n = len(boxes)
	s = [boxes[0]]
	t = [1]
	m = 1
	for i in range(1, n):
		if boxes[i] == boxes[i-1]:
			t[m-1] += 1
		else:
			s.append(boxes[i])
			t.append(1)
			m+=1
	return s, t, m

class Solution:
	def init(self):
		dp = self.dp
		n = self.n
		boxes = self.boxes
		nums = self.nums
		for i in range(0, n):
			dp[i][i][0] = nums[i]**2
			dp[i][i][nums[i]] = nums[i]**2
			dp[i][i-1][0] = 0
	def solve(self):
		dp = self.dp
		n = self.n
		m = self.m
		boxes = self.boxes
		nums = self.nums
		for k in range(1, n):
			for i in range(0, n):
				j = i + k
				if j >= n:
					break
				for l in range(i, j):
					if dp[i][l][0] + dp[l+1][j][0] > dp[i][j][0]:
						dp[i][j][0] = dp[i][l][0] + dp[l+1][j][0]
				if boxes[i] == boxes[j]:
					count = nums[i]+nums[j]
					dp[i][j][count] = dp[i+1][j-1][0] + count**2
					dp[i][j][0] = max(dp[i][j][0], dp[i][j][count])
					for l in range(i+1, j):
						if boxes[l] != boxes[i]:
							continue
						count += nums[l]
						if l < j-1 and boxes[l] == boxes[l+1]:
							continue
						for p in range(2, count+1):
							if dp[i][l][p] == -1:
								continue
							tmp = dp[i][l][p] + dp[l+1][j-1][0] + 2 * p * nums[j] + nums[j] * nums[j]
							if dp[i][j][p+nums[j]] < tmp:
								dp[i][j][p+nums[j]] = tmp
								dp[i][j][0] = max(dp[i][j][0], tmp)
	def removeBoxes(self, boxes: List[int]) -> int:
		m = len(boxes)
		boxes, nums, n = redoboxes(boxes)
		print(boxes, nums, n, m)
		self.boxes = boxes
		self.nums = nums
		self.n = len(boxes)
		self.m = m
		n = len(boxes)
		self.dp = createArray([n+3,n+3,m+3])
		self.init()
		self.solve()
		#print(self.dp)
		return self.dp[0][self.n-1][0]
		
# [3, 8, 8, 5, 5, 3, 9, 2, 4, 4, 6, 5, 8, 4, 8, 6, 9, 6, 2, 8, 6, 4, 1, 9, 5, 3, 10, 5, 3, 3, 9, 8, 8, 6, 5, 3, 7, 4, 9, 6, 3, 9, 4, 3, 5, 10, 7, 6, 10, 7]
# [1,1,1,1,1,1,1,1,1,1,2,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
