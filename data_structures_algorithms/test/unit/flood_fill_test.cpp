#include <catch2/catch.hpp>

#include "traverse/flood_fill.hpp"

TEST_CASE("Flood fill traversal") {
  dsa::traverse::Graph graph = {
      {1U}, {0U, 2U, 3U, 4U}, {1U}, {1U}, {1U}, {6U}, {5U}}; // NOLINT

  dsa::traverse::Visited visited_0 = {
      false, false, false, false, false, false, false};
  // NOLINTNEXTLINE
  dsa::traverse::FloodFill(graph, visited_0, 0U, [](int) { /* Pass. */ });
  REQUIRE(
      visited_0
      == dsa::traverse::Visited{
             true,
             true,
             true,
             true,
             true,
             false,
             false,
         });

  dsa::traverse::Visited visited_1 = {
      false, false, false, false, false, false, false};
  // NOLINTNEXTLINE
  dsa::traverse::FloodFill(graph, visited_1, 1U, [](int) { /* Pass. */ });
  REQUIRE(
      visited_1
      == dsa::traverse::Visited{
             true,
             true,
             true,
             true,
             true,
             false,
             false,
         });

  dsa::traverse::Visited visited_2 = {
      false, false, false, false, false, false, false};
  // NOLINTNEXTLINE
  dsa::traverse::FloodFill(graph, visited_2, 2U, [](int) { /* Pass. */ });
  REQUIRE(
      visited_2
      == dsa::traverse::Visited{
             true,
             true,
             true,
             true,
             true,
             false,
             false,
         });

  dsa::traverse::Visited visited_3 = {
      false, false, false, false, false, false, false};
  // NOLINTNEXTLINE
  dsa::traverse::FloodFill(graph, visited_3, 3U, [](int) { /* Pass. */ });
  REQUIRE(
      visited_3
      == dsa::traverse::Visited{
             true,
             true,
             true,
             true,
             true,
             false,
             false,
         });

  dsa::traverse::Visited visited_4 = {
      false, false, false, false, false, false, false};
  // NOLINTNEXTLINE
  dsa::traverse::FloodFill(graph, visited_4, 4U, [](int) { /* Pass. */ });
  REQUIRE(
      visited_4
      == dsa::traverse::Visited{
             true,
             true,
             true,
             true,
             true,
             false,
             false,
         });

  dsa::traverse::Visited visited_5 = {
      false, false, false, false, false, false, false};
  // NOLINTNEXTLINE
  dsa::traverse::FloodFill(graph, visited_5, 5U, [](int) { /* Pass. */ });
  REQUIRE(
      visited_5
      == dsa::traverse::Visited{
             false,
             false,
             false,
             false,
             false,
             true,
             true,
         });

  dsa::traverse::Visited visited_6 = {
      false, false, false, false, false, false, false};
  // NOLINTNEXTLINE
  dsa::traverse::FloodFill(graph, visited_6, 6U, [](int) { /* Pass. */ });
  REQUIRE(
      visited_6
      == dsa::traverse::Visited{
             false,
             false,
             false,
             false,
             false,
             true,
             true,
         });
}
