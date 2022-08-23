# Find Minimum in Rotated Sorted Array

https://leetcode.com/problems/find-minimum-in-rotated-sorted-array

**Problem Statement.** Suppose an array `nums` of length `n` sorted in
ascending order is rotated between `1` and `n` times. Given the sorted
rotated array `nums` containing unique elements, return the minimum
element of this array. The solution must run in `O.log.n` time.

## Solution

    0: find-min: begin def min, use nums:
      do: {fm-many}="more than one element could be the minimum" ->
        {fm-step}="reduce the range of candidate elements by half"
      :do
      {fm-end}="return the only element in the range"
    :find-min
    
    1a: loc.{find-min} fm-lo var int, fm-hi var int := nums.lob, nums.hib
    1b: inv.{find-min.do} P1: "the minimum element is in nums.(fm-lo..fm-hi)"
    1c: ins.{fm-many} fm-lo < fm-hi
    1d: ins.{fm-end} min var int := nums.fm-lo

The segment `nums.(fm-lo..fm-hi)` can be divided into two parts, with
the upper part starting at the minimum element. Every element in the
(possibly-empty) lower part is greater than every element in the upper
part.

We can determine if the element in the middle of the segment belongs
to the upper part or to the lower part, and therefore whether the
minimum element is located above or below the midpoint.

    2a: {fm-step}:
      loc.{find-min} mid con int := {fm-mid}="midpoint of fm-lo..fm-hi"
      if: nums.mid < nums.fm-hi -> // nums.mid is in the upper part
            {rem-lower}="remove upper half of nums.(fm-lo..fm-hi)"
          nums.mid > nums.fm-hi -> // nums.mid is in the lower part
            {rem-upper}="remove lower half of nums.(fm-lo..fm-hi)"
    :ins
    
    3a: {fm-mid}: (fm-lo + fm-hi) div 2
    3b: post.{fm-mid} fm-lo <= mid < fm-hi
    3c: {rem-lower}: fm-hi := mid
    3d: {rem-upper}: fm-lo := mid+1 [fm-lo <= fm-hi]

## Performance Improvement Ideas

1. Special case: if `nums.fm-lo < nums.fm-hi`, then the minimum
   element is at `fm-lo`.
2. Divide `fm-lo..fm-hi` into three parts rather than two and select
   the third containing the minimum element.
