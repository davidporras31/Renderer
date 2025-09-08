#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture()
{
    glGenTextures(1,&ID);
}

Texture::~Texture()
{
    glDeleteTextures(1,&ID);
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

void Texture::use(const size_t unit)
{
    glActiveTexture(GL_TEXTURE0+unit);
    glBindTexture(GL_TEXTURE_2D,ID);   
}

void Texture::load(const char *path, bool mipmap)
{
    glBindTexture(GL_TEXTURE_2D,ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    if(mipmap)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if(!data)
        throw std::runtime_error("can't open " + std::string(path));
    GLint format = getFromatFromChannels(nrChannels);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    if(mipmap)
        glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}
