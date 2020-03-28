#include <algorithm>
#include <functional>

namespace dsa::sort {

template<class FwdIt, class Compare = std::less<>>
void QuickSort(FwdIt first, FwdIt last, Compare cmp = Compare{}) {
  if (first == last) return;
  auto const pivot = *std::next(first, std::distance(first, last) / 2);
  // Reorders the elements in the range [first, last) in such a way that all
  // elements for which the predicate p returns true precede the elements for
  // which predicate p returns false. Relative order of the elements is not
  // preserved.
  // middle1 iterator to the first element of the second group.
  auto const middle1 = std::partition(
      first, last, [=](auto const &elem) { return cmp(elem, pivot); });
  auto const middle2 = std::partition(
      middle1, last, [=](auto const &elem) { return !cmp(pivot, elem); });
  QuickSort(first, middle1, cmp);
  QuickSort(middle2, last, cmp);
}

} // namespace dsa::sort
