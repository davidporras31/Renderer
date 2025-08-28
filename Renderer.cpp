#include "Renderer.h"

Renderer::Renderer(GLADloadfunc load)
{
    if (!gladLoadGL(load)) {
        // Handle the error appropriately (e.g., throw an exception, log an error, etc.)
        throw std::runtime_error("Failed to initialize GLAD");
    }
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
