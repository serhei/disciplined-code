# XXX Currently assumed and alternative annotation keywords:
#
# * Solver assertion +@{...}+ (+=>+)
# * Loop invariant & variant +@loop+ (+-->+, +@shrink+/+@dec+, +@grow+/+@inc+),
#   or +@invariant+/+@inv+
# * Unchecked assertion +@suppose+, or +@provide+/+@provides+
# * Solver hint +@note+
# * Mark unfinished code +@todo+
#
# * Symbol definition +@let+, or +@def+/+@where+
# * Symbol import +@use+, or +@import+ (also used to clone contracts)
#
# * Contract precondition +@require+, or +@given+/+@requires+/+@req+/+@pre+
# * Contract postcondition +@provide+, or +@provides+/+@pro+ (+@entry()+)
# * Contract return value +@returns+, or +@return+/+@retval+/+@ret+
# * Contract scope +@scope+ (e.g. describing const and non-const values)
# * Contract invariant +@enforce+, or +@invariant+/+@inv+
# * Preserved property +@preserve+, or +@preserves+
# 
# * Ruby expression +@rb()+ or +@ruby()+ (if there are ambiguities)
# * Steep type annotation +@type+ [1]
#   (note that it's unclear if Steep is still using this format)
# * Steep dynamic value annotation +@dynamic+
#
# [1]: https://github.com/soutaro/steep/blob/master/manual/annotations.md

# TODO Apply with more Ruby-shaped code e.g. x.each_with_index {|c,i| ...}

##
# Counts the number of times a pattern +p+ appears in the string +x+.
#
# @require
#   p.length >= 1 and x.length >= 0
# @returns nmatch
# @provide
#   R: nmatch == count k : 0 <= k <= lastStart : matchAt(k)
#
# @let lastStart: x.length - p.length
# @let matchAt(k):
#   0 <= k <= lastStart
#   all l : 0 <= l < p.length : p[l] == x[k+l]

def match(p, x)
   # @TODO
end

# XXX We could also describe the contract in a separate file,
# e.g. attached to the RBS type information:
#
# def match: (p: String, x: String) -> Integer
# # @require p.length >= 1 and x.length >= 0
# # @returns nmatch
# # @provide R: nmatch == count k : 0 <= k <= lastStart : matchAt(k)
# # @let lastStart: x.length - p.length
# # @let matchAt(k): 0 <= k <= lastStart,
# #   all l : 0 <= l < p.length : p[l] == x[k+l]

##
# Counts the number of times a pattern +p+ appears in the string +x+.
#
# Naive implementation that scans the string repeatedly.
#
# @use match.contract

# Step I. Check matchAt(j) at every position in +x+.
def match_basic_s1(p, x)
  j, nmatch = 0, 0
  # @let P: nmatch == count k : 0 <= k < j : matchAt(k)
  # @{P} # <- XXX enter in IDE to quickly check initialization, then delete
  # XXX could define P by a substitution? e.g. P: 
  # @loop P, @grow j < lastStart
  while j <= x.length - p.length
    "increment nmatch if matchAt(j) is true" # @todo
    # @{P.[j->j+1]}
    j += 1
  end # @{P and j > lastStart} => {R}
  return nmatch
end

# Step II. Check matchAt(j) by comparing characters in +p+ and +x+.
def match_basic(p, x)
  j, nmatch = 0, 0
  # XXX the solver could infer the variant '@grow j <= lastStart'
  # @loop P: nmatch == count k : 0 <= k < j : matchAt(k)
  while j <= x.length - p.length
    # increment nmatch is matchAt(j) is true"
    k, matches = 0, true
    # @loop Q: matches <=> (all l : 0 <= l < k : p[l] == x[l+j])
    while matches && k < p.length
      matches = false if p[k] != x[k+j]
      k += 1
    end # @{Q and non (matches and k < p.length)} => {matches <=> matchAt(j)}
    # XXX the solver will prove the above in two cases:
    # @note (Q and non matches) => non matchAt(j)
    # @note (Q and matches and k >= p.length) => matchAt(j)
    nmatch += 1 if matches
    j += 1
  end
  return nmatch
end

# Step II', XXX some examples of off-by-one errors to be caught by solver
def match_basic_err(p, x)
  j, nmatch = 0, 0
  # @let P: nmatch == count k : 0 <= k < j : matchAt(k)
  # @loop P, @grow j < lastStart # XXX err1 off-by-one error
  while j < x.length - p.length # XXX err1 off-by-one error
    # increment nmatch is matchAt(j) is true"
    k, matches = 0, true
    # @loop Q: matches <=> (all l : 0 <= l < k : p[l] == x[l+j])
    # @loop @shrink p.length - k # XXX implicit loop variant, failed by err2
    while matches && k < p.length
      matches = false if p[k] != x[k+j]
      # XXX err2 forgot to increment k
    end # @{Q and non (matches and k < p.length)} => {matches <=> matchAt(j)}
    nmatch += 1 if matches
    j += 1
  end # @{P and j > lastStart} => {R} # XXX implicit conclusion, failed by err1
  # XXX err3 forgot to return nmatch, fails @returns clause of match.contract
