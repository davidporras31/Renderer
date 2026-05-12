#include "../include/String.h"

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

TEST("FromString", "ConvertToInt")
{
    REC_EQL(fromString<int>("42"), 42);
    REC_EQL(fromString<int>("-42"), -42);
}

TEST("FromString", "ConvertToUnsignedInt")
{
    REC_EQL(fromString<unsigned int>("42"), 42u);
}

TEST("FromString", "ConvertToLong")
{
    REC_EQL(fromString<long>("123456789"), 123456789l);
}

TEST("FromString", "ConvertToUnsignedLong")
{
    REC_EQL(fromString<unsigned long>("123456789"), 123456789ul);
}

TEST("FromString", "ConvertToLongLong")
{
    REC_EQL(fromString<long long>("9223372036854775807"), 9223372036854775807ll);
}

TEST("FromString", "ConvertToUnsignedLongLong")
{
    REC_EQL(fromString<unsigned long long>("18446744073709551615"), 18446744073709551615ull);
}

TEST("FromString", "ConvertToFloat")
{
    REC_EQL(fromString<float>("3.14"), 3.14f);
}

TEST("FromString", "ConvertToDouble")
{
    REC_EQL(fromString<double>("3.141592653589793"), 3.141592653589793);
}

TEST("FromString", "ConvertToLongDouble")
{
    REC_EQL(fromString<long double>("3.14159265358979323846"), 3.14159265358979323846l);
}

TEST("FromString", "ConvertToString")
{
    REC_EQL(fromString<std::string>("hello"), "hello");
}

TEST("FromString", "ConvertToBool")
{
    REC_TRUE(fromString<bool>("true"));
    REC_TRUE(fromString<bool>("1"));
    REC_TRUE(fromString<bool>("yes"));
    REC_TRUE(fromString<bool>("on"));
    REC_FALSE(fromString<bool>("false"));
    REC_FALSE(fromString<bool>("0"));
    REC_FALSE(fromString<bool>("no"));
    REC_FALSE(fromString<bool>("off"));
}