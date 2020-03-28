#include <catch2/catch.hpp>

#include "sort/quick_sort.hpp"

TEST_CASE("Quick sort") {
  std::vector<int> items = {1, 5, 2, 3, 4, 9, 7, 8, 6}; // NOLINT

  // Test sorting DESC.
  dsa::sort::QuickSort<decltype(std::begin(items)), std::greater<>>(
      std::begin(items), std::end(items));
  REQUIRE(items == std::vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}); // NOLINT

  // Test sorting ASC.
  dsa::sort::QuickSort(std::begin(items), std::end(items));
  REQUIRE(items == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}); // NOLINT
}
