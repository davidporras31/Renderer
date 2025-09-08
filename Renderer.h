#ifndef RENDERER_H
#define RENDERER_H

#ifdef __gl_h_
  #error OpenGL (gl.h) header already included (API: gl), remove previous include!
#endif
#ifdef __gl3_h_
  #error OpenGL (gl3.h) header already included (API: gl), remove previous include!
#endif
#ifdef __glext_h_
  #error OpenGL (glext.h) header already included (API: gl), remove previous include!
#endif
#ifdef __gl3ext_h_
  #error OpenGL (gl3ext.h) header already included (API: gl), remove previous include!
#endif
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
    void captureScreenshot(const char* filename);
    void draw();
};

#endif // RENDERER_H