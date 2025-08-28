#ifndef RENDERER_H
#define RENDERER_H
#include <glad/gl.h>
#include <stdexcept>
#include <glm/glm.hpp>
#include "Color.h"
#include "Camera.h"
#include "Drawable.h"

class Renderer {
private:
    Camera* camera;

public:
    Renderer(GLADloadfunc load);
    ~Renderer();

    void setViewport(const glm::i64vec4 viewport);
    void render(Drawable* drawable);
    void clear();
    void setClearColor(const Color& color);
    void setCamera(Camera* camera);
    void captureScreenshot();
    void draw();
    void display();
};

#endif // RENDERER_H