end
# XXX example of off-by-one error in matchAt() predicate DEFINITION:
# matchAt(k): 0 <= k <= lastStart, all l : 0 <= l <= p.length : p[l] == x[k+l]
#
# This particular error is checkable because p[p.length] is out-of-bounds,
# (which could generate a warning even when an undefined predicate expression
# is assumed to be false)
# but in general a *mismatch* between the predicate and the program
# could indicate an error in either one of the two.
# The solver should report errors accordingly.

# TOTAL: 6 lines of contract, 3 lines of annotation

##
# Counts the number of times a pattern +p+ appears in the string +x+.
#
# Efficient implementation that scans the string only once.
#
# @use match.contract

# Step 0. We want to talk about partial matches starting at different
# positions in different strings, for example:
# - 'the partial match x[r],...,x[s-1]'
# - 'there is a partial match p[r],...,p.high' [note2]
#
# [note2]: Note that p.high is defined as a shorthand for +p[p.length-1]+
#
# To make this easier, it's helpful to define an additional predicate symbol:
#
# @let partMatch(str, r, s): all l : r <= l <= s-1 : p[l-r] == x[l]
# @note (partMatch(x, r, s) and s-r >= p.length) => matchAt(r)
#
# Then
# - 'the partial match x[r],...,x[s-1]' -> partMatch(x,r,s)
# - 'there is a partial match p[r],...,p.high' -> partMatch(p,r,p.length)

# Step I. Track P.1: nmatch is the number of matches starting at x[0],...,x[r-1]
# and P.2: there is a partial match x[r],...,x[s-1].
def match_efficient_s1(p, x)
  # @let P.1: r >= 0 and nmatch == count i : 0 <= i < r : matchAt(i)
  # @let P.2: r <= s and s-r <= p.length and partMatch(x,r,s)
  # @note (P.2 and s-r >= p.length) => matchAt(r)
  nmatch, r, s = 0, 0, 0
  # @loop P.1, P.2, @dec (lastStart-r), @dec (x.length-s)
  while r <= x.length - p.length && s <= x.length
    # XXX test off-by-one error from writing s < x.length
    "increase r, s under invariance of P1, P2" # @todo
  end # @{P.1 and (r > lastStart or s > x.length)} => {R}
  # XXX the solver will prove the above in two cases:
  # @note (P.1 and r > lastStart) => R
  # @note (P.1 and s > x.length and P.2) =>
  #   (P.1 and r == s-(s-r)) >= s-p.length > lastStart) => R
  return nmatch
end

# Step IIa. In the loop, increase +s+ first, then increase +r+.
def match_efficient_s2a(p, x)
  # @let P.1: r >= 0 and nmatch == count i : 0 <= i < r : matchAt(i)
  # @let P.2: r <= s and s-r <= p.length and partMatch(x,r,s)
  # @note (P.2 and s-r >= p.length) => matchAt(r)
  nmatch, r, s = 0, 0, 0
  # @loop P.1, P.2, @dec (lastStart-r), @dec (x.length-s)
  while r <= x.length - p.length && s <= x.length
    # first, increase s as much as possible
    # @loop P.1, P.2, @dec p.length-(s-r)
    while s-r < p.length && x[s] == p[s-r]
      s += 1
    end
    # s cannot be increased further
    if s-r >= p.length
      nmatch += 1
    end
    # second, increase r while preserving P.1 and P.2
    "r = max r2 : r < r2 <= s : (P.1 and P.2).[r->r2]" # @todo
    # or, if r == s, increment both r and s
  end # @{P.1 and (r > lastStart or s > x.length)} => {R}
  return nmatch
end

