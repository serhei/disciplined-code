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

**1.** Repeatedly transfer a node from `head` to the (incomplete)
reversed list:

    rev-list: begin def rhead, use head, loc this:
      rhead var maybe.node := none
      this var node := head
      do: this /= none ->
        {1rev convert this into an equivalent node at the front of the (incomplete) reversed list;
              replace this with this.next}
    :rev-list
    
    {1rev convert this into an equivalent node}:
      rhead, this := node/make.(val=this.val, next=rhead), this.next
    :1rev

**Cel Solution:** [`Reverse-Linked-List.cel`](../../cel-examples/leetcode-60/Reverse-Linked-List.cel)  
**C++ Solution:** [`Reverse-Linked-List.cxx`](../../c++-examples/leetcode-60/Reverse-Linked-List.cxx)  
**LeetCode Submission:** <https://leetcode.com/submissions/detail/821954674/>

## Recursive Solution

**1fs.** Converted from the iterative solution, initial false start:

    #.rev-list: begin def rhead, use head:
      {1rec construct reversed head.next with head.val as the last node}
    :end

**1.** Converted from the iterative solution:
    
    rev-list: begin def rhead, use head:
      {1rec construct reversed head with none as the suffix}
    :end

**2.** Introduce a recursive helper generalizing `{1rec}` to different
suffixes:

    {1rec}:
      rhead var maybe.node := none
      rhead:rev-list-worker.(head=head)
    :1rec

    rev-list-worker: begin mod rhead, use head:
      {2rec construct reversed head with rhead as the suffix}
    :end

**3.** Proceed by cases:

    {2rec}: if:
      head = none -> skip
      head /= none -> {3rec construct reversed head.next with (head.val, rhead, ...) as the suffix}
    :2rec

    {3rec construct reversed head.next}:
      rhead := node/make.(val=head.val, next=rhead)
      rhead:rev-list-worker.(head=head.next)
    :3rec

**Cel Solution:** [`Reverse-Linked-List-Recursive.cel`](../../cel-examples/leetcode-60/Reverse-Linked-List-Recursive.cel)  
**C++ Solution:** [`Reverse-Linked-List-Recursive.cxx`](../../c++-examples/leetcode-60/Reverse-Linked-List-Recursive.cxx)  
**LeetCode Submission:** <https://leetcode.com/submissions/detail/821955546/>
