#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

void Help(const std::string &message) {
  std::cout << message << std::endl;
  std::exit(1);
}

void ErrorExit(const std::string &message) {
  std::cerr << message << std::endl;
  std::exit(1);
}

void FileWrite(
    const std::filesystem::path &path,
    const std::vector<std::uint8_t> &data) {
  assert(data.size() > 0);
  std::ofstream file(path, std::ios_base::binary);
  assert(file.is_open());
  file.write(
      reinterpret_cast<const char *>(data.data()),
      data.size() * sizeof(data[0]));
  file.close();
}

std::vector<std::uint8_t> FileRead(const std::filesystem::path &path) {
  std::ifstream file(path, std::ios::in | std::ios::binary);
  std::vector<std::uint8_t> data(
      (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  return data;
}

void MemoryWrite(void *start_addr, const std::vector<std::uint8_t> &data) {
  assert(data.size() > 0);
  std::memcpy(start_addr, data.data(), data.size() * sizeof(data[0]));
}

std::vector<std::uint8_t> MemoryRead(void *start_addr, std::size_t length) {
  std::vector<uint8_t> data(length, '\n');
  std::memcpy(data.data(), start_addr, length);
  return data;
}
