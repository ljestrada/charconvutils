# charconvutils
C++17 sports two low-level character conversion functions, [std::from_chars](https://en.cppreference.com/w/cpp/utility/from_chars) and  [std::to_chars](https://en.cppreference.com/w/cpp/utility/to_chars), but they have a usage model that can be easily improved using the power of templates.

charconvutils provides a set of function templates that wrap `std::from_chars` and `std::to_chars` functions, but provides additional flexibility for C-style strings, requiring to pass only the array. Furthermore, standard containers that maintain their elements in contigious storage and provide a `data()` member function are supported, too.
## Requirements
charconvutils requires a C++17 compliant compiler with support for character conversion.

## Examples
The following example illustrates using charconvutils with regular C-style strings and if with initialization.
```C++
#include "charconvutils.hpp"

int main() {
  char const a[] = "8675309";
  long value;

  if (auto [ptr, ec] = charconvutils::from_chars(a, value); ec != std::errc{}) {
    // CONVERSION FAILED
  }

  char buffer[8];
  long input{8675309};

  if (auto [ptr, ec] = charconvutils::to_chars(buffer, input); ec != std::errc{}) {
    // CONVERSION FAILED
  }
}
```
