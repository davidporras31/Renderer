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
std::map<std::string, std::string> generateParameterMap(Parameters &params);

/// @brief Create a Parameters struct from a map of parameter names to their string representations.
/// @param parameterMap A map of parameter names to their string representations.
/// @return A Parameters struct populated with the values from the map.
Parameters fromParameterMap(const std::map<std::string, std::string> &parameterMap);



#endif // PARAMETERS_H