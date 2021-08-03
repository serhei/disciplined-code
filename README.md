# Serhei's Notes on Disciplined Programming

A long time ago, this repository held a handful of cheatsheets I found
useful for doing programming competitions. In 2021, I'm using it to
collect examples and techniques for learning disciplined programming.

Following a collection of texts by Edsger W. Dijkstra, development of
a program can be said to proceed in a disciplined manner if we are
mindful of each decision taken to develop the program and we are
confident that each decision is correct and natural.

Dijkstra documents several techniques to achieve this goal:

- stepwise refinement to break down a problem into smaller subproblems
- predicates defined via weakest-precondition semantics and used
  judiciously to guide the development of the solution
- development of larger systems as a series of layers (cf ['THE' 1968](https://www.eecs.ucf.edu/~eurip/papers/dijkstra-the68.pdf))

My interest is to illustrate these skills on a collection of complex
problems and extend their application beyond small algorithmic
programs. Longer-term, this work may lead to the development of new
tools to support disciplined programming.

Reading list:
- Dijkstra, [*EWD 227*](http://www.cs.utexas.edu/users/EWD/transcriptions/EWD02xx/EWD227.html): 'Stepwise program construction'
- Dijkstra, [*EWD 1300*](https://www.cs.utexas.edu/users/EWD/transcriptions/EWD13xx/EWD1300.html): 'The notational conventions I adopted, and why'
- Dijkstra, [*A Discipline of Programming*](http://www.amazon.com/Discipline-Programming-Edsger-W-Dijkstra/dp/013215871X) (out of print, probably best to search on libgen.rs)
- Gries, [*The Science of Programming*](http://www.amazon.com/Science-Programming-Monographs-Computer/dp/0387964800/ref=sr_1_1?s=books&ie=UTF8&qid=1435447965&sr=1-1&keywords=science+of+programming)

**TODO** Examples, coming soon:
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
