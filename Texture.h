#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/gl.h>
#include <string>
class Texture
{
private:
    unsigned int ID;
public:
    Texture(std::string path);
};

#endif  //TEXTURE_H