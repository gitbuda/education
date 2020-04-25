#include <iostream>

using std::cout;
using std::endl;

template<bool Condition, typename THEN, typename ELSE>
struct if_;
template<typename THEN, typename ELSE>
struct if_<true, THEN, ELSE> {
  using result = THEN;
};
template<typename THEN, typename ELSE>
struct if_<false, THEN, ELSE> {
  using result = ELSE;
};

struct THEN {
  static int func() {
    cout << "inside then" << endl;
    return 1;
  }
};

struct ELSE {
  static int func() {
    cout << "inside else" << endl;
    return 0;
  }
};

int main() {
  int result = if_<true, THEN, ELSE>::result::func();
  cout << result << endl;
  return 0;
}
