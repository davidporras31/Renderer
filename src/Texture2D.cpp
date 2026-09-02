
#include "../include/Texture2D.h"

void Texture2D::use(GLenum textureUnit) const
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::load(const char *path, bool mipmap)
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (!data)
        throw std::runtime_error("can't open " + std::string(path));
    GLint format = getFromatFromChannels(nrChannels);
    loadFromMemory(format, width, height, data, mipmap);
    stbi_image_free(data);
}

void Texture2D::loadFromMemory(GLint format, int width, int height, unsigned char *buffer, bool mipmap, bool clamp)
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

void Texture2D::resize(glm::ivec3 size)
{
    glBindTexture(GL_TEXTURE_2D, ID);
    GLint format;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, nullptr);
}