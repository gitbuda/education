#include <string>
#include <utility>
#include <iostream>

#include <boost/type_index.hpp>
#include <spdlog/spdlog.h>

#include "util/table.hpp"

using boost::typeindex::type_id_with_cvr;

template<typename T>
std::pair<std::string, std::string> T_T(T param) {
  return {type_id_with_cvr<T>().pretty_name(), type_id_with_cvr<decltype(param)>().pretty_name()};
}

template<typename T>
std::pair<std::string, std::string> T_Tr(T &param) {
  return {type_id_with_cvr<T>().pretty_name(), type_id_with_cvr<decltype(param)>().pretty_name()};
}

template<typename T>
std::pair<std::string, std::string> T_Trr(T &&param) {
  return {type_id_with_cvr<T>().pretty_name(), type_id_with_cvr<decltype(param)>().pretty_name()};
}

template<typename T>
std::pair<std::string, std::string> T_cT(const T param) {
  return {type_id_with_cvr<T>().pretty_name(), type_id_with_cvr<decltype(param)>().pretty_name()};
}

template<typename T>
std::pair<std::string, std::string> T_cTr(const T &param) {
  return {type_id_with_cvr<T>().pretty_name(), type_id_with_cvr<decltype(param)>().pretty_name()};
}

template<typename T>
std::pair<std::string, std::string> T_cTrr(const T &&param) {
  return {type_id_with_cvr<T>().pretty_name(), type_id_with_cvr<decltype(param)>().pretty_name()};
}

int main([[maybe_unused]] int argc, [[maybe_unused]] const char **argv) {
  spdlog::info("Cpp Type Deduction Template Function");

  util::Table table;

  std::string delimiter = ",";
  std::string T_T_col = "<T>f(T param)";
  std::string T_Tr_col = "<T>f(T& param)";
  std::string T_Trr_col = "<T>f(T&& param)";
  std::string T_cT_col = "<T>f(const T param)";
  std::string T_cTr_col = "<T>f(const T& param)";
  std::string T_cTrr_col = "<T>f(const T&& param)";
  std::vector<std::string> header = {T_T_col, T_cT_col, T_Tr_col, T_cTr_col, T_Trr_col, T_cTrr_col};
  std::string cell = "T={}; param={}";

  std::string i_row = "int";
  int i = 1;
  table.Add(i_row, T_T_col, fmt::format(cell, T_T(i).first, T_T(i).second));
  table.Add(i_row, T_Tr_col, fmt::format(cell, T_Tr(i).first, T_Tr(i).second));
  table.Add(i_row, T_Trr_col, fmt::format(cell, T_Trr(i).first, T_Trr(i).second));
  table.Add(i_row, T_cT_col, fmt::format(cell, T_cT(i).first, T_cT(i).second));
  table.Add(i_row, T_cTr_col, fmt::format(cell, T_cTr(i).first, T_cTr(i).second));
  table.Add(i_row, T_cTrr_col, fmt::format("{}", "no known conversion"));

  std::string ci_row = "const int";
  const int ci = 1;
  table.Add(ci_row, T_T_col, fmt::format(cell, T_T(ci).first, T_T(ci).second));
  table.Add(ci_row, T_Tr_col, fmt::format(cell, T_Tr(ci).first, T_Tr(ci).second));
  table.Add(ci_row, T_Trr_col, fmt::format(cell, T_Trr(ci).first, T_Trr(ci).second));
  table.Add(ci_row, T_cT_col, fmt::format(cell, T_cT(ci).first, T_cT(ci).second));
  table.Add(ci_row, T_cTr_col, fmt::format(cell, T_cTr(ci).first, T_cTr(ci).second));
  table.Add(ci_row, T_cTrr_col, fmt::format("{}", "no known conversion"));

  std::string ir_row = "int&";
  int &ir = i;
  table.Add(ir_row, T_T_col, fmt::format(cell, T_T(ir).first, T_T(ir).second));
  table.Add(ir_row, T_Tr_col, fmt::format(cell, T_Tr(ir).first, T_Tr(ir).second));
  table.Add(ir_row, T_Trr_col, fmt::format(cell, T_Trr(ir).first, T_Trr(ir).second));
  table.Add(ir_row, T_cT_col, fmt::format(cell, T_cT(ir).first, T_cT(ir).second));
  table.Add(ir_row, T_cTr_col, fmt::format(cell, T_cTr(ir).first, T_cTr(ir).second));
  table.Add(ir_row, T_cTrr_col, fmt::format("{}", "no known conversion"));

  std::string cir_row = "const int&";
  const int &cir = 1;
  table.Add(cir_row, T_T_col, fmt::format(cell, T_T(cir).first, T_T(cir).second));
  table.Add(cir_row, T_Tr_col, fmt::format(cell, T_Tr(cir).first, T_Tr(cir).second));
  table.Add(cir_row, T_Trr_col, fmt::format(cell, T_Trr(cir).first, T_Trr(cir).second));
  table.Add(cir_row, T_cT_col, fmt::format(cell, T_cT(cir).first, T_cT(cir).second));
  table.Add(cir_row, T_cTr_col, fmt::format(cell, T_cTr(cir).first, T_cTr(cir).second));
  table.Add(cir_row, T_cTrr_col, fmt::format("{}", "no known conversion"));

  std::string irr_row = "int&&";
  int &&irr = 1;
  table.Add(irr_row, T_T_col, fmt::format(cell, T_T(irr).first, T_T(irr).second));
  table.Add(irr_row, T_Tr_col, fmt::format(cell, T_Tr(irr).first, T_Tr(irr).second));
  table.Add(irr_row, T_Trr_col, fmt::format(cell, T_Trr(irr).first, T_Trr(irr).second));
  table.Add(irr_row, T_cT_col, fmt::format(cell, T_cT(irr).first, T_cT(irr).second));
  table.Add(irr_row, T_cTr_col, fmt::format(cell, T_cTr(irr).first, T_cTr(irr).second));
  table.Add(irr_row, T_cTrr_col, fmt::format("{}", "no known conversion"));

  std::string cirr_row = "const int&&";
  int &&cirr = 1;
  table.Add(cirr_row, T_T_col, fmt::format(cell, T_T(cirr).first, T_T(cirr).second));
  table.Add(cirr_row, T_Tr_col, fmt::format(cell, T_Tr(cirr).first, T_Tr(cirr).second));
  table.Add(cirr_row, T_Trr_col, fmt::format(cell, T_Trr(cirr).first, T_Trr(cirr).second));
  table.Add(cirr_row, T_cT_col, fmt::format(cell, T_cT(cirr).first, T_cT(cirr).second));
  table.Add(cirr_row, T_cTr_col, fmt::format(cell, T_cTr(cirr).first, T_cTr(cirr).second));
  table.Add(cirr_row, T_cTrr_col, fmt::format("{}", "no known conversion"));

  std::cout << "Type" << delimiter << util::RanderRow(header) << std::endl;
  std::cout << i_row << delimiter << util::RenderTableRow(header, i_row, table) << std::endl;
  std::cout << ci_row << delimiter << util::RenderTableRow(header, ci_row, table) << std::endl;
  std::cout << ir_row << delimiter << util::RenderTableRow(header, ir_row, table) << std::endl;
  std::cout << cir_row << delimiter << util::RenderTableRow(header, cir_row, table) << std::endl;
  std::cout << irr_row << delimiter << util::RenderTableRow(header, irr_row, table) << std::endl;
  std::cout << cirr_row << delimiter << util::RenderTableRow(header, cirr_row, table) << std::endl;

  return 0;
}
