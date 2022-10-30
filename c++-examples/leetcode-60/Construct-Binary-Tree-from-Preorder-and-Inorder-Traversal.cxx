#include <map>
class Solution {
public:
  TreeNode *buildTree(vector<int>& preorder, vector<int>& inorder) {
    // {2nodes}="build an array nodes with elements of type node matching the elements in preorder":
    TreeNode* nodes[preorder.size()];
    for (unsigned k = 0; k < preorder.size(); k++) {
      nodes[k] = new TreeNode(preorder[k]);
    }

    // map<int,int> preorderToInorder;
    // {12build}="build preorderToInorder mapping index k in preorder to the same item's index j in inorder":
    map<int,int> valToInorder;
    for (unsigned i = 0; i < inorder.size(); i++)
      valToInorder[inorder[i]] = i;
    // for (unsigned j = 0; j < preorder.size(); j++)
    //   preorderToInorder[j] = valToInorder[preorder[j]];

    int lb[preorder.size()]; int rb[preorder.size()];
    lb[0] = 0; rb[0] = inorder.size()-1;
    // {0proc}="find and connect the left and right subtrees for each item in preorder":
    for (unsigned k = 0; k < preorder.size(); k++) {
      // {1find}="find and connect the left and right subtrees of preorder[k]":
      // {6find}="find the position M of the (unique) value preorder[k] within inorder":
      //unsigned M = preorderToInorder[k];
      unsigned M = valToInorder[preorder[k]];
      // {6left}="update lb,rb for the left subtree, rooted at preorder.[k+1], if any":
      if (lb[k] < M) {
        lb[k+1] = lb[k]; rb[k+1] = M-1;
      }
      // {4left}="connect nodes[k] to nodes[k+1], the root of its left subtree, if any":
      if (lb[k] < M) {
        nodes[k]->left = nodes[k+1];
      }
      // {4N}="find the length N of the left subtree of nodes[k], if any":
      unsigned N = 0;
      if (lb[k] < M) {
        N = M-lb[k];
      } // else N = 0;
      // {4right}="connect nodes[k] to nodes[k+N+1], the root of its right subtree, if any":
      if (rb[k] > M) {
        nodes[k]->right = nodes[k+N+1];
      }
      // {6right}="update lb,rb for the right subtree, rooted at preorder.[k+N+1], if any":
      if (rb[k] > M) {
        lb[k+N+1] = M+1; rb[k+N+1] = rb[k];
      }
    }

    // {0root}="return the root node of the tree":
    return nodes[0];
  }
};
