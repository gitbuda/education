#include <iostream>

// c++17

[[nodiscard]] int StatusInt() {
    return 1;
}

enum class [[nodiscard]] StatusCode {
    Ok,
    Error
};

StatusCode StatusEnum() {
    return StatusCode::Error;
}

int main() {

  StatusInt();
  auto code = StatusInt();
  std::cout << code << std::endl;

  StatusEnum();
  auto status = StatusEnum();
  if (status == StatusCode::Ok) {
      std::cout << "Ok" << std::endl;
  } else {
      std::cout << "Error" << std::endl;
  }

  return 0;
}
