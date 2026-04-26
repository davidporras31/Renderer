#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <map>
#include <string>
#include "String.h"

#define RENDERER_PARAMETERS(type, name, defaultValue) type name = defaultValue;
struct Parameters
{
    #include "Parameter.h"
};
#undef RENDERER_PARAMETERS

/// @brief Generate a map of parameter names to their string representations.
/// @param params The parameters struct containing all parameter values.
/// @return A map of parameter names to their string representations.
std::map<std::string, std::string> generateParameterMap(Parameters &params)
{
    std::map<std::string, std::string> parameterMap;
    #define RENDERER_PARAMETERS(type, name, defaultValue) parameterMap[#name] = std::to_string(params.name);
    #include "Parameter.h"
    #undef RENDERER_PARAMETERS
    return parameterMap;
}
Parameters fromParameterMap(const std::map<std::string, std::string> &parameterMap)
{
    Parameters params;
    #define RENDERER_PARAMETERS(type, name, defaultValue) params.name = fromString<type>(parameterMap.at(#name));
    #include "Parameter.h"
    #undef RENDERER_PARAMETERS
    return params;
}



#endif // PARAMETERS_H