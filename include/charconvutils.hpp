#ifndef CHARCONVUTILS_HPP
#define CHARCONVUTILS_HPP

//
//  charconvutils.hpp
//
//  Copyright (c) 2019 Javier Estrada
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <charconv>
#include <type_traits>

namespace charconvutils {
// -----
// Helper alias templates

template<typename T>
using EnableIfIntegral = std::enable_if_t<std::is_integral_v<T>>;

template<typename T>
using EnableIfFloating = std::enable_if_t<std::is_floating_point_v<T>>;

// -----
// from_chars function templates for C-style arrays

template<std::size_t N, typename T, typename = EnableIfIntegral<T>>
std::from_chars_result from_chars(const char(&a)[N], T& value, int base = 10) {
	return std::from_chars(a, a + N, value, base);
}

template<std::size_t N, typename T, typename = EnableIfFloating<T>>
std::from_chars_result from_chars(const char(&a)[N], T& value, std::chars_format fmt = std::chars_format::general) {
	return std::from_chars(a, a + N, value, fmt);
}

// -----
// from_chars function templates for random access containers

template<typename Cont, typename T, typename = EnableIfIntegral<T>>
std::from_chars_result from_chars(const Cont& c, T& value, int base = 10)  {
	static_assert(std::is_same_v<typename Cont::value_type, char>, "Container value type must be char.");
	return std::from_chars(c.data(), c.data() + c.size(), value, base);
}

template<typename Cont, typename T, typename = EnableIfFloating<T>>
std::from_chars_result from_chars(const Cont& c, T& value, std::chars_format fmt = std::chars_format::general) {
	static_assert(std::is_same_v<typename Cont::value_type, char>, "Container value type must be char.");
	return std::from_chars(c.data(), c.data() + c.size(), value, fmt);
}

// -----
// to_chars function templates for C-style arrays

template<std::size_t N, typename T, typename = EnableIfIntegral<T>>
std::to_chars_result to_chars(char(&a)[N], T value, int base = 10)  {
	return std::to_chars(a, a + N, value, base);
}

template<std::size_t N, typename T, typename = EnableIfFloating<T>>
std::to_chars_result to_chars(char(&a)[N], T value, std::chars_format fmt) {
	return std::to_chars(a, a + N, value, fmt);
}

template<std::size_t N, typename T, typename = EnableIfFloating<T>>
std::to_chars_result to_chars(char(&a)[N], T value, std::chars_format fmt, int precision) {
	return std::to_chars(a, a + N, value, fmt, precision);
}

// -----
// to_chars function templates for random access containers

template<typename Cont, typename T, typename = EnableIfIntegral<T>>
std::to_chars_result to_chars(Cont& c, T value, int base = 10) {
	static_assert(std::is_same_v<typename Cont::value_type, char>, "Container value type must be char.");
	return std::to_chars(c.data(), c.data() + c.size(), value, base);
}

template<typename Cont, typename T, typename = EnableIfFloating<T>>
std::to_chars_result to_chars(Cont& c, T value, std::chars_format fmt) {
	static_assert(std::is_same_v<typename Cont::value_type, char>, "Container value type must be char.");
	return std::to_chars(c.data(), c.data() + c.size(), value, fmt);
}

template<typename Cont, typename T, typename = EnableIfFloating<T>>
std::to_chars_result to_chars(Cont& c, T value, std::chars_format fmt, int precision) {
	static_assert(std::is_same_v<typename Cont::value_type, char>, "Container value type must be char.");
	return std::to_chars(c.data(), c.data() + c.size(), value, fmt, precision);
}

}

#endif // CHARCONVUTILS_HPP
