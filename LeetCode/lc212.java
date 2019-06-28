class Solution {
    public TrieNode root = new TrieNode();
    
    public void dfs(Set<String> ret, int i, int j, char[][] board, TrieNode root, boolean[][] visited) {
        if(root != null && root.s != null) ret.add(root.s);
        if(i < 0 || i >= board.length || j < 0 || j >= board[0].length || visited[i][j] || root == null ) return; 
        visited[i][j] = true; 
        dfs(ret, i - 1, j, board, root.children[board[i][j] - 'a'], visited);
        dfs(ret, i + 1, j, board, root.children[board[i][j] - 'a'], visited);
        dfs(ret, i, j - 1, board, root.children[board[i][j] - 'a'], visited);
        dfs(ret, i, j + 1, board, root.children[board[i][j] - 'a'], visited);
        visited[i][j] = false; 
    }
    public void insert(TrieNode cur, String word) {
        for(int i = 0; i < word.length(); i++) {
            int index = word.charAt(i) - 'a';
            if(cur.children[index] == null) {
                cur.children[index] = new TrieNode();
            }
            cur = cur.children[index];
        }
        cur.s = word;
    }
    public List<String> findWords(char[][] board, String[] words) {
        Set<String> ret = new HashSet<>(); 
        if(words == null || words.length == 0) return new ArrayList<>();
        for(String word : words) insert(root, word);
        for(int i = 0; i < board.length; i++) {
            for(int j = 0; j < board[0].length; j++) {
                boolean[][] visited = new boolean[board.length][board[0].length]; 
                dfs(ret, i, j, board, root, visited);
            }
        }
        List<String> ans = new ArrayList<>(); 
        for(String s : ret) ans.add(s);
        
        return  ans;
    }
}

class TrieNode {
    String s; 
    TrieNode[] children = new TrieNode[26];
}
