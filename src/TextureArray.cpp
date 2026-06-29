
#include "../include/TextureArray.h"

TextureArray::TextureArray()
{
    glGenTextures(1, &textureID);
}

TextureArray::~TextureArray()
{
    glDeleteTextures(1, &textureID);
}

void TextureArray::use(GLenum textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
}

void TextureArray::makeEmpty(GLint internalFormat, glm::ivec3 size)
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, internalFormat, size.x, size.y, size.z, 0, internalFormat, GL_UNSIGNED_BYTE, nullptr);
}

void TextureArray::saveToFile(const std::string &filename, GLenum format, GLenum type)
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
    glm::ivec3 size;
    glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_WIDTH, &size.x);
    glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_HEIGHT, &size.y);
    glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_DEPTH, &size.z); // Get the depth (number of layers) of the texture array
    GLint channelFormat = Texture::getChannelsFromFormat(format);
    unsigned char * data = new unsigned char[size.x * size.y * size.z * channelFormat];
    glGetTexImage(GL_TEXTURE_2D_ARRAY, 0, format, GL_UNSIGNED_BYTE, data);
    stbi_write_png(filename.c_str(), size.x, size.y * size.z, channelFormat, data, size.x * channelFormat);
    delete[] data;
}

void TextureArray::resize(glm::ivec3 size)
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
    GLint format;
    glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, format, size.x, size.y, size.z, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
}

GLuint TextureArray::getID() const
{
    return textureID;
}
