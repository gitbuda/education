#include <cppcoro/task.hpp>
#include <cppcoro/sync_wait.hpp>
#include <cppcoro/generator.hpp>
#include <iostream>

// https://en.cppreference.com/w/cpp/language/coroutines
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1056r0.html
// https://github.com/lewissbaker/cppcoro
// https://github.com/facebook/folly/tree/master/folly/experimental/coro
// https://www.youtube.com/watch?v=1Wy5sq3s2rg

cppcoro::task<std::string> co_task_f() {
  co_return "co_return executed.";
}

/// This function is required because
/// 'co_await' cannot be used in the 'main' function.
cppcoro::task<> co_task_usage() {
  auto coro_task = co_task_f();
  std::cout << "I have the task..." << std::endl;
  std::cout << co_await coro_task << std::endl;
}

cppcoro::generator<std::uint64_t> fibonacci() {
  std::uint64_t a = 0, b = 1;
  while (true) {
    co_yield b;
    auto tmp = a;
    a = b;
    b += tmp;
  }
}

int main() {
  // Task.
  cppcoro::sync_wait(co_task_usage());

  // Generator.
  for (auto i : fibonacci()) {
    if (i > 1'000'000) break;
    std::cout << i << std::endl;
  }

  return 0;
}
