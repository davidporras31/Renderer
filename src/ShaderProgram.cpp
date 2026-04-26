#include "../include/ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string path, std::map<std::string, std::string> *defines)
    : ShaderBase(path)
{
    std::map<std::string, std::string> definescopy;
    if (defines)
        definescopy = *defines;
    std::ifstream file("./shaders/src/" + path);

    std::string directory;

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open shader file: " + path);
    }
    std::string name;
    std::getline(file, name); // read the first line as the shader name

    std::vector<std::pair<const char *, GLenum>> objects;
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos)
        {
            throw std::runtime_error("Invalid shader file format: " + path);
        }
        std::string filePath = line.substr(0, commaPos);
        std::string typeStr = line.substr(commaPos + 1);
        GLenum shaderType;
        if (typeStr == "vertex")
            shaderType = GL_VERTEX_SHADER;
        else if (typeStr == "fragment")
            shaderType = GL_FRAGMENT_SHADER;
        else if (typeStr == "geometry")
            shaderType = GL_GEOMETRY_SHADER;
        else if (typeStr == "tess_control")
            shaderType = GL_TESS_CONTROL_SHADER;
        else if (typeStr == "tess_evaluation")
            shaderType = GL_TESS_EVALUATION_SHADER;
        else
        {
            throw std::runtime_error("Unknown shader type: " + typeStr);
        }
        objects.emplace_back(strdup(filePath.c_str()), shaderType);
    }

    for (size_t i = 0; i < objects.size(); i++)
    {
        std::string source = "./shaders/src/" + std::string(objects[i].first);
        std::string object = "./shaders/obj/" + std::string(objects[i].first) + ".o";
        delete[] objects[i].first;
        objects[i].first = strdup(object.c_str());
        if (ShaderPrecompiler::needsReprecompile(object, &definescopy))
            ShaderPrecompiler::precompileShader(source, object, &definescopy);
    }

    this->build(name, objects, "./shaders/bin/");
}

void ShaderProgram::build(const std::string &name, const std::vector<std::pair<const char *, GLenum>> &shaders, std::string binaryPath)
{
    this->name = name;
    if (this->neadRebuild(shaders, binaryPath))
    {
        for (const auto &shader : shaders)
            this->addShader(shader.first, shader.second);
        this->link();
        if (ShaderBase::checkBinaryShaderSupport())
            this->saveBinary(binaryPath.c_str());
    }
    else
    {
        this->loadBinary(binaryPath.c_str());
    }
}
