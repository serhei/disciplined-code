# Dijkstra's *A Discipline of Programming* -- Chapter 8 Examples

## 8.1 Maximum of Two Numbers {in 3 moves}

**Problem statement:** Given `x`, `y`, compute `m` to ensure

    R.m: (m = x or m = y) and m >= x and m >= y

**Development steps:**

* `(1): if.(0) x >= y -> (1a); y >= x -> (1b)`
* `(2): set.(1a) m var int := x`
* `(3): set.(1b) m var int := y`

Required proof steps:

    (1): (0).pre = (1).pre => (1).EB
         T => (x >= y or y >= x)
    
    (2): (1a).pre => (1a).post.[m -> x]; (1a).post = R.m
         (T and x >= y) => R.m.[m -> x]
         (x >= y) => ((x = x or x = y) and x >= x and x >= y)
    
    (3): (1b).pre => (1b).post.[m -> y]; (1b).post = R.m
         (T and y >= x) => R.m.[m -> y]
         (y >= x) => ((y = x or y = y) and y >= x and y >= y)

**Final program:**

    max2: proc glocon x y, defvar m:
      if: x >= y -> m var int := x
          y >= x -> m var int := y
    :max2

*Note:* `proc` uses the same scope definition directives as `begin`,
TBD abbreviations for more function-signature-like syntax and syntax
for variable/keyword arguments.

## 8.2 Maximum of `n` Numbers {in 7 moves}

**Problem statement:** Given `ax`, `n` satisfying `Pre: n > 0`, compute `k` to ensure

    R: 0 <= k < n and A j : 0 <= j < n : ax.k >= ax.j

**Development steps:**

* `(1): seq.(0)     (1a); (1b)`
* `(2): locvar.(B0) i`
* Define invariant `P: 0 <= k < i <= n and A j : 0 <= j < i : ax.k >= ax.j`
* `(3): do.(1b) {P} i /= n -> (3a)`
* `(4): set.(1a)    k, i var int := 0, 1`
* `(5): if.(3a)     ax.k >= ax.i -> (5a); ax.k <= ax.i -> (5b)`
* `(6): set.(5a)    k, i := i, i + 1`
* `(7): set.(5b)    i := i + 1`

Required proof steps:

    (1): (1a).post = (1b).pre
    (3): (1b).pre => P; P and non (3).EB => R
    (4): Pre => (1a).post.[k, i -> 0, 1]
    (6): (5a).pre => (5a).post.[k, i -> i, i + 1]
    (7): (5b).pre => (5b).post.[i -> i + 1]

**Final program:**

    maxn: proc glocon ax n, defvar k, locvar i:
      P: 0 <= k < i <= n and A j : 0 <= j < i : ax.k >= ax.j
      k, i var int := 0, 1
      do {P}: i /= n and ax.k >= ax.i -> k, i := i, i + 1
              i /= n and ax.k <= ax.i -> i := i + 1
    :maxn

## 8.3a Long Division, basic version

**Problem statement:** ...

...

## 8.3b Long Division, extended with quotient

**Problem statement:** ...

...

## 8.3c Long Division, accelerated by doubling `dd`

...

And, extended with quotient:

...

## 8.3d Long Division, accelerated with multiplication/division by small `m`

...

And, extended with quotient:

...
