#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <vector>

#include <unistd.h>

#include <sys/uio.h>

struct Profile {
  std::string name;
  std::chrono::high_resolution_clock::time_point start;
  Profile(const std::string &name)
      : name(name), start(std::chrono::high_resolution_clock::now()) {}
  auto Delta() {
    using duration = std::chrono::duration<double>;
    auto delta = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<duration>(delta).count();
  }
  ~Profile() {
    using duration = std::chrono::duration<double>;
    auto delta = std::chrono::high_resolution_clock::now() - start;
    std::cout << name << " duration: "
              << std::chrono::duration_cast<duration>(delta).count()
              << std::endl;
  }
};

// TODO: write Profile that is going to be aware of iterations
// TODO: take care of the flush before writing
// TODO: write a proper benchmark
// TODO: visualize the results
// TODO: use smart pointers

auto profile_write(int length) {
  std::vector<char> str(length, 'a');
  FILE *file = fopen("file", "a");
  ssize_t nwritten;
  double duration;
  {
    Profile profile("write call");
    nwritten = write(fileno(file), &str.front(), str.size());
    duration = profile.Delta();
  }
  std::cout << nwritten << std::endl;
  return duration;
}

auto profile_writev(const std::vector<int> &lenghts) {
  std::vector<struct iovec> buffers(lenghts.size());
  for (auto i = 0; i < lenghts.size(); ++i) {
    char *str = new char[lenghts[i]];
    for (auto i = 0; i < lenghts[i]; ++i) str[i] = 'a';
    buffers[i].iov_base = str;
    buffers[i].iov_len = lenghts[i];
  }
  ssize_t nwrittenv;
  FILE *filev = fopen("filev", "a");
  double duration;
  {
    Profile profile("writev call");
    nwrittenv = writev(fileno(filev), &buffers.front(), lenghts.size());
    duration = profile.Delta();
  }
  std::cout << nwrittenv << std::endl;
  for (int i = 0; i < lenghts.size(); ++i) {
    delete[] static_cast<char *>(buffers[i].iov_base);
  }
  return duration;
}

template <typename T>
auto median(T &v) {
  size_t n = v.size() / 2;
  nth_element(v.begin(), v.begin() + n, v.end());
  return v[n];
}

int main() {
  int niterations = 10;
  int length = 65536;
  std::vector<int> lenghts = {16384, 16384, 16384, 16384};
  std::vector<double> write_durations;
  std::vector<double> writev_durations;
  for (int i = 0; i < niterations; ++i) {
    write_durations.push_back(profile_write(length));
    writev_durations.push_back(profile_writev(lenghts));
  }
  auto write_median = median(write_durations);
  auto writev_median = median(writev_durations);
  std::cout << "Write duration median: " << write_median << std::endl;
  std::cout << "Writev duration median: " << writev_median << std::endl;
  return 0;
}
