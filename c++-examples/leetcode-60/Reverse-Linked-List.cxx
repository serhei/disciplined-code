class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *rhead = nullptr; ListNode *thisN = head;
        while (thisN != nullptr) {
            rhead = new ListNode(thisN->val, rhead);
            thisN = thisN->next;
        return rhead;
    }
};
