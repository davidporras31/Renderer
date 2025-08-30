#ifndef SHADERBASE_H
#define SHADERBASE_H

#include <glad/gl.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

class ShaderBase
{
private:
    static bool* supportBinaryShaders;
protected:
    static bool checkBinaryShaderSupport();
    bool neadRebuild(const std::vector<std::pair<const char*, GLenum>>& shaders, const std::string& binaryPath);
    unsigned int ID;
    std::string name;
    void addShader(const char* source, GLenum shaderType);
    void link();
    void saveBinary(const char* filename);
    void loadBinary(const char* filename);
public:
    ShaderBase(const std::string& name);
    ~ShaderBase();
};

#endif //SHADERBASE_H