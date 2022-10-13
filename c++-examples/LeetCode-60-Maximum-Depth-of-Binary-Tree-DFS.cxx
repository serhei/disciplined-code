#include <deque>
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        deque<TreeNode*> path = { root };
        deque<unsigned char> next = { 0 }; // 0,1,2 -> L,R,X
        int m = 1;
        while (path.size() >= 1)
        {
            if (next.back() == 0)
            {
                next.back() = 1;
                //next.pop_back(); next.push_back(1);
                if (path.back()->left != nullptr)
                {
                    path.push_back(path.back()->left);
                    next.push_back(0);
                }
            }
            if (next.back() == 1)
            {
                next.back() = 2;
                //next.pop_back(); next.push_back(2);
                if (path.back()->right != nullptr)
                {
                    path.push_back(path.back()->right);
                    next.push_back(0);
                }
            }
            while (next.size() > 0 && next.back() == 2)
            {
                path.pop_back();
                next.pop_back();
            }
            if (path.size() > m) m = path.size();
        }
        return m;
    }
};
