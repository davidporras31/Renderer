#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/gl.h>
#include <stb/stb_image.h>
#include <stdexcept>
class Texture
{
private:
    GLuint ID;
public:
    Texture();
    ~Texture();

    static GLint getFromatFromChannels(int chanels);

    void use(const size_t unit = 0);
    void load(const char* path, bool mipmap = true);
    void loadFromMemory(GLint format,int width,int height,unsigned char * buffer, bool mipmap = true);
};

#endif  //TEXTURE_H