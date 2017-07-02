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
    for (int j = 0; j < 100000; ++j) ThreadWorkI(i_);
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

int main() {
  std::thread thread1(ThreadWork);
  // function declaration, not a start of a new thread!
  // std::thread thread(BackgroundTask());
  std::thread thread2((BackgroundTask()));
  std::thread thread3{BackgroundTask()};
  std::thread thread4([] { ThreadWork(); });

  thread1.join();
  thread2.join();
  thread3.join();
  thread4.join();

  // using RAII to wait for a thread to complete
  int local_var = 0;
  Func func(local_var);
  std::thread thread5(func);
  ThreadGuard g(thread5);
  // do something in current thread

  return 0;
}
