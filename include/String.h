#ifndef STRING_H
#define STRING_H

#include <string>
#include <sstream>
#include <type_traits>

template <typename T>
T fromString(const std::string &str);

template <typename T>
T fromString(const std::string &str)
{
    std::istringstream iss(str);
    T result;
    iss >> result;
    return result;
}

template <>
long double fromString(const std::string &str)
{
    return std::stold(str);
}
template <>
double fromString(const std::string &str)
{
    return std::stod(str);
}
template <>
float fromString(const std::string &str)
{
    return std::stof(str);
}
template <>
std::string fromString(const std::string &str)
{
    return str;
}
template <>
bool fromString(const std::string &str)
{
    return str == "true" || str == "1" || str == "yes" || str == "on" || str == "True" || str == "TRUE" || str == "Yes" || str == "YES" || str == "On" || str == "ON";
}
template <>
int fromString(const std::string &str)
{
    return std::stoi(str);
}
template <>
unsigned int fromString(const std::string &str)
{
    return std::stoul(str);
}
template <>
long fromString(const std::string &str)
{
    return std::stol(str);
}
template <>
unsigned long fromString(const std::string &str)
{
    return std::stoul(str);
}
template <>
long long fromString(const std::string &str)
{
    return std::stoll(str);
}
template <>
unsigned long long fromString(const std::string &str)
{
    return std::stoull(str);
}


#endif // STRING_H