# Minimum Depth of Binary Tree

**Problem Statement:** Given the root node `root` of a binary tree,
return the minimum depth of the tree, i.e. the length of the shortest path from the root node to a leaf node of the tree.

Assume a binary tree node `N` supports the following operations:

- `N.left`: retrieve left subtree, if any. Returns `maybe.node`.
- `N.right`: retrieve right subtree, if any. Returns `maybe.node`.

**Source:** <https://leetcode.com/problems/minimum-depth-of-binary-tree>

(Note that the Cel solution assumes a root node always exists.  The
C++ solutions for LeetCode must also correctly handle the edge case
when `root == nullptr` and so the depth is `0`.)

## Solution

(Adapt the code from the [breadth-first search solution](Maximum-Depth-of-Binary-Tree.md#breadth-first) of the
problem '*Maximum Depth of Binary Tree*', as specified in the linked
problem writeup.)

**Cel Solution:** [`Minimum-Depth-of-Binary-Tree.cel`](../../cel-examples/leetcode-60/Minimum-Depth-of-Binary-Tree.cel)  
**C++ Solution:** [`Minimum-Depth-of-Binary-Tree.cxx`](../../c++-examples/leetcode-60/Minimum-Depth-of-Binary-Tree.cxx)  
**LeetCode Submission:** <https://leetcode.com/submissions/detail/811491239/> <!-- TODO: from old account; needs cleanup -->
