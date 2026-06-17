
#include "../include/FrameBufferTexArray.h"

FrameBufferTexArray::FrameBufferTexArray(const glm::vec2 &scale, const GLint attachment)
    : size(1, 1, 1), scale(scale), attachment(attachment)
{
    glGenFramebuffers(1, &FBO);

    unbind();
}

FrameBufferTexArray::~FrameBufferTexArray()
{
    glDeleteFramebuffers(1, &FBO);
}

void FrameBufferTexArray::initialize(const glm::ivec3 &size)
{
    textureArray.makeEmpty(GL_DEPTH_COMPONENT, size);

    bind();

    glViewport(0, 0, size.x, size.y);

    attach(0); // Attach the first layer of the texture array to the framebuffer
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        // Handle framebuffer creation error
        throw std::runtime_error("Failed to create framebuffer");
    }
    unbind();
}

void FrameBufferTexArray::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void FrameBufferTexArray::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferTexArray::attach(GLint index)
{
    glFramebufferTextureLayer(
        GL_FRAMEBUFFER,       // Target
        attachment,           // Attachment point
        textureArray.getID(), // Texture ID (must be GL_TEXTURE_2D_ARRAY)
        0,                    // Mipmap level
        index                 // Specific layer index
    );
}
void FrameBufferTexArray::resize(const glm::ivec3 &newSize)
{
    glm::ivec3 true_size = {newSize.x * scale.x, newSize.y * scale.y, newSize.z};
    if (true_size != size)
    {
        size = true_size;

        // Resize the framebuffer and its attachments
        bind();
        glViewport(0, 0, size.x, size.y);
        textureArray.resize(size);
    }
}

glm::ivec3 FrameBufferTexArray::getSize() const
{
    return size;
}