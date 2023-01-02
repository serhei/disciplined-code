#include <deque>
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> vals; // TODO: C++ fixy to return by value more efficiently?
        deque<TreeNode *> roots;
        if (root != nullptr) roots.push_back(root);
        int r = 0;
        while (roots.size() > 0) {
            if (r == 0) {
                vector<int> nv; vals.push_back(nv); // TODO: C++ fixy
                r = roots.size();
            }
            TreeNode *n = roots.front(); roots.pop_front();
            vals[vals.size()-1].push_back(n->val);
            r--;
            if (n->left != nullptr) roots.push_back(n->left);
            if (n->right != nullptr) roots.push_back(n->right);
        }
        return vals;
    }
}
