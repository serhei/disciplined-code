# Valid Parentheses

**Problem Statement.** Given an input string `s` with indices ranging
from a lower bound `s.lob` to an upper bound `s.hib`, and containing
only the characters `(`, `)`, `{`, `}`, `[`, `]`, determine whether
`s` is valid, i.e. whether the opening and closing brackets are
balanced correctly.

**Source:** <https://leetcode.com/problems/valid-parentheses/>

## Solution

A *valid prefix* of `s` with closing index `i` is a substring
`s.(lob..i)` which is valid, i.e. the opening brackets and closing
brackets are balanced correctly. We can use this definition to
implement a solution with the following structure:

    valid-parens: begin def valid, use s, {1}

    1: seq:
      {1find}="compute the longest valid prefix of the string s"
      {1end}="return true if the longest valid prefix covers the entirety of s"
    :1

After the program executes, the variable `valid` should contain `true`
if and only if `s` is valid.

### The Basic Strategy -- Looping with an Invariant

The longest valid prefix of the string `s` cannot be found in one
step. The program will have to go through a sequence of intermediate
states that gradually move it towards the final state.

The present problem is straightforward in part because the sequence of
intermediate states is clear: we are going to scan the string `s` one
character at a time. Thus, we'll introduce the variable `i` to denote
the index of the last character of `s` that has been scanned.

We introduce the variable `valid-end` to denote the index of the last
character of the longest valid prefix of `s.(lob..i)`. At the end,
when we've scanned the entire string, `valid-end` should denote the
longest valid prefix of `s.(lob..hib)`. Then we can use it to compute
`valid`:

    2a: loc.{0} valid-end
    2b: {1end}: valid var bool := (valid-end = s.hib)

It might not make sense to scan the entire string if it includes an
'obvious' error, such as `"()}[(..."`, where a closing bracket has no
matching opening bracket and we can immediately conclude the string is
invalid. Thus, we start writing the loop to scan `s` with a carefully
phrased placeholder condition that preserves the possibility of
terminating early:

    3: {1find}:
      valid-end var int := s.lob-1
      -- <- the empty string at the start of s is valid
      do: {3cond}="valid-end could still be extended" ->
          {3scan}="scan one more character of s and extend valid-end if possible"
    :3

We say that a prefix of `s` *could be part of a valid prefix* if there
is a way to add characters at the end to produce a valid string,
i.e. there are no incorrect closing brackets, and the remaining
opening brackets could be closed to produce a valid string.

This definition lets us start defining *invariants* for the loop.  In
the following step, the predicates `P1` and `P2` specify the key
conditions that must be satisfied by `i` and `valid-end` respectively:

    4a: loc.{1,3.do.before} i var int := s.lob-1
    4b: inv.{3.do} P1: "s.(lob..i) could be part of a valid prefix"
    4c: inv.{3.do} P2: "s.(lob..valid-end) is the longest valid prefix of s.(lob..i)"

To determine when `valid-end` can no longer be extended, we introduce
an additional boolean variable `fin` and an invariant predicate `P3`.
The loop can be exited either when `i = s.hib` (`valid-end` identifies
the longest valid prefix of `s.(lob..i), i = hib`) or when `fin` is
set to true (and `valid-end` can no longer be extended, and hence
identifies the longest valid prefix of `s`):

    4d: loc.{1,3.do.before} fin var bool := false
    4e: inv.{3.do} P3: fin => "s.(lob..i+1) could not be part of a valid prefix"
    4f: {3cond}: i < s.hib and non fin

(*In a programming language such as C, we would exit the loop with a
`break` statement instead of using a boolean variable, but a
structured programming style that avoids non-linear control flow has
the advantage of making the prerequisites for ending the loop more
obvious.*)

### The Loop Body

The need to update different variables gives us an obvious way to
split the loop body. First we scan an additional character and extend
`i` (satisfying conditions `P1` and `P3`). Then we extend `valid-end`
to identify the longest valid prefix of `s.(lob..i)`:

    5: {3scan}:
      {5i}="check if s.(lob..i+1) could be part of a valid prefix and extend i, fin"
      {5valid-end}="check if s.(lob..i) is a valid prefix; extend valid-end if possible"

The operation `{5i}` must examine the character at `s.(i+1)` and, if
it's a closing parenthesis, must determine if it can be matched to an
earlier parenthesis in the string. To do this, we introduce a variable
`parens` that keeps track of the currently open parentheses in
`s.(lob..i)`:

    6a: loc.{0,3.do.before} parens var list.int := ()
    6b: inv.{3.do} P4: "parens gives the indices of unclosed parens in s.(lob..i)"

The invariant `P4` makes it easy to fill in `{5valid-end}':

    6c: {5valid-end}: when: parens.empty -> valid-end := i :when

At this point, the remainder of the program is straightforward to
implement by considering the various possibilities for whether the
character `s.(i+1)` is an opening or closing bracket and whether it
matches an earlier opening bracket. For the purpose of comparing
brackets, we introduce two helper functions:

    is-closing: fn c -> c in {')', '}', ']'}
    opener: fn ')' -> '(', '}' -> '{', ']' -> '['

Then proceed by cases to finish the program:

    7a: wrap.{3.do.body} use s, mod valid-end, i, fin, parens, loc nc, lc
        -- <- creates a local scope around the body of (3.do)
    7b: ins.{3scan.before} nc var char := s.(i+1)
    7c: ins.{3scan.before} lc var maybe.char := maybe.s.(parens.high)
        -- <- the maybe operator evaluates to none if s.(parens.high) is invalid
    7d: {5i} if:
      non is-closing.nc ->
        -- opening bracket; record it in parens
        parens:hiext i + 1; i := i + 1
      parens.empty and is-closing.nc ->
        -- closing bracket but no matching opening bracket
        fin := true
      non parens.empty and is-closing.nc and lc = opener.nc ->
        -- closing bracket with a matching opening bracket
        parens:hirem; i := i + 1
      non parens.empty and is-closing.nc and lc /= opener.nc ->
        -- closing bracket but the last opening bracket is different
        fin := true

<!-- previously had a BUG here (parens:hiext i; i := i + 1) -->

**Cel Solution:** [`Valid-Parentheses.cel`](../../cel-examples/leetcode-60/Valid-Parentheses.cel)  
**C++ Solution:** [`Valid-Parentheses.cxx`](../../c++-examples/leetcode-60/Valid-Parentheses.cxx)  
**LeetCode Submission:** <https://leetcode.com/submissions/detail/703131201/> 
