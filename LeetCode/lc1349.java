class MaxMatch {
    List<Integer>[] edges;
    int n, m;
    int[] visited, prev;
    public MaxMatch(int n, int m) {
        this.n = n;
        this.edges = new List[n]; 
        for(int i = 0; i < n; ++i) {
            this.edges[i] = new ArrayList<Integer>();
        }
        
        this.m = m;
        this.prev = new int[m];
        for(int i = 0; i < m; ++i) {
            prev[i] = -1; 
        }
    }
    public void addEdge(int v, int u) {
        edges[v].add(u);
    }
    private int dfs(int x) {
        for(int y : edges[x]) {
            if(visited[y] == 1) continue;
            visited[y] = 1;
            if(prev[y] == -1 || dfs(prev[y]) == 1) {
                prev[y] = x;
                return 1;
            }
        }
        return 0;
    }
    public int solve() {
        int ret = 0;
        for(int i = 0; i < n; ++i) {
            this.visited = new int[m];
            ret += dfs(i);
        }
        return ret;
    }
}

class Solution {
    public int maxStudents(char[][] seats) {
        int n = seats.length;
        int m = seats[0].length;
        MaxMatch mm = new MaxMatch(n * m, n * m);
        int[] dx = {0, 0, 1, -1, 1, -1};
        int[] dy = {1, -1, 1, -1, -1, 1};
        int total = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(seats[i][j] == '#') continue;
                total += 1;
                if(j % 2 != 0) continue;
                for(int k = 0; k < 6; ++k) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if(x < 0 || y < 0 || x >= n || y >= m) continue;
                    if(seats[x][y] == '.') {
                        mm.addEdge(i * m + j, x * m + y);
                    }
                }
            }
        }
        return total - mm.solve();
    }
}
