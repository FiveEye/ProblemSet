class Solution {
    int[] in;
    int[] bc;
    int find(int i) {
        if(bc[i] == -1) return i;
        return bc[i] = find(bc[i]);
    }
    void uni(int i, int j) {
        i = find(i);
        j = find(j);
        if(i != j) bc[i] = j;
    }
    public int[] findRedundantDirectedConnection(int[][] edges) {
        int n = edges.length;
        in = new int[n];
        bc = new int[n];
        for(int i = 0; i < n; ++i) {
            in[i] = -1;
            bc[i] = -1;
        }
        int c = -1;
        int d = -1;
        for(int i = 0; i < n; ++i) {
            int x = edges[i][0] - 1;
            int y = edges[i][1] - 1;
            if(in[y] == -1) {
                in[y] = x;
                if(find(y) != find(x)) {
                    uni(y, x);
                } else {
                    c = i;
                }
            } else {
                d = i;
            }
            
        }
        if(d == -1) {
            return new int[]{edges[c][0], edges[c][1]};
        }
        int t = 0;
        for(int i = 0; i < n; ++i) {
            if(bc[i] == -1) ++t;
        }
        if(t == 1) {
            return new int[]{edges[d][0], edges[d][1]};
        } else {
            return new int[]{in[edges[d][1]-1] + 1, edges[d][1]};
        }
        
    }
}
