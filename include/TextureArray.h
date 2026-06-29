
#ifndef TEXTUREARRAY_H
#define TEXTUREARRAY_H

#include <glad/gl.h>
#include <cstddef>
#include <string>
#include <glm/vec3.hpp>
#include <stb/stb_image_write.h>
#include "Texture.h"

class TextureArray {
private:
    GLuint textureID;
public:
    TextureArray();
    ~TextureArray();
    void use(GLenum textureUnit = 0);
    void makeEmpty(GLint internalFormat, glm::ivec3 size);
    void saveToFile(const std::string &filename, GLenum format, GLenum type);
    void resize(glm::ivec3 size);
    GLuint getID() const;
};

#endif // TEXTUREARRAY_H
    