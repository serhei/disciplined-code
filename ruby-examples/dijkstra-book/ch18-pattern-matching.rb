# Example from Chapter 18 of Dijkstra's "A Discipline of Programming".

# Warmup: a naive implementation that scans the string repeatedly.
def count_match_basic(p, x)
  j, nmatch = 0, 0
  while j <= x.length - p.length
    # @inv P: nmatch == count k : 0 <= k < j : matchAt(k)
    # "increment nmatch if matchAt(j) is true":
    k, matches = 0, true
    while matches && k < p.length
      # @inv Q: matches <=> (all l : 0 <= l < k : p[l] == x[l+j])
      matches = false if p[k] != x[k+j]
      k += 1
    end # @{Q and non (matches and k < p.length)} => {matches <=> matchAt(j)}
    nmatch += 1 if matches
    j += 1
  end
  return nmatch
end

def build_lookup_table(p)
  # @require p.length >= 1
  # @returns d
  # @provide Pd: all k : 0 < k <= p.length :
  #    d[k] == min.(l : 1 <= l <= k : pmatch.(p,l,k))
  # @let P4: all j, k: 0 < j <= r, j < k < p.length :
  #    pmatch.(p,j,k) => (k < d.length and d.k <= j)
  d = []; r = 1; s = 1 # @{P4 and pmatch.(p,r,s)}
  # XXX Example error to check: r = 0, s = 0
  while r <= p.length
    # @inv P.4 and pmatch.(p,r,s) and @dec p.length - r
    # XXX Example error to check: while r < p.length
    # increase s as much as possible
    while s < p.length && p[s] == p[s-r]
      # @inv pmatch.(p,r,s)
      # XXX Example error to check: p[s] = p[s-r]
      s += 1
    end
    # extend d to known matches
    while s > d.length-1
      d.append(r)
    end
    # increase r, adjust s under invariance of P4
    r += 1; s = r # the obvious option
    # XXX: The following option is not quite correct, be sure to investigate why:
    # if s-r < d.length
    #   r = r + d[s-r]
    # else
    #   r += 1; s = r
    # end
  end # @{P.4 and r > p.length} => {Pd}
  return d
end

def count_match(p, x)
  # match: (p: String, x:String) -> Integer
  # @require p.length >= 1 and x.length >= 0
  # @returns nmatch
  # @provide R: nmatch == count k : 0 <= k <= last_start : match.k
  # @let last_start: x.length - p.length
  # @let match.k: 0 <= k <= last_start and all j : 0 <= j < p.length : p[j] == x[k+j]

  d = build_lookup_table(p) # @{Pd}

  # @let P1: r >= 0 and nmatch == count k : 0 <= k < r : match.k
  # @let pmatch.(str,r,s): all j : r <= j < s : p[j-r] == x[j]
  # @note (pmatch.(x,r,s) and s - r >= p.length) => match.r
  # @let P2: r <= s and s - r <= N and pmatch.(x,r,s)
  # @note (P2 and s - r >= p.length) => match.r
  nmatch, r, s = 0, 0, 0
  while r <= x.length - p.length && s <= x.length
    # @inv P1 and P2 and Pd and @dec (last_start - r, x.length - s)
    # first, increase s as much as possible under invariance of P1, P2
    while s - r < p.length && x[s] == p[s-r]
      s += 1
    end
    # next, s cannot be increased further; record the match, if any
    if s - r >= p.length
      nmatch += 1
    end
    # next, increase r to restore P1 while preserving P2
    if r < s
      r = r + d[s-r]
      # @{P1 and P2}
    else
      r += 1; s += 1
      # @{r == s} => {P1 and P2}
    end
  end # @{P1 and P2 and (r > last_start or s > x.length)} => {R}

  return nmatch
end

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
testMatch {|p, x| count_match_basic(p,x)}
puts "match_efficient"
testMatch {|p, x| count_match(p,x)}
