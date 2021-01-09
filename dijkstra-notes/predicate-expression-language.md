# Predicate Expression Language

In-progress notes on a predicate notation I developed while studying through Dijkstra's *A Discipline of Programming*. The notation is intended for writing predicate expressions in a comfortable way. I plan to gradually evolve my rough sketch closer to a rigorous and complete language specification.

The syntax is described by an (ambiguous) EBNF grammar. Brackets `[` and `]` signify an optional element. Brackets `{` and `}` signify an element that may be repeated 0 or more times.

## Basic Definitions

A predicate expression is evaluated against a *program state* and *environment*.

The program state consists of a set of named *variables*. Each top-level variable has a *type* and a set of *fields* and *methods*.

The environment consists of a set of named *global constants* and *functions*.

A predicate expression can be thought of as a function that maps program states to values in some data type.

A *predicate* is a boolean-valued predicate expression.

A predicate can be thought of as a function that maps program states to boolean values `true` and `false`. A predicate function can also be thought of as the subset of program states that satisfy the predicate (i.e. the set of states on which the predicate evaluates to `true`).

## Vocabulary

**Identifiers** are sequences of letters, digits, hyphen `-` and underscore `_`. The first character must be a letter.

    IDENT -> LETTER {LETTER | DIGIT | '-' | '_'}

**Numbers** are signed integers.

    INTEGER -> ["-"] DIGIT {DIGIT}

**Operators** and **delimiters** are any of the special character sequences listed or reserved identifiers listed below:

    + - * / **
    = /= < > <= >=
    and or cand cor =>
    . , : ; NEWLINE ( )
    true false

Some of these act as binary operators:

    BINARY -> '+' | '-' | '*' | '/' | '**' |
              '=' | '/=' | '<' | '>' | '<=' | '>=' |
              'and' | 'or' | 'cand' | 'cor' | '=>'

Others act as delimiters with a special syntax role:

    DELIMITER -> '.' | ',' | ':' | ';' | NEWLINE | '(' | ')'

The keywords `true` and `false` are reserved for boolean literals:

    BOOLEAN -> 'true' | 'false'

Newlines are skipped (treated as non-significant whitespace) if they occur in a position where they do not act as a delimiter:

    (empty) -> NEWLINE

## Predicate Expressions

Rough sketch of the grammar:

    expr -> INTEGER
    expr -> IDENT
    expr -> BOOLEAN
    expr -> expr {BINARY expr}
    expr -> '(' expr ')'
    expr -> form

Binary operators listed in order of decreasing precedence:

    **
    * /
    + -
    = /= < > <= >=
    and or cand cor =>

Comparison operators may be chained, e.g.

    q.1 <= q.2 <= q.3 <= q.4
    0 <= a = b < n

## Form Application

Both LISP-style `f a b c` and Dijkstra-style `f.(a b c)` (somewhat inspired by [EWD 1300][ewd_1300]) forms are permitted.

In addition, the arguments of a form can be separated by spaces, commas `,`, colons `:`, or semicolons `;`, in descending order of priority, to allow maximum flexibility in . For example, `f a x.b : c p q, y.r : d z` is parsed as `f.(a.(x.b) c.(p.q y.r) d.z)`. This allows to write nested forms without overuse of parentheses. The colons in particular are useful for writing quantifier expressions e.g. `all i : i >= 0 : P.i`.

Rough sketch of the grammar:

    form -> form_head args
    form -> form_head '.' args
    form -> form_head '.' expr
    form_head -> IDENTIFIER | BINARY
    args -> arg {arg}
    args -> args_list
    args_list -> '(' args ')'
    args_list -> arg {',' arg}
    args_list -> arg {':' arg}
    args_list -> arg {stmt_sep arg}
    arg -> expr | args_list
    stmt_sep -> ';' | NEWLINE

[ewd_1300]: https://www.cs.utexas.edu/users/EWD/transcriptions/EWD13xx/EWD1300.html

A binary operation `a op b` is syntactic sugar for the form application `op a b`.

Possible meanings of form application:
- *Array indexing*, e.g. `ax.i` &ndash; `ax` is an array, `i` is an index.
- *Method or field reference*, e.g. `ax.val` &ndash; `ax` is a variable, `val` identifies a method or a field of `ax`.
- *Function or method invocation*, e.g. `f.(a b c)` &ndash; `f` is a global function or a method.
- *Special form*, e.g. a quantifier expression `some.(k : int : a - r = k * d)`.

Some special forms accept nested argument lists, e.g. `all.(x, y : 0 <= x, x <= y : foo.x, bar .y)`

## Quantifier and Comprehension Expressions

Existential quantifier with data type:

    some k : int : a - r = k * d

Existential quantifier with predicate:

    some k : k >= 0 : a - r = k * d

Universal quantifier with predicate:

    all i : 0 <= i <= n : f.i = 6

Count the elements satisfying a predicate or list of predicates:

    count i : 0 <= i < r : match i

Minimum and maximum of a set:

    min i : 0 < i <= j : dif.(i j) = false
    max i : 0 < i <= j : dif.(i j) = false

Each element of a quantifier can be a nested argument list:

    all x, k : 0 < x <= i, x < k < N, shift.(x k) : k <= d.hib, d.k <= x

## Builtin Forms

- Logical negation `non P`.
- Integer modulus `mod a d`.

## Labeled Predicates

Rough sketch of the grammar:

    labeled_predicate -> header ':' expr
    header -> IDENT
    header -> IDENT '.' label_arg
    header -> IDENT '.' '(' label_arg { label_arg } ')'
    label_arg -> IDENT
    label_arg -> label_const
    label_const -> INTEGER

Examples:

    R: 0 <= k < n and all.(i : 0 <= i < n : f.k >= f.i)
    R.1: 0 <= r < d and some.(k : int : a - r = k * d)
    P2: 1 <= k <= n and r < s + fact.k and mod.(s fact.k) = 0
    dif i k: some j : 0 <= k < k-i : p.j /= p.(i+j)
