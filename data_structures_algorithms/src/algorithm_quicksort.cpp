#include <algorithm>
#include <functional>
#include <vector>

#include "include/using_iostream.hpp"

template <class FwdIt>
void PrintArrayIt(FwdIt first, FwdIt last) {
    for (auto elem = first; elem != last; elem++) {
        Print(*elem, " ");
    }
    Println();
}

template <class FwdIt, class Compare = std::less<>>
void QuickSort(FwdIt first, FwdIt last, Compare cmp = Compare{}) {
    PrintArrayIt(first, last);

    if (first == last) return;
    auto const pivot = *std::next(first, std::distance(first, last) / 2);
    Println("Pivot: ", pivot);

    // Reorders the elements in the range [first, last) in such a way that all
    // elements for which the predicate p returns true precede the elements for
    // which predicate p returns false. Relative order of the elements is not
    // preserved.
    // middle1 iterator to the first element of the second group.
    auto const middle1 = std::partition(
        first, last, [=](auto const& elem) { return cmp(elem, pivot); });
    PrintArrayIt(first, last);

    auto const middle2 = std::partition(
        middle1, last, [=](auto const& elem) { return !cmp(pivot, elem); });
    PrintArrayIt(first, last);

    Println("First: ", *first, " Middle1: ", *middle1);
    Println("Middle2: ", *middle2, " Last: ", *last);

    QuickSort(first, middle1, cmp);
    QuickSort(middle2, last, cmp);
}

int main() {
    std::vector<int> array = {1, 5, 2, 3, 4, 9, 7, 8, 6};

    Println<0>("Quicksort DESC");
    QuickSort<decltype(std::begin(array)), std::greater<>>(std::begin(array),
                                                           std::end(array));
    Println<0>("Quicksort DESC Result");
    PrintArrayIt(std::begin(array), std::end(array));
    Println();
    Println();

    Println<0>("Quicksort ASC");
    QuickSort(std::begin(array), std::end(array));
    Println<0>("Quicksort ASC Result");
    PrintArrayIt(std::begin(array), std::end(array));

    return 0;
}
