#ifndef SHADERBASE_H
#define SHADERBASE_H

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <unordered_map>

class ShaderBase
{
private:
    static bool* supportBinaryShaders;
    std::unordered_map<std::string, int> uniformLocations;
protected:
    static bool checkBinaryShaderSupport();
    std::string* loadFile(const char* path);
    bool neadRebuild(const std::vector<std::pair<const char*, GLenum>>& shaders, const std::string& binaryPath);
    unsigned int ID;
    std::string name;
    void addShader(const char* path, GLenum shaderType);
    void link();
    void saveBinary(const char* filename);
    void loadBinary(const char* filename);
public:
    ShaderBase(const std::string& name);
    ~ShaderBase();
    void use() const;
    int getUniformLocation(const std::string& uniformName);
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec2(const std::string& name, const glm::vec2& value);
    void setVec4(const std::string& name, const glm::vec4& value);
    void setMat4(const std::string& name, const glm::mat4& mat);
};

#endif //SHADERBASE_H