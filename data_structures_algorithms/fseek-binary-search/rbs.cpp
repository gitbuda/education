#include <chrono>
#include <cstdio>
#include <filesystem>
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "The first and only argument should be array size."
              << std::endl;
    std::exit(1);
  }
  const int64_t SIZE = std::stoll(argv[1]);
  std::vector<int64_t> writeArray(SIZE);
  for (int64_t i = 0; i < SIZE; ++i) {
    writeArray[i] = i;
  }
  std::vector<int64_t> readArray(SIZE);

  // Remove test file if it's there.
  if (std::filesystem::exists("test.bin")) {
    std::filesystem::remove("test.bin");
  }

  // Writing.
  FILE *writeF;
  if ((writeF = fopen("test.bin", "w")) == nullptr) {
    std::cout << "Fail to open write file." << std::endl;
    std::exit(1);
  }
  fwrite(writeArray.data(), sizeof(int64_t), SIZE, writeF);
  fclose(writeF);

  // In-memory binary search (read all + search).
  // Read.
  FILE *readF;
  auto startRead = std::chrono::high_resolution_clock::now();
  if ((readF = fopen("test.bin", "rb")) == nullptr) {
    std::cout << "Fail to open read file." << std::endl;
    std::exit(1);
  }
  fread(readArray.data(), sizeof(int64_t), SIZE, readF);
  fclose(readF);
  auto stopRead = std::chrono::high_resolution_clock::now();
  // Test read.
  for (int64_t i = 0; i < SIZE; ++i) {
    if (readArray[i] != writeArray[i]) {
      std::cerr << "Array do not match." << std::endl;
      std::exit(1);
    }
  }
  // Search.
  int64_t low = 0;
  int64_t high = SIZE - 1;
  int64_t s = 1;
  bool flag = false;
  int64_t iter_no = 0;
  int64_t value;
  auto startSearch = std::chrono::high_resolution_clock::now();
  while (low <= high) {
    iter_no += 1;
    int64_t index = low + (high - low) / 2;
    value = readArray[index];
    if (value == s) {
      flag = true;
      break;
    } else if (value < s) {
      low = index + 1;
    } else {
      high = index - 1;
    }
  }
  auto stopSearch = std::chrono::high_resolution_clock::now();
  // Test search.
  if (flag != true) {
    std::cerr << "Binary search failed." << std::endl;
    std::exit(1);
  }
  if (value != s) {
    std::cerr << "Binary search failed." << std::endl;
    std::exit(1);
  }
  // Print times.
  auto durationRead = std::chrono::duration_cast<std::chrono::nanoseconds>(
      stopRead - startRead);
  auto durationSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(
      stopSearch - startSearch);
  std::cout << durationRead.count() << "," << durationSearch.count()
            << std::endl;

  return 0;
}
