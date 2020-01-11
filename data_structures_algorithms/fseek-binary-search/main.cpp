#include <chrono>
#include <cstdio>
#include <filesystem>
#include <iostream>

// TODO: Binary search function.

int main() {
  const int64_t SIZE = 400000;
  int64_t writeArray[SIZE];
  for (int64_t i = 0; i < SIZE; ++i) {
    writeArray[i] = i;
  }
  int64_t readArray[SIZE];

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
  fwrite(writeArray, sizeof(int64_t), SIZE, writeF);
  fclose(writeF);
  std::cout << "writing done" << std::endl;

  // In-memory binary search (read all + search).
  // Read.
  FILE *readF;
  auto startRead = std::chrono::high_resolution_clock::now();
  if ((readF = fopen("test.bin", "rb")) == nullptr) {
    std::cout << "Fail to open read file." << std::endl;
    std::exit(1);
  }
  fread(readArray, sizeof(int64_t), SIZE, readF);
  fclose(readF);
  auto stopRead = std::chrono::high_resolution_clock::now();
  std::cout << "reading done" << std::endl;
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
  auto startSearch = std::chrono::high_resolution_clock::now();
  while (low <= high) {
    iter_no += 1;
    int64_t index = low + (high - low) / 2;
    if (readArray[index] == s) {
      flag = true;
      break;
    } else if (readArray[index] < s) {
      low = index + 1;
    } else {
      high = index - 1;
    }
  }
  auto stopSearch = std::chrono::high_resolution_clock::now();
  std::cout << "Binary search found result in " << iter_no << " iter"
            << std::endl;
  // Test search.
  if (flag != true) {
    std::cerr << "Binary search failed." << std::endl;
  }
  // Print times.
  auto durationRead = std::chrono::duration_cast<std::chrono::microseconds>(
      stopRead - startRead);
  auto durationSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(
      stopSearch - startSearch);
  auto durationTotal = std::chrono::duration_cast<std::chrono::microseconds>(
      stopRead - startRead + stopSearch - startSearch);
  std::cout << "READ   : " << durationRead.count() << "us" << std::endl;
  std::cout << "SEARCH : " << durationSearch.count() << "ns" << std::endl;
  std::cout << "TOTAL  : " << durationTotal.count() << "us" << std::endl;

  // fseek binary search.
  std::cout << std::endl << "fseek binary search" << std::endl;
  auto startReadFBS = std::chrono::high_resolution_clock::now();
  FILE *readFBS;
  if ((readFBS = fopen("test.bin", "rb")) == nullptr) {
    std::cout << "Fail to open read file." << std::endl;
    std::exit(1);
  }
  auto endReadFBS = std::chrono::high_resolution_clock::now();
  int64_t lowFBS = 0;
  int64_t highFBS = SIZE - 1;
  int64_t sFBS = 1;
  bool flagFBS = false;
  int64_t iterNoFBS = 0;
  int64_t valueFBS;
  while (lowFBS <= highFBS) {
    iterNoFBS += 1;
    int64_t index = lowFBS + (highFBS - lowFBS) / 2;
    fseek(readFBS, index * sizeof(int64_t), SEEK_SET);
    fread(&valueFBS, sizeof(int64_t), 1, readFBS);
    if (valueFBS == sFBS) {
      flagFBS = true;
      break;
    } else if (valueFBS < sFBS) {
      lowFBS = index + 1;
    } else {
      highFBS = index - 1;
    }
  }
  auto stopReadFBS = std::chrono::high_resolution_clock::now();
  // Test search.
  if (flagFBS != true) {
    std::cerr << "Binary search failed." << std::endl;
  }
  if (valueFBS != sFBS) {
    std::cerr << "Binary search failed." << std::endl;
  }
  // Print times.
  std::cout << "Binary search found result in " << iterNoFBS << " iter"
            << std::endl;
  auto durationReadFBS = std::chrono::duration_cast<std::chrono::microseconds>(
      stopReadFBS - startReadFBS);
  std::cout << "READFBS : " << durationReadFBS.count() << "us" << std::endl;

  return 0;
}
