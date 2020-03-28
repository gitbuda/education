#include <catch2/catch.hpp>

#include "bit/operation.hpp"

TEST_CASE("XOR swap") {
  uint32_t first_1 = 10U; // NOLINT
  uint32_t second_1 = 20U; // NOLINT
  auto [first_2, second_2] = dsa::bit::Swap(first_1, second_1);
  REQUIRE(first_1 == second_2);
  REQUIRE(second_1 == first_2);
}

TEST_CASE("The value of lowest set bit in base 10") {
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(0U) == 0);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(1U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(2U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(3U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(4U) == 4);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(5U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(6U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(7U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(8U) == 8);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(9U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(10U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(11U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(12U) == 4);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(13U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(14U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(15U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(16U) == 16);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(17U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(18U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(19U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(20U) == 4);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(21U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(22U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(23U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(24U) == 8);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(25U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(26U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(27U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(28U) == 4);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(29U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(30U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(31U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(32U) == 32);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(33U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(34U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(35U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(36U) == 4);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(37U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(38U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(39U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(40U) == 8);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(41U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(42U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(43U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(44U) == 4);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(45U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(46U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(47U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(48U) == 16);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(49U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(50U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(51U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(52U) == 4);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(53U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(54U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(55U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(56U) == 8);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(57U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(58U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(59U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(60U) == 4);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(61U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(62U) == 2);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(63U) == 1);
  REQUIRE(dsa::bit::LowestSetBitInBase10Value(64U) == 64);
}
