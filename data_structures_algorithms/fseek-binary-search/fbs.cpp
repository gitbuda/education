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

  // fseek binary search.
  auto startReadFBS = std::chrono::high_resolution_clock::now();
  FILE *readFBS;
  if ((readFBS = fopen("test.bin", "rb")) == nullptr) {
    std::cout << "Fail to open read file." << std::endl;
    std::exit(1);
  }
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
  auto durationReadFBS = std::chrono::duration_cast<std::chrono::nanoseconds>(
      stopReadFBS - startReadFBS);
  std::cout << durationReadFBS.count() << std::endl;

  return 0;
}
