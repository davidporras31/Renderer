#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <fstream>
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

/// @brief Save Parameters to a file or create the file.
/// @param params The parameters to save.
/// @param filename The name of the file to save parameters to.
void saveParametersToFile(const Parameters &params, const std::string &filename);

/// @brief Load parameters from a file or create the file with default values, unset value will be populated with default one.
/// @param filename The name of the file to load parameters from.
/// @return A Parameters struct populated with the values from the file.
Parameters loadParametersFromFile(const std::string &filename);



#endif // PARAMETERS_H