#include "ComputeShader.h"

ComputeShader::ComputeShader(const std::string &name, const char *computeShaderSource, const std::string &binaryPath)
: ShaderBase(name)
{
    if(this->neadRebuild({{computeShaderSource, GL_COMPUTE_SHADER}},binaryPath))
    {
        this->addShader(computeShaderSource, GL_COMPUTE_SHADER);
        this->link();
        if(ShaderBase::checkBinaryShaderSupport())
            this->saveBinary(binaryPath.c_str());
    }
    else
    {
        this->loadBinary(binaryPath.c_str());
    }

}