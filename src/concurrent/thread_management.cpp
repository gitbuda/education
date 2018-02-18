#include <iostream>
#include <thread>

using std::cout;
using std::endl;

// TODO: std::thread can't be initialized with one of overloaded fuctions
//       figure out why
void ThreadWork() { cout << "some work" << endl; }
void ThreadWorkI(int i) { cout << "some work: " << i << endl; }

class BackgroundTask {
 public:
  void operator()() const { ThreadWork(); }
};

struct Func {
  int &i_;
  Func(int &i) : i_(i) {}
  void operator()() {
    for (int j = 0; j < i_; ++j) ThreadWorkI(i_);
  }
};

class ThreadGuard {
 private:
  std::thread &t_;

 public:
  explicit ThreadGuard(std::thread &t) : t_(t) {}
  ~ThreadGuard() {
    if (t_.joinable()) t_.join();
  }
  ThreadGuard(const ThreadGuard &) = delete;
  ThreadGuard &operator=(const ThreadGuard &) = delete;
};

// Test Copy
// std::thread constructor copies arguments into internal storage by default
class TestCopyClass {
 public:
  TestCopyClass() = default;
  TestCopyClass(const TestCopyClass &) {
    std::cout << "Test Copy: [Copy Constructor]" << std::endl;
  }
  // TestCopyClass(TestCopyClass &&) = delete; // -> compile time error
};
class TestCopyWithMoveClass {
 public:
  TestCopyWithMoveClass() = default;
  TestCopyWithMoveClass(const TestCopyWithMoveClass &) {
    std::cout << "[Copy Constructor]" << std::endl;
  }
  TestCopyWithMoveClass(TestCopyWithMoveClass &&) {
    std::cout << "[Move Constructor]" << std::endl;
  }
};
void TestCopyFunc(const TestCopyClass &) {
  std::cout << "Test copy func called." << std::endl;
}
void TestCopyWithMoveFunc(const TestCopyWithMoveClass &) {
  std::cout << "Test copy func called." << std::endl;
}
void TestCopy() {
  TestCopyClass test_copy_obj;
  std::cout << "# Test Copy Case 1" << std::endl;
  std::thread test_copy_thread(TestCopyFunc, test_copy_obj);
  test_copy_thread.join();

  TestCopyWithMoveClass test_copy_with_move_obj;
  std::cout << "# Test Copy Case 2" << std::endl;
  std::thread test_copy_with_move_thread(TestCopyWithMoveFunc,
                                         test_copy_with_move_obj);
  test_copy_with_move_thread.join();
  std::cout << "# Test Copy Case 3" << std::endl;
  std::thread test_copy_with_move_plus_move_thread(
      TestCopyWithMoveFunc, std::move(test_copy_with_move_obj));
  test_copy_with_move_plus_move_thread.join();
}
// https://stackoverflow.com/questions/15990689/stdthread-why-object-is-copied-twice
// Test Copy

int main() {
  std::thread thread1(ThreadWork);

  // NOTE!
  // std::thread thread(BackgroundTask());
  // function declaration, not a start of a new thread!
  std::thread thread2((BackgroundTask()));

  std::thread thread3{BackgroundTask()};
  std::thread thread4([] { ThreadWork(); });

  thread1.join();
  thread2.join();
  thread3.join();
  thread4.join();

  // using RAII to wait for a thread to complete
  int local_var = 5;
  Func func(local_var);
  std::thread thread5(func);
  ThreadGuard g(thread5);

  TestCopy();

  return 0;
}
