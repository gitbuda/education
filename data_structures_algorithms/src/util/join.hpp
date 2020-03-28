#include <sstream>
#include <string>
#include <iterator>

namespace dsa::util {

/// Join elements of a container separated by a separator with concluder
/// at the end.
template<typename InputIt>
std::string join(
    InputIt begin,
    InputIt end,
    const std::string &separator = ", ",
    const std::string &concluder = "") {
  std::ostringstream ss;
  using value_type = typename std::iterator_traits<InputIt>::value_type;
  std::copy(
      begin, end, std::ostream_iterator<value_type>(ss, separator.c_str()));
  ss << concluder;
  return ss.str();
}

}// namespace dsa::util
