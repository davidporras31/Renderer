#ifndef COMPUTESHADER_H
#define COMPUTESHADER_H

#include "ShaderBase.h"

class ComputeShader : public ShaderBase
{
private:
public:
    ComputeShader(const std::string& name, const char* computeShaderSource, const std::string& binaryPath);
    void dispatch(glm::uvec3 num_groupe);
};
#endif //COMPUTESHADER_H