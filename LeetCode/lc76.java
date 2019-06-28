class Solution {
    public String minWindow(String s, String t) {
        int[] k = new int[256];
        int[] tt = new int[256]; 
        int count = 0, target = 0;
        int j = 0, n = s.length();
        for(int i = 0; i < t.length(); ++i) {
            int x = t.charAt(i);
            if(tt[x] == 0) {
                target++;
            }
            tt[x]++;
        }
        int ans_i = 0, ans_j = n + 1;
        for(int i = 0; i < n; ++i) {
            for(;j < n && count != target;++j) {
                int x = s.charAt(j);
                if(tt[x] == 0) continue;
                k[x]++;
                if(k[x] == tt[x]) count++;
                
            }
            if(count != target) {
                break;
            }
            if(j - i < ans_j - ans_i) {
                ans_i = i;
                ans_j = j;
            }
            int x = s.charAt(i);
            if(tt[x] == 0) {
                continue;
            }
            if(k[x] == tt[x]) count--;
            k[x]--;
        }
        if(ans_j - ans_i == n+1) return "";
        return s.substring(ans_i, ans_j);
    }
