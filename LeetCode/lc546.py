def createArray(dims) :
	if len(dims) == 1:
		return [-1 for _ in range(dims[0])]
	return [createArray(dims[1:]) for _ in range(dims[0])]
	
def redoboxes(boxes):
	n = len(boxes)
	m = 1
	t = {}
	s = [0 for _ in range(n)]
	for x in boxes:
		if x in t:
			continue
		t[x] = m
		m += 1
	for i in range(n):
		s[i] = t[boxes[i]]
	return s, m

class Solution:
	def init(self):
		dp = self.dp
		n = self.n
		boxes = self.boxes
		for i in range(0, n):
			dp[i][i][0] = 1
			dp[i][i][1] = 0
			dp[i][i-1][0] = 0
	def solve(self):
		dp = self.dp
		n = self.n
		m = self.m
		boxes = self.boxes
		
		for k in range(1, n):
			for i in range(0, n):
				j = i + k
				if j >= n:
					break
				for l in range(i, j):
					if dp[i][l][0] + dp[l+1][j][0] > dp[i][j][0]:
						dp[i][j][0] = dp[i][l][0] + dp[l+1][j][0]
				if boxes[i] == boxes[j]:
					dp[i][j][2] = dp[i+1][j-1][0]
					dp[i][j][1] = max(dp[i+1][j][0], dp[i][j-1][0])
					for l in range(i+1, j):
						if boxes[l] != boxes[i]:
							continue
						if l < j - 1 and boxes[l] == boxes[l+1]:
							continue
						for p in range(0, l-i+2):
							if dp[i][l][p] == -1:
								continue
							dp[i][j][p] = max(dp[i][l][p] + dp[l+1][j][0], dp[i][j][p])
							dp[i][j][p+1] = max(dp[i][j][p+1], dp[i][l][p] + dp[l+1][j-1][0])
					for p in range(0, n+1):
						if dp[i][j][p] == -1:
							continue
						dp[i][j][0] = max(dp[i][j][0], dp[i][j][p] + p * p)
	def removeBoxes(self, boxes: List[int]) -> int:
		boxes, m = redoboxes(boxes)
		#print(boxes, m)
		self.boxes = boxes
		self.n = len(boxes)
		n = len(boxes)
		self.m = m
		self.dp = createArray([n+3,n+3,n+3])
		self.init()
		self.solve()
		#print(self.dp)
		return self.dp[0][self.n-1][0]
