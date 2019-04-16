/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * interface Master {
 *     public int guess(String word) {}
 * }
 */
class Solution {
    int n;
    int m;
    int[] rank;
    int[] nosure;
    int[][][] matched;
    String[] wdlst;
    
    public int count(String a, String b) {
        int ret = 0;
        for(int i = 0; i < 6; ++i) {
            if(a.charAt(i) == b.charAt(i)) ++ret;
        }
        return ret;
    }
    
    public int findNext() {
        int ret = -1;
        for(int i = 0; i < n; ++i) {
            if(nosure[i] == 0) continue;
            if(ret == -1) {
                ret = i;
            }
            if(rank[ret] < rank[i]) {
                ret = i;
            }
        }
        return ret;
    }
    
    public void merge(int l, int i) {
        for(int j = 0; j < n; ++j) {
            if(matched[l][i][j] == 0) {
                nosure[j] = 0;
            }
        }
    }
    
    public int countNosure() {
        int ret = 0;
        for(int i = 0; i < n; ++i) {
            ret += nosure[i];
        }
        if(ret < 5) {
            for(int i = 0; i < n; ++i) {
                if(nosure[i] == 1) {
                    System.out.println(wdlst[i]);
                }
            }
        }
        return ret;
    }
    
    public void updateRank() {
        for(int i = 0; i < n; ++i) {
            rank[i] = 0;
        }
        for(int l = 0; l < 6; ++l) {
            for(int i = 0; i < n; ++i) {
                if(nosure[i] == 0) continue;
                for(int j = 0; j < n; ++j) {
                    if(nosure[j] == 0) continue;
                    if(matched[l][i][j] == 0) rank[i]+=(6-l);
                }
            }
        }
    }
    
    public void findSecretWord(String[] wordlist, Master master) {
        n = wordlist.length;
        m = 0;
        rank = new int[n];
        nosure = new int[n];
        matched = new int[6][n][n];
        wdlst = wordlist;
        
        for(int i = 0; i < n; ++i) {
            nosure[i] = 1;
            for(int j = i+1; j < n; ++j) {
                int l = count(wordlist[i], wordlist[j]);
                matched[l][i][j] = 1;
                matched[l][j][i] = 1;
            }
        }
        
        for(int tt = 0; tt < 10; ++tt) {
            int next = findNext();
            int ans = master.guess(wordlist[next]);
            if(ans == 6) return;
            merge(ans, next);
            updateRank();
            //int c = countNosure();
            //System.out.println(wordlist[next] + " " + ans + " " +  c);

        }
        
    }
}
