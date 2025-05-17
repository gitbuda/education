#include "signal.h"
#include <vector>
#include <iostream>

// TODO(gitbuda): Try to make the following work on x86_64
// https://feepingcreature.github.io/handling.html

void seghandle_userspace() {
  *(int*) NULL = 0;
}

// TODO(gitbuda): Make it complete and correct.
enum X86Registers {
  RSP = 15,
  RIP = 16,
};

void seghandle(int sig, siginfo_t* si, void* unused) {
  ucontext_t* uc = (ucontext_t*) unused;
  auto gregs = uc->uc_mcontext.gregs;
  void* eip = (void*) gregs[X86Registers::RIP];
  void** esp = (void**) gregs[X86Registers::RSP];
  esp --;
  *esp = eip;
  eip = (void*) &seghandle_userspace;
}

void setup_segfault_handler() {
  struct sigaction sa;
  sa.sa_flags = SA_SIGINFO;
  sigemptyset (&sa.sa_mask);
  sa.sa_sigaction = &seghandle;
  if (sigaction(SIGSEGV, &sa, NULL) == -1) {
    fprintf(stderr, "failed to setup SIGSEGV handler\n");
    std::exit(1);
  }
}

int main() {
  // TODO(gitbuda): The program hangs figure out why :thinking:
  setup_segfault_handler();
  std::vector<int> nums;
  std::cout << nums[1] << std::endl;
  return 0;
}
