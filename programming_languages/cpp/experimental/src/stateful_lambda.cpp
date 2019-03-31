/*
 * Trying stuff from this video: https://www.youtube.com/watch?v=_1X9D8Z5huA
 */

#include <iostream>
#include <memory>

using std::cout;
using std::endl;

int main() {
  // a is taken by copy and isn't mutable
  int a = 1;
  auto simple = [a] { return a; };
  cout << "a: " << a << " "
       << "call: " << simple() << endl;

  // b is taken by reference and is mutable
  int b = 1;
  auto ref_capture = [&b] { return ++b; };
  cout << "b: " << b << " "
       << "call: " << ref_capture() << " "
       << "b: " << b << endl;

  // c is taken by copy and is mutable
  int c = 1;
  auto mutable_var = [c]() mutable { return ++c; };
  cout << "c: " << c << " "
       << "call: " << mutable_var() << " "
       << "c: " << c << endl;

  // create a variable inside capture list, the variable is mutable object
  auto capture_create = [d = 1]() mutable { return ++d; };
  cout << "d: " << capture_create() << " "
       << "d: " << capture_create() << endl;

  // because std::unique_ptr is not copyable the labmda has the same
  // property
  auto non_copy_lambda = [ e = 0, p = std::make_unique<int>(2) ]() mutable {
    return ++e;
  };
  // auto lambda_copy = non_copy_lambda;

  // fibonacci lambda
  auto fibb_lambda = [ i = 0, j = 1 ]() mutable {
    i = std::exchange(j, j + i);
    return i;
  };
  for (int i = 0; i < 10; ++i) {
    cout << fibb_lambda() << " ";
  }
  cout << endl;

  return 0;
}
