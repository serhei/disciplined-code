#include <deque>
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
        vector<vector<int>> vals; // TODO: C++ fixy to return by value more efficiently?
        deque<TreeNode *> roots;
        if (root != nullptr) roots.push_back(root);
        bool flip = false;
        int r = 0;
        while (roots.size() > 0) {
            if (r == 0) {
                flip = !flip;
                vector<int> nv; vals.push_back(nv); // TODO C++ fixy
                r = roots.size();
            }
            TreeNode *n;
            if (flip) {
                n = roots.back(); roots.pop_back();
            } else {
                n = roots.front(); roots.pop_front();
            }
            vals[vals.size()-1].push_back(n->val);
            r--;
            if (flip) {
                if (n->right != nullptr) roots.push_front(n->right);
                if (n->left != nullptr) roots.push_front(n->left);
            } else {
                if (n->left != nullptr) roots.push_back(n->left);
                if (n->right != nullptr) roots.push_back(n->right);
            }
        }
        return vals;
    }
};
