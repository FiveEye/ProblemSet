class Solution {
    public int trap(int[] height) {
        if(height == null || height.length < 2) return 0;
        Stack<Integer> stack = new Stack<>();
        int i = 0;
        int ret = 0;
        while(i < height.length) {
            
            while(!stack.isEmpty() && height[stack.peek()] < height[i]) {
                int cur = stack.pop();
                if(stack.isEmpty()) {
                    break;
                }
                ret += ((Math.min(height[i], height[stack.peek()]) - height[cur]) * (i-stack.peek() - 1));
            }
            stack.push(i);
            i++;
        }
        return ret;
    }
}
