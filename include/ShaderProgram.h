#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <map>
#include <fstream>
#include "ShaderBase.h"
#include "../lib/shader-precompiler/ShaderPrecompiler.h"

class ShaderProgram : public ShaderBase
{
private:
    // data
public:
    ShaderProgram(std::string path, std::map<std::string, std::string> *defines);
    void build(const std::string &name, const std::vector<std::pair<const char *, GLenum>> &shaders, std::string binaryPath);
};

#endif // SHADERPROGRAM_H