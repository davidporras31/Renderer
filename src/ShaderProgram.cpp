#include "../include/ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string &name, const std::vector<std::pair<const char*, GLenum>>& shaders, std::string binaryPath)
: ShaderBase(name)
{
    if(this->neadRebuild(shaders,binaryPath))
    {
        for(const auto& shader : shaders)
            this->addShader(shader.first, shader.second);
        this->link();
        if(ShaderBase::checkBinaryShaderSupport())
            this->saveBinary(binaryPath.c_str());
    }
    else
    {
        this->loadBinary(binaryPath.c_str());
    }
}
