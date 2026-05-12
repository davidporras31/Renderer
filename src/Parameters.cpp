#include "../include/Parameters.h"

std::map<std::string, std::string> generateParameterMap(Parameters &params)
{
    std::map<std::string, std::string> parameterMap;
    #define RENDERER_PARAMETERS(type, name, defaultValue) parameterMap[#name] = std::to_string(params.name);
    #include "../include/Parameter.h"
    #undef RENDERER_PARAMETERS
    return parameterMap;
}

Parameters fromParameterMap(const std::map<std::string, std::string> &parameterMap)
{
    Parameters params;
    #define RENDERER_PARAMETERS(type, name, defaultValue) params.name = fromString<type>(parameterMap.at(#name));
    #include "../include/Parameter.h"
    #undef RENDERER_PARAMETERS
    return params;
}