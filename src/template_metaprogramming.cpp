#include <iostream>

using std::cout;
using std::endl;

template <bool Condition, typename THEN, typename ELSE>
class if_;
template <typename THEN, typename ELSE>
struct if_<true, THEN, ELSE> {
  typedef THEN result;
};
template <typename THEN, typename ELSE>
struct if_<false, THEN, ELSE> {
  typedef ELSE result;
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

int main(int argc, char *argv[]) {
  int result = if_<true, THEN, ELSE>::result::func();
  cout << result << endl;
  return 0;
}
