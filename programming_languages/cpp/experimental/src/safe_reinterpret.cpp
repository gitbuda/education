#include <iostream>

// From Modern C++ Design

// template<bool>
// struct CompileTimeChecker
// {
//
// };
//
// template<> struct CompileTimeChecker<false> {};
//
// template <class To, class From>
// To safe_reinterpret_cast(From from) {
//   {
//     class ERROR_Destination_Type_Too_Narrow {};
//     void sizeof(CompileTimeChecker<(sizeof(From) <= sizeof(To))>(
//         ERROR_Destination_Type_Too_Narrow()));
//   }
//   return reinterpret_cast<To>(from);
// }

// TODO: make static assert
template <class From, class To>
To safe_reinterpret_cast(From from) {
  static_assert(sizeof(From) <= sizeof(To), "Destination type too narrow");
  return reinterpret_cast<To>(from);
}

int main() {
  using From = uint32_t;
  using To = uint16_t;
  std::cout << "sizeof(From): " << sizeof(From) << std::endl;
  std::cout << "sizeof(To): " << sizeof(To) << std::endl;
  From *x = new From(100000000);
  auto y = safe_reinterpret_cast<From *, To *>(x);
  std::cout << "x: " << *x << std::endl;
  std::cout << "y: " << *y << std::endl;
  return 0;
}
