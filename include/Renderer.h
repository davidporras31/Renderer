#ifndef RENDERER_H
#define RENDERER_H


#include <glad/gl.h>
#include <stdexcept>
#include <glm/glm.hpp>
#include <stb/stb_image_write.h>
#include "Vector.h"
#include "Color.h"
#include "Font.h"
#include "Model.h"
#include "RendererStage.h"

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