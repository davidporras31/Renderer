#ifndef SHADERBASE_H
#define SHADERBASE_H

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <unordered_map>

#include "Vector.h"
#include "Material.h"
#include "UBO.h"

/// @brief Base class for shader programs. shader programs are built from a shader file (.shader).
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
    /// @brief Get the location of a uniform variable in the shader program.
    /// @param uniformName The name of the uniform variable.
    /// @return The location of the uniform variable
    /// @throws std::runtime_error if the uniform variable does not exist in the shader program.
    int getUniformLocation(const std::string& uniformName);
    /// @brief Check if a uniform location exists in the shader program.
    /// @param uniformName The name of the uniform variable.
    /// @return True if the uniform location exists, false otherwise.
    bool isUniformLocationExists(const std::string& uniformName);
    /// @brief Get the binding point of a uniform buffer object (UBO) in the shader program.
    /// @param uboName The name of the UBO.
    /// @return The binding point of the UBO.
    /// @throws std::runtime_error if the UBO does not exist in the shader program
    int getUBOBindingPoint(const std::string& uboName);
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec2(const std::string& name, const glm::vec2& value);
    void setVec3(const std::string& name, const glm::vec3& value);
    void setVec4(const std::string& name, const glm::vec4& value);
    void setMat4(const std::string& name, const glm::mat4& mat);
    void setMaterial(const std::string& name, const Material& material);
    void setUBO(const std::string& name, const UBO& ubo);
};

#endif //SHADERBASE_H