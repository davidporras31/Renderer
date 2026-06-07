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

void saveParametersToFile(const Parameters &params, const std::string &filename)
{
    std::map<std::string, std::string> parameterMap = generateParameterMap(const_cast<Parameters &>(params));
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    for (const auto &entry : parameterMap)
    {
        outFile << entry.first << "=" << entry.second << std::endl;
    }
    outFile.close();
}

Parameters loadParametersFromFile(const std::string &filename)
{
    std::map<std::string, std::string> parameterMap;
    if (!std::ifstream(filename))
    {
        saveParametersToFile(Parameters(), filename);
    }
    std::ifstream inFile(filename);
    std::string line;
    while (std::getline(inFile, line))
    {
        size_t pos = line.find('=');
        if (pos != std::string::npos)
        {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            parameterMap[key] = value;
        }
    }
    inFile.close();
    return fromParameterMap(parameterMap);
}