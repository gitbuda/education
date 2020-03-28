#include <catch2/catch.hpp>

#include "union_find/quick_find.hpp"
#include "union_find/quick_union.hpp"
#include "union_find/weighted_quick_union.hpp"

template<typename TUnionFind>
void Test(TUnionFind& uf) {
  uf.Union(0, 3); // NOLINT
  REQUIRE(uf.Count() == 8); // NOLINT
  REQUIRE(uf.Connected(0, 3) == true); // NOLINT

  uf.Union(1, 4); // NOLINT
  REQUIRE(uf.Count() == 7); // NOLINT
  REQUIRE(uf.Connected(1, 4) == true); // NOLINT

  uf.Union(3, 4); // NOLINT
  REQUIRE(uf.Count() == 6); // NOLINT
  REQUIRE(uf.Connected(0, 1) == true); // NOLINT
  REQUIRE(uf.Connected(0, 4) == true); // NOLINT
  REQUIRE(uf.Connected(1, 3) == true); // NOLINT

  uf.Union(2, 5); // NOLINT
  REQUIRE(uf.Count() == 5); // NOLINT
  REQUIRE(uf.Connected(2, 5) == true); // NOLINT

  uf.Union(5, 8); // NOLINT
  REQUIRE(uf.Count() == 4); // NOLINT
  REQUIRE(uf.Connected(8, 2) == true); // NOLINT

  uf.Union(4, 7); // NOLINT
  REQUIRE(uf.Count() == 3); // NOLINT
  REQUIRE(uf.Connected(7, 4) == true); // NOLINT
  REQUIRE(uf.Connected(7, 0) == true); // NOLINT
  REQUIRE(uf.Connected(1, 7) == true); // NOLINT
  REQUIRE(uf.Connected(7, 3) == true); // NOLINT

  uf.Union(7, 6); // NOLINT
  REQUIRE(uf.Count() == 2); // NOLINT
  REQUIRE(uf.Connected(7, 6) == true); // NOLINT
  REQUIRE(uf.Connected(6, 1) == true); // NOLINT
  REQUIRE(uf.Connected(6, 0) == true); // NOLINT
  REQUIRE(uf.Connected(6, 3) == true); // NOLINT
  REQUIRE(uf.Connected(6, 4) == true); // NOLINT

  uf.Union(2, 1); // NOLINT
  REQUIRE(uf.Count() == 1); // NOLINT
  REQUIRE(uf.Connected(8, 0) == true); // NOLINT
}

TEST_CASE("Union Find Quick Find") {
  dsa::union_find::QuickFindUnionFind uf(9U); // NOLINT
  Test(uf);
}

TEST_CASE("Union Find Quick Union") {
  dsa::union_find::QuickUnionUnionFind uf(9U); // NOLINT
  Test(uf);
}

TEST_CASE("Union Find Weighted Quick Union") {
  dsa::union_find::WeightedQuickUnionUnionFind uf(9U); // NOLINT
  Test(uf);
}
