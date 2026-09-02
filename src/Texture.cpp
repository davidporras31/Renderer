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
GLuint Texture::getID() const
{
    return ID;
}
