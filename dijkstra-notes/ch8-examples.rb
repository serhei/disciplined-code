# TODO Examples from Chapter 8 of Dijkstra's "A Discipline of Programming".

# Example 1: Maximum of two numbers

# @returns m
# @provide m >= x and m >= y
def max2(x, y)
  return x > y ? x : y
end

# Example 2: Maximum of several numbers

# @require ax.length >= 1
# @returns m
# @provide all i : ax : m >= ax[i]
def maxn(ax)
  i = 1; m = ax[0]
  # @loop P: all j : 0 <= j < i : m >= ax[j]
  while i < ax.length
    m = ax[i] if ax[i] > m
  end
  return m
end

# Slightly more Ruby-like version of the same function.
# Shows some of the problems in adapting predicate notation
# to some of the more compact Ruby idioms.
#
# @use maxn.contract
def maxn_rb(ax)
  m = ax[0]
  # TODO: Need a better way to refer to the progress of ax.each{}:
  # @loop P: all j : each_index : m >= ax[j]
  ax.each { |val| m = val if val > m }
  return m
end
