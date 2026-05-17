#include "../include/Renderer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

unsigned int Renderer::getChanelSize(GLuint format)
{
    switch (format)
    {
    case GL_RGBA:
        return 4;
    case GL_RGB:
        return 3;
    case GL_RG:
        return 2;
    case GL_ALPHA:
        return 1;
    default:
        return 0;
    }
}

Renderer::Renderer(GLADloadfunc load)
{
    if (!gladLoadGL(load))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    stbi_flip_vertically_on_write(1);
    Font::init();
    Model::init();
    glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
    for (unsigned int i = 0; i < this->stages.getSize(); i++)
    {
        delete this->stages[i];
    }
    frameBuffers.safeClear();
}

void Renderer::addStage(RendererStage *stage)
{
    this->stages.pushBack(stage);
}

void Renderer::initialize(Parameters params)
{
    glm::i64vec4 viewport;
    glGetIntegerv(GL_VIEWPORT, (GLint *)&viewport);
    for (unsigned int i = 0; i < this->frameBuffers.getSize(); i++)
    {
        this->frameBuffers[i].first->initialize({viewport.z, viewport.w});
        this->frameBuffers[i].first->unbind();
    }
    for (unsigned int i = 0; i < this->stages.getSize(); i++)
    {
        this->stages[i]->initialize(this, params);
    }
}

RendererStage *Renderer::getStage(const std::string &name) const
{
    RendererStage *tmp = nullptr;
    for (unsigned int i = 0; i < this->stages.getSize(); i++)
    {
        tmp = this->stages[i];
        if (tmp->getName() == name)
            break;
    }
    return tmp;
}

void Renderer::addFrameBuffer(FrameBuffer *frameBuffer, const std::string &name)
{
    this->frameBuffers.pushBack({frameBuffer, name});
}
FrameBuffer *Renderer::getFrameBuffer(const std::string &name) const
{
    for (unsigned int i = 0; i < this->frameBuffers.getSize(); i++)
    {
        if (this->frameBuffers[i].second == name)
        {
            return this->frameBuffers[i].first;
        }
    }
    return nullptr;
}
void Renderer::renderFrame()
{
    for (unsigned int i = 0; i < this->stages.getSize(); i++)
    {
        this->stages[i]->execute(this);
    }
    for (unsigned int i = 0; i < this->stages.getSize(); i++)
    {
        this->stages[i]->cleanup(this);
    }
}

bool Renderer::getDebugMode(const std::string &stageName) const
{
    RendererStage *stage = getStage(stageName);
    if (stage)
    {
        return stage->getDebugMode();
    }
    else
    {
        throw std::runtime_error("Renderer stage " + stageName + " not found");
    }
}

void Renderer::setDebugMode(const std::string &stageName, const bool mode)
{
    RendererStage *stage = getStage(stageName);
    if (stage)
    {
        stage->setDebugMode(mode);
    }
    else
    {
        throw std::runtime_error("Renderer stage " + stageName + " not found");
    }
}
void Renderer::setViewport(const glm::ivec4 viewport)
{
    glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
    for (unsigned int i = 0; i < this->frameBuffers.getSize(); i++)
    {
        this->frameBuffers[i].first->resize({viewport.z, viewport.w});
    }
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setClearColor(const Color &color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::captureScreenshot(const char *filename, GLuint format)
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int width = viewport[2];
    int height = viewport[3];

    unsigned int format_size = getChanelSize(format);

    unsigned char *pixels = new unsigned char[width * height * format_size];

    glReadPixels(0, 0, width, height, format, GL_UNSIGNED_BYTE, pixels);

    int file = stbi_write_png(filename, width, height, format_size, pixels, 0);
    if (!file)
    {
        throw std::runtime_error("Failed to open file for screenshot");
    }
    delete[] pixels;
}
