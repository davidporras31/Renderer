#ifndef STRING_H
#define STRING_H

#include <string>
#include <sstream>
#include <type_traits>
#include "Test.hpp"

template <typename T>
T fromString(const std::string &str);


#endif // STRING_H