
#ifndef TEXTUREARRAY_H
#define TEXTUREARRAY_H

#include <cstddef>
#include <string>
#include <stb/stb_image_write.h>
#include "Texture.h"

class TextureArray : public Texture
{
public:
    void use(GLenum textureUnit = 0) const override;
    void resize(glm::ivec3 size) override;
    void makeEmpty(GLint internalFormat, glm::ivec3 size);
    void saveToFile(const std::string &filename, GLenum format, GLenum type);
};

#endif // TEXTUREARRAY_H
