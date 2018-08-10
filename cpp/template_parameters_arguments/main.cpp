#include <iostream>
#include <vector>

// References:
//   https://stackoverflow.com/questions/213761/what-are-some-uses-of-template-template-parameters
//   TODO: Test policy based design with template template parameters.

// Template template parameter.
//                                         |--> since C++17
template <template <typename, typename> typename TContainer, typename TType,
          typename TAllocator>
void f1(TContainer<TType, TAllocator>& container) {
  TType tmp = container.back();
  std::cout << tmp << std::endl;
}
// Not very useful any more because of auto.
template <typename TContainer>
void f2(TContainer& container) {
  auto tmp = container.back();
  std::cout << tmp << std::endl;
}

// There is no stream output operators for standard containers, but ...
template <template <typename, typename...> typename C, typename T,
          typename... Args>
std::ostream& operator<<(std::ostream& os, const C<T, Args...>& objs) {
  os << __PRETTY_FUNCTION__ << '\n';
  for (auto const& obj : objs) {
    os << obj << ' ';
  }
  return os;
}

int main() {
  std::vector<int> container(1, 1);
  f1(container);
  f2(container);
  std::cout << container << '\n';
  return 0;
}
