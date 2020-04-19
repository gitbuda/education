#include <string>
#include <map>
#include <utility>

#include <fmt/format.h>

namespace util {

class Table {
public:
  void Add(const std::string &row, const std::string &col, const std::string &value) {
    table_.emplace(std::make_pair(row, col), value);
  }

  const std::string &At(const std::string &row, const std::string &col) const {
    return table_.at(std::make_pair(row, col));
  }

private:
  std::map<std::pair<std::string, std::string>, std::string> table_;
};


std::string RanderRow(const std::vector<std::string> &row, const std::string &delimiter = ",") {
  return fmt::format("{}", fmt::join(row, delimiter));
}

std::string RenderTableRow(
    const std::vector<std::string> &header,
    const std::string &row_selector,
    const Table &table,
    const std::string &delimiter = ",") {
  std::vector<std::string> row;
  row.reserve(header.size());
  for (const auto &col_selector : header) {
    const auto &cell = table.At(row_selector, col_selector);
    row.emplace_back(cell);
  }
  return RanderRow(row, delimiter);
}

} // namespace util