# Step IIb. This is the tricky part of the reasoning.
# We want to find some r2, r <= r2 <= s that preserves the invariants P.1 and P.2.
# In particular, since P.2.[r->r2] => partMatch(x,r2,s)
# that means partMatch(x,r2,s) must still hold.
#
# We've already scanned the characters from r through s and don't
# want to scan them again. But because we already know partMatch(x,r,s),
# we already know that the characters of x starting at r
# will be the same as the characters of p starting at 0. Therefore:
#
# @note (partMatch(x,r,s) and partMatch(p,r2-r,s-r)) => partMatch(x,r2,s)
#
# We can decide which r is correct by creating a lookup table d that satisfies:
#
# @let Pd: all k : 0 < k <= p.length :
#   d[k] == min.(l : 1 <= l <= k : partMatch(p,l,k))
#
# Then, if we choose r2 == r + d[s-r] and k == s-r, we can conclude:
#
# @note partMatch(x,r,s) and Pd
#       => partMatch(x,r,s) and partMatch(p,d[s-r],s-r)
#       => partMatch(x,r,s) and partMatch(p,r2-r,s-r)
#       => partMatch(r,r2,s)
#
# We also need to show that no matches could start between r and r3:
#
# @note Pd => all r3: r < r3 < r2 : non partMatch(p,r3-r,s-r)
#       => all r3: r < r3 < r2 : non partMatch(x,r3,s)
#       => all r3: r < r3 < r2 : non matchAt(x,r3)
def match_efficient_s2b(p, x)
  # @let Pd: all k : 0 < k <= p.length :
  #   d[k] == min.(l : 1 <= l <= k : partMatch(p,l,k))
  "compute the table d satisfying P.3" # @todo
  # @let P.1: r >= 0 and nmatch == count i : 0 <= i < r : matchAt(i)
  # @let P.2: r <= s and s-r <= p.length and partMatch(x,r,s)
  # @note (P.2 and s-r >= p.length) => matchAt(r)
  nmatch, r, s = 0, 0, 0
  # @loop P.1, P.2, Pd, @dec (lastStart-r), @dec (x.length-s)
  while r <= x.length - p.length && s <= x.length
    # first, increase s as much as possible
    # @loop P.1, P.2, @dec p.length-(s-r)
    while s-r < p.length && x[s] == p[s-r]
      s += 1
    end
    # s cannot be increased further
    if s-r >= p.length
      nmatch += 1
    end
    # second, increase r while preserving P.1 and P.2
    if r < s
      r = r + d[s-r]
      # @{P.1 and P.2}
    else
      r = r + 1; s = s + 1
      # @{r == s} => {P.1 and P.2}
    end
  end # @{P.1 and (r > lastStart or s > x.length)} => {R}
  return nmatch
end

# TODO: Need to clarify the reasoning for this step.
# Step III. Scan the pattern p to produce the lookup table d.
#
# Just as in the main procedure, we will maintain a partial match
# from index r to index s. A natural loop invariant would then be
# "all the matches that start at index r are accounted for in d".
#
# @let P.4: all l, k: 0 < i <= r, i < k < p.length :
#    partMatch(p,l,k) => (k < d.length and d.k <= i)
#
# @require p.length >= 1
# @returns d
# @provide Pd: all k : 0 < k <= p.length :
#   d[k] == min.(l : 1 <= l <= k : partMatch(p,l,k))
def build_lookup_table(p)
  d = []; r = 1; s = 1 # @{P.4 and partMatch(p,r,s)}
  # XXX Example error to check: r = 0, s = 0
  # @loop P.4, partMatch(p,r,s), @dec p.length-r
  while r <= p.length
    # XXX Example error to check: while r < p.length
    # increase s as much as possible
    # @loop partMatch(p,r,s)
    while s < p.length && p[s] == p[s-r]
      # XXX Example error to check: p[s] = p[s-r]
      s = s + 1
    end
    # extend d to known matches
    while s > d.length-1
      d.append(r)
    end
    # increase r, adjust s under invariant of 
    r = r + 1; s = r # the obvious option
    # TODO: The following option is not quite correct,
    # could use the solver to investigate why:
    # if s-r < d.length
    #   r = r + d[s-r]
    # else
    #   r = r + 1; s = r
    # end
  end # @{P.4 and r > p.length} => {Pd}
  return d
end

def match_efficient(p, x)
  d = build_lookup_table(p)
  # @let P.1: r >= 0 and nmatch = count i : 0 <= i < r : matchAt(i)
  # @let P.2: r <= s and s-r <= p.length and partMatch(x,r,s)
  # @note (P.2 and s-r >= p.length) => matchAt(r)
  nmatch, r, s = 0, 0, 0
  # @loop P.1, P.2, Pd, @dec (lastStart-r), @dec (x.length-s)
  while r <= x.length - p.length && s <= x.length
    print "match_efficient @", r, ", ", s, "\n"
    # first, increase s as much as possible
    # @loop P.1, P.2, @dec p.length-(s-r)
    while s-r < p.length && x[s] == p[s-r]
      s += 1
    end
    # s cannot be increased further
    if s-r >= p.length
      nmatch += 1
    end
    # second, increase r while preserving P.1 and P.2
    if r < s
      r = r + d[s-r]
      # @{P.1 and P.2}
    else
      r = r + 1; s = s + 1
      # @{r = s} => {P.1 and P.2}
    end
  end # @{P.1 and (r > lastStart or s > x.length)} => {R}
  return nmatch
end

# TOTAL: 10 lines of contract, 12 lines of annotation

# Test the above code:

$testcases = [
  ['aaaa', 'a', 4],
  ['ababa', 'a', 3],
  ['abbba', 'bb', 2],
  ['ababa', 'aba', 2],
  ['bbbbb', 'bbb', 3],
]
def testMatch()
  $testcases.each do |testcase|
    x, p, expected = *testcase
    puts "'#{x}' =~ '#{p}' :: expected #{expected}, got #{yield(p,x)}"
  end
end

puts "match_basic"
testMatch {|p, x| match_basic(p,x)}
puts "match_efficient"
testMatch {|p, x| match_efficient(p,x)}
