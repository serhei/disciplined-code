# Maximum Depth of Binary Tree

**Problem Statement:** Given the root node `root` of a binary tree,
return the maximum depth of the tree, i.e. the length of the longest path from the root node to a leaf node of the tree.

Assume a binary tree node `N` supports the following operations:

- `N.left`: retrieve left subtree, if any. Returns `maybe.node`.
- `N.right`: retrieve right subtree, if any. Returns `maybe.node`.

**Source:** <https://leetcode.com/problems/maximum-depth-of-binary-tree>

(Note that the Cel solutions assume a root node always exists.  The
C++ solutions for LeetCode must also correctly handle the edge case
when `root == nullptr` and so the depth is `0`.)

## Solution based on Depth-First Search

My initial take on this problem.

    0: max-depth: begin def m, use root:
      {0dfs}="perform a depth-first (inorder) traversal and record the distance to the deepest node seen in m"
    :0

    1: {0dfs}:
      loc.{0} path var list.node := (root)
      loc.{0} dir var list.enum.(L,R,X) := (L)
      loc.{0} m var int := 1
      do: path.dom > 0 ->
        {1a}="continue the depth-first traversal, advancing by one node from path.high or popping path"
        {1b}="update m if we reached a new depth"
    :1

(The array `path` represents the current position in the tree, with
`dir.i` indicating the *next* subtree that should be tried from
`path.i`: `L` for left, `R` for right, `X` when no more subtrees are
left to try.)

    2: {1b}: when: path.dom > m -> m := path.dom :when

    3: {1a}:
      {3left}="when dir.high = L, advance to the left subtree if possible"
      {3right}="when dir.high = R, advance to the right subtree if possible"
      {3pop}="when dir.high = X, pop as many nodes as possible"
    :3

(The three placeholder statements in `3` are deliberately chained in a
sequence: if advancing to the left subtree fails, then we immediately
set `dir.high` to `R` and attempt to advance to the right subtree, and
so forth.)

    4: {3left}: when:
      dir.high = L and path.high.left /= none ->
        dir:hialt R; dir:hiext L; path:hiext path.high.left
      dir.high = L and path.high.left = none ->
        dir:hialt R
    :4

    5: {3right}: when:
      dir.high = R and path.high.right /= none ->
        dir:hialt X; dir:hiext L; path:hiext path.high.right
      dir.high = R and path.high.right = none ->
        dir:hialt R
    :5

    6: {3pop}: do: dir.high = X -> dir:hipop; path:hipop :do

**Cel Solution:** [`Maximum-Depth-of-Binary-Tree-DFS.cel`](../../cel-examples/leetcode-60/Maximum-Depth-of-Binary-Tree-DFS.cel)  
**C++ Solution:** [`Maximum-Depth-of-Binary-Tree-DFS.cxx`](../../c++-examples/leetcode-60/Maximum-Depth-of-Binary-Tree-DFS.cxx)  
**LeetCode Submission:** <https://leetcode.com/submissions/detail/811443416/> <!-- TODO: from old account; needs cleanup -->

## Solution based on Breadth-First Search
<a name="breadth-first" />

My second solution based on breadth-first search and two arrays can
also be adapted to the related [*Minimum Depth of Binary Tree*](Minimum-Depth-of-Binary-Tree.md)
problem, as described below:

    0: max-depth: begin def m, use root, loc next:
      m var int := 0; next var list.node := (root)
      do: next.dom > 0 -> -- *1
        m := m + 1
        {0next}="replace next with a list of all the child nodes of elements of next"
    :0

*If finding the minimum depth instead, the line marked `-- *1` should
instead read `do: non found-leaf and next.dom > 0 ->` and there should
be a local variable definition `loc.{0} found-leaf var bool := false`.*

    1: {0next}: begin mod next, loc children, k:
      k var int := next.lob - 1; children var list.node := ()
      do: k < next.hib -> -- *2
        k := k + 1
        when: next.k.left /= none -> children:hiext next.k.left :when
        when: next.k.right /= none -> children:hiext next.k.right :when
        -- *3
      :do
      next := children
    :1

*If finding the minimum depth instead, the line marked `-- *2` should
instead read `do: non found-leaf and k < next.hib` and the line marked
`-- *3` should be replaced with the following statement:*

    when: next.k.left = next.k.right = none -> found-leaf := true :when

**Cel Solution:** [`Maximum-Depth-of-Binary-Tree.cel`](../../cel-examples/leetcode-60/Maximum-Depth-of-Binary-Tree.cel)  
**C++ Solution:** [`Maximum-Depth-of-Binary-Tree.cxx`](../../c++-examples/leetcode-60/Maximum-Depth-of-Binary-Tree.cxx)  
**LeetCode Submission:** <https://leetcode.com/submissions/detail/811491239/> <!-- TODO: from old account; needs cleanup -->

## **TODO** Other Ideas to Try

- A more basic breadth-first traversal with single queue.
- *Language design:* packaging the breadth-first traversal in an iterator.
