#include <codecvt>
#include <iomanip>
#include <iostream>
#include <locale>
#include <string>

/**
 * References:
 *   https://www.compart.com/en/unicode
 *   https://www.italiancpp.org/2016/04/20/unicode-localization-and-cpp-support
 *   http://utf8everywhere.org
 *   https://github.com/ThePhD/sol2/issues/571
 *   https://github.com/CppCon/CppCon2014/tree/master/Presentations/Unicode%20in%20C%2B%2B
 */

int main() {
  // Avoids synchronization with C stdio on gcc (either localize both or disable
  // sync).
  std::ios_base::sync_with_stdio(false);

  // // Change default locale.
  std::wcout.imbue(std::locale("en_US.UTF-8"));

  std::array<uint8_t, 5> lion_utf8 = {0xF0, 0x9F, 0xA6, 0x81, 0x00}; // NOLINT

  // Save as string.
  std::string lion_str = std::string(std::begin(lion_utf8), std::end(lion_utf8));
  std::cout << lion_str << " string size: " << lion_str.size() << std::endl;

  // Save as wide string.
  std::wstring_convert<std::codecvt_utf8<wchar_t>> converter_utf8_wchar;
  std::wstring lion_wstr = converter_utf8_wchar.from_bytes(lion_str.c_str());
  std::wcout << lion_wstr << " wstring size: " << lion_wstr.size() << std::endl;

  // Convert from wide string back to string.
  lion_str = converter_utf8_wchar.to_bytes(lion_wstr);
  std::cout << lion_str << std::endl;
}
