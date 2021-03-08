# *WIP* -- Notes on the Pattern-Matching Problem from Ch. 18 of "A Discipline of Programming"

These notes illustrate some of the programming methods I learned from Dijkstra's "A Discipline of Programming". I decided to start with an explanation of the pattern-matching problem from Chapter 18 of that book because the problem definition is relatively straightforward and the problem has a na&iuml;ve solution that is easy to understand. If we already know what to expect from the problem, we can focus on the programming method and how it contributes to an improved solution. Once I have this simple problem described cleanly, it will make more sense to try describing a more complex example (such as the 3D convex hull chapter of Dijkstra's book).

Along the way, I speculate on various types of interactive tools that could help a programmer with the task of formulating and proving predicates. However, Dijkstra's methods are intended to be simple enough for a skilled programmer to apply with the aid of only pencil and paper.

## Problem Statement and Na&iuml;ve Solution

**Problem Statement.** Given two sequences of values `p.0, p.1, ..., p.(N-1)` and `x.0, x.1, ..., x.(M-1)` with `N >= 1` and `M >= 0`, how many times (and at which positions) does the pattern `p` occur within the sequence `x`?

For example, `x` could be a string `"ababacabab"` and `p` could be a string `"aba"`. In that case, `p` would occur within `x` a total of 3 times, starting at positions 0, 2, and 6.

...
