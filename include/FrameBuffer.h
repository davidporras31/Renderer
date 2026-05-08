#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <glm/glm.hpp>
#include <glad/gl.h>
#include <stdexcept>
#include "Texture.h"

/// @brief A wrapper around an OpenGL framebuffer object (FBO) that manages a color texture attachment and allows for resizing.
class FrameBuffer {
    private:
        glm::ivec2 size;
        glm::vec2 scale;
        GLuint FBO;
        Texture colorTexture;
    public:
        FrameBuffer(const glm::vec2& scale = {1.0f, 1.0f});
        ~FrameBuffer();

        void initialize(const glm::ivec2& size);
        void bind();
        void unbind();

        void resize(const glm::ivec2& newSize);
        glm::ivec2 getSize() const;
        Texture* getColorTexture() { return &colorTexture; }
};

#endif // FRAME_BUFFER_H