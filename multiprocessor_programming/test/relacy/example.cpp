#include <relacy/relacy_std.hpp>

struct race_test : rl::test_suite<race_test, 2> {
  std::atomic<int> a;
  rl::var<int> x;
  void before() {
    x($) = 0;
    a($) = 0;
  }
  void thread(unsigned thread_index) {
    if (0 == thread_index) {
      x($) = 1;
      a($).store(1, rl::mo_relaxed);
    } else {
      if (1 == a($).load(rl::mo_relaxed))
        x($) = 2;
    }
  }
};

int main() { rl::simulate<race_test>(); }
