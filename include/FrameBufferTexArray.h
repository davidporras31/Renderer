
#ifndef FRAMEBUFFERTEXARRAY_H
#define FRAMEBUFFERTEXARRAY_H

#include <glm/glm.hpp>
#include <glad/gl.h>
#include <stdexcept>
#include "TextureArray.h"

class FrameBufferTexArray {
private:
        glm::ivec3 size;
        glm::vec2 scale;
        GLuint FBO;
        TextureArray textureArray;
        GLint attachment;

public:
        FrameBufferTexArray(const glm::vec2& scale = {1.0f, 1.0f}, const GLint attachment = GL_COLOR_ATTACHMENT0);
        ~FrameBufferTexArray();

        void initialize(const glm::ivec3& size);
        void bind();
        static void unbind();

        void attach(GLint index);

        void resize(const glm::ivec3& newSize);
        glm::ivec3 getSize() const;
        TextureArray* getColorTexture() { return &textureArray; }
};

#endif // FRAMEBUFFERTEXARRAY_H
    