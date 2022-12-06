class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        return revListWorker(nullptr, head);
    }
    ListNode* revListWorker(ListNode* rhead, ListNode* head) {
        if (head == nullptr) return rhead;
        return revListWorker(new ListNode(head->val, rhead), head->next);
    }
};
