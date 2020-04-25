#include <iostream>
#include <string_view>

int main() {
  char str_array[] = "   Test";
  std::cout << str_array << std::endl;

  std::string_view str_view(str_array, std::size(str_array));
  std::cout << str_view << std::endl;

  str_array[3] = 't';
  std::cout << str_view << std::endl;

  // Update only view.
  str_view.remove_prefix(std::min(str_view.find_first_not_of(" "), str_view.size()));
  std::cout << str_view << std::endl;

  std::cout << str_array << std::endl;

  return 0;
}
