#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "ShaderBase.h"

class ShaderProgram : public ShaderBase
{
private:

public:
    ShaderProgram(const std::string& name, const std::vector<std::pair<const char*, GLenum>>& shaders,std::string binaryPath);
};


#endif //SHADERPROGRAM_H