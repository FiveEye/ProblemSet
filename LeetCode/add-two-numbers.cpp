/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode * nt(ListNode *p) {if(!p) return NULL; return p->next;}
    
    ListNode * add(ListNode *l1, ListNode *l2, int w) {
        if(l1) w += l1->val;
        if(l2) w += l2->val;
        if((!l1) && (!l2) && w == 0) return NULL;
        ListNode *p = new ListNode(w % 10);
        p->next = add(nt(l1), nt(l2), w / 10);
        return p;
    }
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        return add(l1, l2, 0);
    }
};