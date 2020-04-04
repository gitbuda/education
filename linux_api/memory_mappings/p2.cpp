#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include <thread>

#include "common.hpp"

int main(int argc, char *argv[]) {
  if (argc != 2 || std::strcmp(argv[1], "--help") == 0) {
    Help("Usage ./program_name file_path");
  }

  std::vector<std::uint8_t> pid{'p', '2'};

  std::filesystem::path file(argv[1]);
  int fd = open(file.c_str(), O_RDONLY);
  if (fd == -1) {
    ErrorExit("Failed to open file.");
  }
  void *addr = mmap(NULL, getpagesize(), PROT_READ, MAP_PRIVATE, fd, 0);
  if (addr == MAP_FAILED) {
    ErrorExit("mmap failed.");
  }
  if (close(fd) == -1) {
    ErrorExit("Failed to close file.");
  }

  int cnt = 0;
  while (MemoryRead(addr, pid.size()) != pid) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "p2 still waiting (" << ++cnt << "s) ..." << std::endl;
  }
  std::cout << "p2 read p2 from memory mapped region." << std::endl;

  return 0;
}
