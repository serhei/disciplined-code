#include <vector>
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        vector<char> sum;
        char carry = 0;
        while (l1 != nullptr || l2 != nullptr || carry > 0) {
            char d = carry;
            if (l1 != nullptr) {
                d += l1->val; l1 = l1->next;
            }
            if (l2 != nullptr) {
                d += l2->val; l2 = l2->next;
            }
            carry = 0;
            while (d > 9) { carry++; d -= 10; }
            sum.push_back(d);
        }
        ListNode* lsum = nullptr;
        for (int k = sum.size()-1; k >= 0; k--) {
            lsum = new ListNode((int)sum[k], lsum);
        }
        return lsum;
    }
};
