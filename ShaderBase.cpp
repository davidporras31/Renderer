#include "ShaderBase.h"

bool ShaderBase::checkBinaryShaderSupport()
{
    if (ShaderBase::supportBinaryShaders != nullptr)
    {
        GLint formats = 0;
        glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS, &formats);
        ShaderBase::supportBinaryShaders = new bool(formats > 0);
    }
    return *ShaderBase::supportBinaryShaders;
}

bool ShaderBase::neadRebuild(const std::vector<std::pair<const char *, GLenum>> &shaders, const std::string &binaryPath)
{
    if (checkBinaryShaderSupport())
        return true;
    
    std::string binFilePath( binaryPath + '/' + name + ".glbin");
    if (!std::filesystem::exists(binFilePath))
        return true;
    std::filesystem::file_time_type binFileTime = std::filesystem::last_write_time(binFilePath);
    for (const auto& shader : shaders)
    {
        std::filesystem::file_time_type shaderFileTime = std::filesystem::last_write_time(shader.first);
        if (shaderFileTime > binFileTime)
            return true;
    }
    return false;
}

ShaderBase::ShaderBase(const std::string &name)
: name(name)
{
    this->ID = glCreateProgram();
    if (this->ID == 0)
        throw std::runtime_error("Failed to create shader program");
}

ShaderBase::~ShaderBase()
{
    glDeleteProgram(this->ID);
}

void ShaderBase::addShader(const char *source, GLenum shaderType)
{
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("Shader compilation failed: ") + infoLog);
    }
    glAttachShader(this->ID, shader);
    glDeleteShader(shader);
}

void ShaderBase::link()
{
    glLinkProgram(this->ID);
    GLint success;
    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(this->ID, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("Shader linking failed: ") + infoLog);
    }
}

void ShaderBase::saveBinary(const char *filename)
{
    std::ofstream file(std::string(filename) + '/' + name + ".glbin", std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Could not open file to save binary shader");
    GLint length = 0;
    glGetProgramiv(this->ID, GL_PROGRAM_BINARY_LENGTH, &length);
    if (length <= 0)
        throw std::runtime_error("Could not get binary shader length");
    std::vector<char> binary(length);
    GLenum format = 0;
    glGetProgramBinary(this->ID, length, nullptr, &format, binary.data());
    file.write(reinterpret_cast<const char*>(&format), sizeof(GLenum));
    file.write(binary.data(), length);
    file.close();
}

void ShaderBase::loadBinary(const char *filename)
{
    std::ifstream file(std::string(filename) + '/' + name + ".glbin", std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Could not open file to load binary shader");
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    if (size <= sizeof(GLenum))
        throw std::runtime_error("Invalid binary shader file");
    GLenum format = 0;
    file.read(reinterpret_cast<char*>(&format), sizeof(GLenum));
    std::vector<char> binary(size - sizeof(GLenum));
    file.read(binary.data(), size - sizeof(GLenum));
    file.close();
    glProgramBinary(this->ID, format, binary.data(), static_cast<GLsizei>(binary.size()));
    GLint success = 0;
    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(this->ID, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("Failed to load binary shader: ") + infoLog);
    }
}
