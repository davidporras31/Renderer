#include "Renderer.h"

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
    if (!gladLoadGL(load)) {
        // Handle the error appropriately (e.g., throw an exception, log an error, etc.)
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
    
}

void Renderer::setViewport(const glm::i64vec4 viewport)
{
    glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
}

void Renderer::render(Drawable *drawable)
{
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setClearColor(const Color &color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::setCamera(Camera *camera)
{
    this->camera = camera;
}

void Renderer::captureScreenshot(const char *filename,GLuint format)
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int width = viewport[2];
    int height = viewport[3];

    unsigned int format_size = getChanelSize(format);

    unsigned char* pixels = new unsigned char[width * height * format_size];

    glReadPixels(0, 0, width, height, format, GL_UNSIGNED_BYTE, pixels);

    int file = stbi_write_png(filename,width,height,format_size,pixels,0);
    if (!file)
    {
        throw std::runtime_error("Failed to open file for screenshot");
    }
    delete[] pixels;
}
