#include "../include/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture()
{
    glGenTextures(1, &ID);
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}

GLint Texture::getFromatFromChannels(int chanels)
{
    switch (chanels)
    {
    case 4:
        return GL_RGBA;
    case 3:
        return GL_RGB;
    case 2:
        return GL_RG;
    case 1:
        return GL_ALPHA;

    default:
        return 0;
    }
}
GLint Texture::getChannelsFromFormat(GLint format)
{
    switch (format)
    {
    case GL_RGBA:
        return 4;
    case GL_RGB:
        return 3;
    case GL_RG:
        return 2;
    case GL_ALPHA:
        return 1;
    case GL_DEPTH_COMPONENT:
        return 1;

    default:
        return 0;
    }
}

void Texture::use(const size_t unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::load(const char *path, bool mipmap)
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (!data)
        throw std::runtime_error("can't open " + std::string(path));
    GLint format = getFromatFromChannels(nrChannels);
    loadFromMemory(format, width, height, data, mipmap);
    stbi_image_free(data);
}

void Texture::loadFromMemory(GLint format, int width, int height, unsigned char *buffer, bool mipmap, bool clamp)
{
    glBindTexture(GL_TEXTURE_2D, ID);
    GLint wrapMode = clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    if (mipmap)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, buffer);
    if (mipmap)
        glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::resize(glm::ivec2 size)
{
    glBindTexture(GL_TEXTURE_2D, ID);
    GLint format;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, nullptr);
}
GLuint Texture::getID() const
{
    return ID;
}
