#include "../include/FrameBuffer.h"

FrameBuffer::FrameBuffer(const glm::vec2& scale)
    : size(1,1), scale(scale)
{
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    // Create a texture to attach to the framebuffer
    
    colorTexture.use();
    colorTexture.resize(size);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture.getID(), 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        // Handle framebuffer creation error
        throw std::runtime_error("Failed to create framebuffer");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &FBO);
}

void FrameBuffer::initialize(const glm::ivec2& size)
{
    bind();
    resize(size);
}

void FrameBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void FrameBuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::resize(const glm::ivec2& newSize)
{
    glm::ivec2 true_size = {newSize.x * scale.x, newSize.y * scale.y};
    if (true_size != size) {
        size = true_size;

        // Resize the framebuffer and its attachments
        bind();
        glViewport(0, 0, size.x, size.y);
        colorTexture.use();
        colorTexture.resize(size);
    }
}

glm::ivec2 FrameBuffer::getSize() const
{
    return size;
}