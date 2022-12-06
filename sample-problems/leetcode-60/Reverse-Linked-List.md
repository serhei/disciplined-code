# Reverse Linked List

**Problem Statement:** Given the `head` of a singly linked list,
reverse the list, and return the reversed list.

Assume a list node `N` supports the following operations:

- `L.val`: the value of the list node. Returns `int`.
- `L.next`: the next node of the list node. Returns `maybe.node`.
- `node/make.(val=0, next=none)`: construct a list node with specified
  `val` and `next.`

**Source:** https://leetcode.com/problems/reverse-linked-list/

(The LeetCode problem statement explicitly suggests to implement the
problem both iteratively and recursively.)

## Iterative Solution

Repeatedly transfer a node from `head` to the (incomplete) reversed list:

    0: rev-list: begin def rhead, use head, loc this:
      rhead var maybe.node := none
      this var node := head
      do: this /= none ->
        {0rev}="convert this into an equivalent node at the front of the (incomplete) reversed list; replace this with this.next"
    :0
    
    1: {0rev}:
      rhead, this := node/make.(val=this.val, next=rhead), this.next
    :1

**Cel Solution:** [`Reverse-Linked-List.cel`](../../cel-examples/leetcode-60/Reverse-Linked-List.cel)  
**C++ Solution:** [`Reverse-Linked-List.cxx`](../../c++-examples/leetcode-60/Reverse-Linked-List.cxx)  
**LeetCode Submission:** <https://leetcode.com/submissions/detail/821954674/>

## Recursive Solution

Converted from the iterative solution, initial false start:

    #.0fs: rev-list: begin def rhead, use head:
      {0rec}="construct reversed head.next with head.val as the last node"
    :0fs

Converted from the iterative solution:
    
    0: rev-list: begin def rhead, use head:
      {0rec}="construct reversed head with none as the suffix"
    :0

Introduce a recursive helper generalizing `{0rec}` to different suffixes:

    1a: {0rec}:
      rhead var maybe.node := none
      rhead:rev-list-worker.(head=head)
    :1a
    1b: rev-list-worker: begin mod rhead, use head:
      {1rec}="construct reversed head with rhead as the suffix"
    :1b

Proceed by cases:

    2: {1rec}: if:
      head = none -> skip
      head /= none -> {2rec}="construct reversed head.next with (head.val, rhead, ...) as the suffix"
    :2
    
    3: {2rec}:
      rhead := node/make.(val=head.val, next=rhead)
      rhead:rev-list-worker.(head=head.next)
    :3

**Cel Solution:** [`Reverse-Linked-List-Recursive.cel`](../../cel-examples/leetcode-60/Reverse-Linked-List-Recursive.cel)  
**C++ Solution:** [`Reverse-Linked-List-Recursive.cxx`](../../c++-examples/leetcode-60/Reverse-Linked-List-Recursive.cxx)  
**LeetCode Submission:** <https://leetcode.com/submissions/detail/821955546/>
