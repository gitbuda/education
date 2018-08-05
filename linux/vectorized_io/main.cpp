#include <chrono>
#include <cstring>
#include <iostream>

#include <unistd.h>

#include <sys/uio.h>

struct Profile {
  std::string name;
  std::chrono::high_resolution_clock::time_point start;
  Profile(const std::string &name)
      : name(name), start(std::chrono::high_resolution_clock::now()) {}
  ~Profile() {
    using duration = std::chrono::duration<double>;
    auto delta = std::chrono::high_resolution_clock::now() - start;
    std::cout << name << " duration: "
              << std::chrono::duration_cast<duration>(delta).count()
              << std::endl;
  }
};

// TODO: write with c primitives
// TODO: take care of the flush before writing
// TODO: write a proper benchmark
// TODO: visualize the results

int main() {
  char str[16384];
  ssize_t nwritten;
  for (int i = 0; i < 16383; ++i) str[i] = 'a';
  str[16383] = '\n';
  FILE *file = fopen("file", "a");
  {
    Profile("write call");
    nwritten = write(fileno(file), str, 16384);
  }
  std::cout << nwritten << std::endl;

  char str0[4096];
  for (int i = 0; i < 4096; ++i) str0[i] = 'a';
  char str1[4096];
  for (int i = 0; i < 4096; ++i) str1[i] = 'a';
  char str2[4096];
  for (int i = 0; i < 4096; ++i) str2[i] = 'a';
  char str3[4096];
  for (int i = 0; i < 4095; ++i) str3[i] = 'a';
  str3[4095] = '\n';
  struct iovec iov[4];
  ssize_t nwrittenv;
  iov[0].iov_base = str0;
  iov[0].iov_len = 4096;
  iov[1].iov_base = str1;
  iov[1].iov_len = 4096;
  iov[2].iov_base = str2;
  iov[2].iov_len = 4096;
  iov[3].iov_base = str3;
  iov[3].iov_len = 4096;
  FILE *filev = fopen("filev", "a");
  {
    Profile("writev call");
    nwrittenv = writev(fileno(filev), iov, 4);
  }
  std::cout << nwrittenv << std::endl;

  return 0;
}
