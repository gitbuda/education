/**
 * Starting point:
 * https://vorpus.org/blog/notes-on-structured-concurrency-or-go-statement-considered-harmful
 *
 * The idea is to provide an implementation in C++
 */

#include <functional>
#include <iostream>
#include <thread>
#include <vector>

// TODO(gitbuda): Implement generic StartSoon method.
// TODO(gitbuda): Find a way how to disable direct access to threads.

class Nursery {
public:
  Nursery() = default;
  Nursery(const Nursery &) = default;
  Nursery(Nursery &&) = default;
  Nursery &operator=(const Nursery &) = default;
  Nursery &operator=(Nursery &&) = default;

  void StartSoon(const std::function<void()> &task) { tasks.emplace_back(std::thread(task)); }

  ~Nursery() {
    for (auto &task : tasks) {
      if (task.joinable()) { task.join(); }
    }
  }

private:
  std::vector<std::thread> tasks;
};

int main() {
  {
    Nursery nursery;
    for (int i = 0; i < 10; ++i) { // NOLINT
      nursery.StartSoon([i]() { std::cout << "Task " << i << std::endl; });
    }
  }
  std::cout << "DONE" << std::endl;
  return 0;
}
