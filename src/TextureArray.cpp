
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
