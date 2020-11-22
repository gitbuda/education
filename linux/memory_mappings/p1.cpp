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

  std::vector<std::uint8_t> pid{'p', '1'};

  std::filesystem::path file(argv[1]);
  int fd = open(file.c_str(), O_RDWR);
  if (fd == -1) { ErrorExit("Failed to open file."); }
  void *addr =
      mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (addr == MAP_FAILED) { ErrorExit("mmap failed."); }
  if (close(fd) == -1) { ErrorExit("Failed to close file."); }

  MemoryWrite(addr, {'p', '2'});
  if (msync(addr, 2, MS_SYNC) == -1) { ErrorExit("Failed to open file."); }
  std::this_thread::sleep_for(std::chrono::seconds(1));

  return 0;
}
