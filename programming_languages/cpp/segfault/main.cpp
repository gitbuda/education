#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <execinfo.h>
#include <iostream>
#include <unistd.h>
#include <vector>

// Example from
// https://stackoverflow.com/questions/77005/how-to-automatically-generate-a-stacktrace-when-my-program-crashes
void handler(int sig) {
  void *array[10];
  size_t size;
  // get void*'s for all entries on the stack
  size = backtrace(array, 10);
  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}
void baz() {
  int *foo = (int *)-1; // make a bad pointer
  printf("%d\n", *foo); // causes segfault
}
void bar() { baz(); }
void foo() { bar(); }

int main() {
  signal(SIGSEGV, handler);
  foo();

  std::vector<int> nums;
  // TODO(gitbuda): Learn more segfaults.
  std::cout << nums[1] << std::endl;
  return 0;
}
