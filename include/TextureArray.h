
#ifndef TEXTUREARRAY_H
#define TEXTUREARRAY_H

#include <glad/gl.h>
#include <cstddef>
#include <glm/vec3.hpp>

class TextureArray {
private:
    GLuint textureID;
public:
    TextureArray();
    ~TextureArray();
    void use(GLenum textureUnit);
    void makeEmpty(GLint internalFormat, glm::ivec3 size);
    void resize(glm::ivec3 size);
    GLuint getID() const;
};

#endif // TEXTUREARRAY_H
    