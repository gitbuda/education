add_executable(template_function template_function.cpp)
target_link_libraries(
  template_function PRIVATE project_options project_warnings
  CONAN_PKG::docopt.cpp CONAN_PKG::fmt CONAN_PKG::spdlog
  CONAN_PKG::boost_type_index)

add_executable(variant variant.cpp)
target_link_libraries(variant PRIVATE project_options project_warnings)
