#include <catch2/catch.hpp>

#include "util/table.hpp"

TEST_CASE("Util", "Table") {
  util::Table table;
  table.Add("1", "2", "3");
  REQUIRE(table.At("1", "2") == "3");
}
