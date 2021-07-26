# Serhei's Notes on Disciplined Programming

A long time ago, this repository held a handful of cheatsheets I found
useful when doing programming competitions. In 2021, I'm using it to
collect notes on methods for disciplined programming.

'Disciplined programming' is a term I've coined after studying a set
of books and articles by Edsger W. Dijkstra describing the various
skills required to develop dense, algorithmic code with confidence and
a low probability of programmer error. These skills include:

- top-down refinement to break down a problem into smaller pieces
- judicious use of predicates and weakest-precondition semantics to
  guide the development of a solution
- layered architecture for larger systems (cf [THE 1968](https://www.eecs.ucf.edu/~eurip/papers/dijkstra-the68.pdf))

Long-term, I have some interest in developing new kinds of developer
tools to better support disciplined programming. Short-term, I want to
finish mastering these skills on a collection of increasingly more
complex problems solved with existing programming languages and
developer tools.

Reading list:
- Dijkstra, [*EWD 227*](http://www.cs.utexas.edu/users/EWD/transcriptions/EWD02xx/EWD227.html)
- Dijkstra, [*EWD 1300*](https://www.cs.utexas.edu/users/EWD/transcriptions/EWD13xx/EWD1300.html)
- Dijkstra, [*A Discipline of Programming*](http://www.amazon.com/Discipline-Programming-Edsger-W-Dijkstra/dp/013215871X) (out of print, probably best to search on libgen.rs)
- Gries, [*The Science of Programming*](http://www.amazon.com/Science-Programming-Monographs-Computer/dp/0387964800/ref=sr_1_1?s=books&ie=UTF8&qid=1435447965&sr=1-1&keywords=science+of+programming)

**TODO** Examples coming soon:
- *'Saruman's Army'*, a basic dynamic programming (DP) problem
- *String pattern matching*, from Ch18 of *A Discipline of Programming*
- *Laminar set optimization*, a slightly more complex DP problem

## Programming Language Cheatsheets

**TODO** These will need to be reworked to support direct translation
of the common constructs and data structures in my pseudocode:
- [C++](cheatsheet.cc)
- [Java](cheatsheet.java)
- *Python*
- *Ruby*
