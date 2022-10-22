#include <deque>
class Solution {
public:
    int minDepth(TreeNode* root) {
        deque<TreeNode*> *level = new deque<TreeNode*>;
        deque<TreeNode*> *next = new deque<TreeNode*>;
        if (root != nullptr) level->push_back(root);
        int m = 0;
        bool found_leaf = false; // XXX for min-depth
        // while (level->size() > 0) { // XXX for max-depth
        while (!found_leaf && level->size() > 0) { // XXX for min-depth
            m++;
            // for (int k = 0; k < level->size(); k++) { // XXX for max-depth
            for (int k = 0; !found_leaf && k < level->size(); k++) { // XXX for min-depth
                if ((*level)[k]->left != nullptr)
                    next->push_back((*level)[k]->left);
                if ((*level)[k]->right != nullptr)
                    next->push_back((*level)[k]->right);
                if ((*level)[k]->left == nullptr && (*level)[k]->right == nullptr) found_leaf = true; // XXX for min-depth
            }
            deque<TreeNode *> *t = level;
            level = next; t->clear(); next = t;
        }
        delete level;
        delete next;
        return m;
    }
};
