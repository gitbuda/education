#include <iostream>
#include <vector>

int main() {
  std::vector<int> nums;
  // TODO(gitbuda): Learn more segfaults.
  std::cout << nums[1] << std::endl;
  return 0;
}
