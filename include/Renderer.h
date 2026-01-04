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
#include <stb/stb_image_write.h>
#include "Vector.h"
#include "Color.h"
#include "Font.h"
#include "RendererStage.h"
#include "Model.h"

class Renderer {
private:
    static unsigned int getChanelSize(GLuint format);
    Vector<RendererStage*,unsigned int> stages;
public:
    Renderer(GLADloadfunc load);
    ~Renderer();

    void addStage(RendererStage* stage);
    void initialize();
    RendererStage* getStage(const std::string& name) const;
    void renderFrame();
    void clear();

    void setViewport(const glm::i64vec4 viewport);
    void setClearColor(const Color& color);
    void captureScreenshot(const char* filename,GLuint format = GL_RGB);
};

#endif // RENDERER_H