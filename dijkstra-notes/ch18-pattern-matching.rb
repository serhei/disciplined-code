# XXX Currently assumed annotations:
# * Contract +@given+/+@require+/+@req+/+@pre+, +@provide+/+@pro+
# * Return value contract +@return+/+@returns+ (+@where+)
# * Cloned contract +@same-contract-as+/+@same-contract+
# * Symbol definition +@let+, +@where+
# * Loop invariant, loop variant +@loop+ (+-->+, +@dec+, +@inc+)
# * Checked assertion +@{...}+ (+=>+)
# * Solver hint +@note+
# * Unimplemented +@TODO+
# * Bare assertion +@assume+
# * **TODO** Scope annotation (e.g. describing const and non-const values)
# * **TODO** Type annotation (e.g. shared with Steep annotation format [1])
#
# [1]: https://github.com/soutaro/steep/blob/master/manual/annotations.md

# XXX Apply with more Ruby-shaped code e.g. x.each_with_index {|c,i| ...}

##
# Counts the number of times a pattern +p+ appears in the string +x+.
#
# @given (N: p.length >= 1) and (M: x.length >= 0)
# @returns nmatch
# @where R: nmatch = count i : 0 <= i <= M-N : matchAt(i)
# @where matchAt(i): 0 <= i <= M-N, all j : 0 <= j < N : p[j] = x[j+i] 

def match(p, x)
   # @TODO
end

##
# Counts the number of times a pattern +p+ appears in the string +x+.
#
# Naive implementation that scans the string repeatedly.
#
# @same-contract-as match

# Step I
def match_basic_s1(p, x)
  j, nmatch = 0, 0
  # @let P: nmatch = count i : 0 <= i <= M-N : matchAt(i)
  # @{P} # <- XXX enter in IDE to quickly check initialization, then delete
  while j < x.length - p.length
    # @loop P, @inc j < x.length-p.length
    "check if matchAt(j) is true and increment count" # @TODO
    # @{P.[j->j+1]}
    j += 1
  end # @{P and j >= N-M} => {R}
  return nmatch
end

# Step II
def match_basic(p, x)
  j, nmatch = 0, 0
  # @loop P: nmatch = count i : 0 <= i <= M-N : matchAt(i)
  while j <= x.length - p.length
    # check if matchAt(j) is true and increment count
    k, matches = 0, true
    # @loop Q: all l : 0 <= l < k : p[l] = x[l+j]
    while matches and k < p.length
      matches = false if p[k] != x[k+j]
      k += 1
    end # @{Q and k >= p.length} => matchAt(j)
    nmatch += 1 if matches
    j += 1
  end
  return nmatch
end

# Step II, XXX examples of off-by-one errors to be caught by checker
def match_basic_err(p, x)
  j, nmatch = 0, 0
  # @loop P: nmatch = count i : 0 <= i <= M-N : matchAt(i)
  while j < x.length - p.length # XXX err1 off-by-one error
    # check if matchAt(j) is true and increment count
    k, matches = 0, true
    # @loop Q: all l : 0 <= l < k : p[l] = x[l+j]
    # @loop @dec p.length - k # XXX implicit loop variant, failed by err2
    while matches and k < p.length
      matches = false if p[k] != x[k+j]
      # XXX err2 forgot to increment k
    end # @{Q and k >= p.length} => matchAt(j)
    nmatch += 1 if matches
    j += 1
  end # @{P and j > N-M} => {R} # XXX implicit conclusion, failed by err1
  return nmatch
end
# XXX example of off-by-one error in matchAt() predicate DEFINITION:
# matchAt(i): 0 <= i <= M-N, all j : 0 <= j <= N : p[j] = x[j+i]

##
# Counts the number of times a pattern +p+ appears in the string +x+.
#
# Efficient implementation that scans the string only once.
#
# @same-contract-as match

def match_efficient(p, x)
  # @TODO
end

# Test the above code:

$testcases = [
  ['ababa', 'a', 3],
  ['abbba', 'bb', 2],
  ['ababa', 'aba', 2],
]
def testMatch()
  $testcases.each do |testcase|
    x, p, expected = *testcase
    puts "'#{x}' =~ '#{p}' :: expected #{expected}, got #{yield(p,x)}"
  end
end

puts "match_basic"
testMatch {|p, x| match_basic(p,x)}
