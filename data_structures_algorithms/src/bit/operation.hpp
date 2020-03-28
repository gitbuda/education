#include <type_traits>
#include <tuple>

namespace dsa::bit {

template<typename T>
constexpr auto LowestSetBitInBase10Value(T x) {
  static_assert(std::is_unsigned<T>::value, "Has to be unsigned.");
  return x & -x;
}

template<typename T>
constexpr auto Swap(T x, T y) {
  x = x ^ y;
  y = y ^ x;
  x = x ^ y;
  return std::make_tuple(x, y);
}

} // namespace dsa::bit
