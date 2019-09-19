# charconvutils
C++17 sports two low-level character conversion functions, [std::from_chars](https://en.cppreference.com/w/cpp/utility/from_chars) and  [std::to_chars](https://en.cppreference.com/w/cpp/utility/to_chars), but they have a usage model that can be easily improved using the power of templates.

charconvutils provides a set of function templates that wrap `std::from_chars` and `std::to_chars` functions, but provides additional flexibility for C-style strings, requiring to pass only the array. Furthermore, standard containers that maintain their elements in contigious storage and provide a `data()` member function are supported, too.
## Requirements
charconvutils requires a C++17 compliant compiler with support for character conversion.

## Examples
The following examples illustrates different usage scenarios.  Notice that similar to `std::to_chars`, `charconvutils::to_chars` will return a non-NTBS (null-terminated byte stream). If the conversion succeeds and it will be used in a scenario that requires a NTBS, you can use any of the following techniques.
* Overallocate the output buffer by one (or more) elements and fill the buffer with `'\0'`. This is useful when you have a very good idea how many bytes will be needed to hold the result.
*  Terminate the output buffer by setting the `ptr` member of the resulting `std::to_chars_result` to `'\0'` as follows: `*result.ptr = '\0'`.
* Use a container with a small number of elements and loop, incrementing its size until the conversion succeeds.

### Using C-style strings
The following example illustrates using charconvutils with regular C-style strings, it makes use of the if with initialization and structured bindings features present in C++17.
Notice that the `buffer` array is initialized with `'\0'`s and has an extra character to guarantee a NTBS after a successful call to `charconvutils::to_chars`.  

```C++
#include "charconvutils.hpp"

int main() {
  char const a[] = "8675309";
  unsigned int value;

  if (auto [ptr, ec] = charconvutils::from_chars(a, value); ec != std::errc{}) {
    // CONVERSION FAILED
  }

  char buffer[8] {}; // Initialize with '\0's.
  unsigned int input{8675309};

  if (auto [ptr, ec] = charconvutils::to_chars(buffer, input); result.ec != std::errc{}) {
    // CONVERSION FAILED
  }
}
```
### Using std::array
The following example illustrates using charconvutils to place the result of the conversion in a `std::array`.
Notice that the `buffer` `std::array` is initialized with `'\0'`s and has an extra character to guarantee a NTBS after a successful call to `charconvutils::to_chars`. 
```C++
#include "charconvutils.hpp"
#include <array>

int main() {
  std::array<char, 7> a{ '8', '6', '7', '5', '3', '0', '9' };
  unsigned int value;

  if (auto [ptr, ec] = charconvutils::from_chars(a, value); ec != std::errc{}) {
    // CONVERSION FAILED
  }

  std::array<char, 8> buffer{}; // initialize array with '\0's
  unsigned int input{8675309};
  
  if (auto [ptr, ec] = charconvutils::to_chars(buffer, input); result.ec != std::errc{}) {
    // CONVERSION FAILED
  }
}
```

### Using std::string
The following example illustrates using charconvutils to place the result of the conversion in a `std::string`. It uses a small string with a size of 1 element and then loops, calling `charconvutils::to_chars`, resizing by doubling in size if needed.  Notice that it may be needed to terminate the string with a `'\0'`, which is done with a call to `push_back`. Resizing the string may throw an exception.
Notice that in lieu of this technique you may consider using `std::to_string`. The example is provided to explore possibilities and to help a user make a decision.
 
```C++
#include "charconvutils.hpp"
#include <string>

int main() {

  std::string s{'\0'}; // initialize string with a '\0's to give it size 1
  std::to_chars_result r{};
  unsigned int jenny{ 8674309 };

  // Calculate size dynamically.
  for (size_t sz{ 2 }; /*empty*/ ; sz *= 2) {
    r = charconvutils::to_chars(s, jenny);
  
    if (r.ec != std::errc::value_too_large)
      break;
  
    // May throw std::bad_alloc 
    s.resize(sz, '\0');
  }

  if (r.ec != std::errc{}) {
    // CONVERSION FAILED
  }
  
  // In case the conversion uses all of the string elements
  // and a NTBS is needed.
  s.push_back('\0');
}
```
