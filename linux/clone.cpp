/**
 * References:
 * https://eli.thegreenplace.net/2018/launching-linux-threads-and-processes-with-clone
 * http://man7.org/linux/man-pages/man2/clone.2.html
 * http://man7.org/linux/man-pages/man2/waitpid.2.html
 */

#include <sched.h>
#include <sys/wait.h>

#include <cstdlib>
#include <cstring>
#include <iostream>

static int task(void* arg) {
  char* data = reinterpret_cast<char*>(arg);
  std::cout << "Child sees buf = " << std::string(data) << std::endl;
  std::strcpy(data, "hello from child");
  return 0;
}

static void bad_exit(std::string msg) {
  std::cerr << msg << std::endl;
  std::exit(1);
}

static void wait_for_change(char* buf) {
  int status;
  if (wait(&status) == -1) {
    bad_exit("wait failed");
  }
  printf("Child exited with status %d. buf = \"%s\"\n", status, buf);
}

int main() {
  const int STACK_SIZE = 65536;
  char* stack = static_cast<char*>(std::malloc(STACK_SIZE));

  if (!stack) bad_exit("malloc failed");

  char buf[100];
  std::strcpy(buf, "hello from parent");

  // Start a new "process".
  std::cout << "Starting a new \"process\"..." << std::endl;
  // Stacks grow downward on all processors that run Linux (except the HP PA
  // processors), so child_stack usually points to the topmost address of the
  // memory space set up for the child stack.
  if (clone(task, stack + STACK_SIZE, SIGCHLD, buf) == -1)
    bad_exit("clone failed");
  wait_for_change(buf);

  // Start a new "thread" (pthread_create uses .
  std::cout << "Starting a new \"thread\"..." << std::endl;
  if (clone(task, stack + STACK_SIZE, CLONE_VM | SIGCHLD, buf) == -1)
    bad_exit("clone failed");
  wait_for_change(buf);

  return 0;
}
