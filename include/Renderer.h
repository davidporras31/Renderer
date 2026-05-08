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
#include "FrameBuffer.h"

/// @brief the openGL renderer that manages the rendering stages and frame buffers, and handles the rendering loop.
/// The renderer is responsible for initializing the rendering stages and frame buffers, and for executing the rendering loop.
class Renderer {
private:
    static unsigned int getChanelSize(GLuint format);
    Vector<RendererStage*,unsigned short> stages;
    Vector<std::pair<FrameBuffer*,std::string>,unsigned short> frameBuffers;
public:
    Renderer(GLADloadfunc load);
    ~Renderer();

    void addStage(RendererStage* stage);
    RendererStage* getStage(const std::string& name) const;

    void addFrameBuffer(FrameBuffer* frameBuffer, const std::string& name);
    FrameBuffer* getFrameBuffer(const std::string& name) const;

    void initialize();
    void renderFrame();
    void clear();

    bool getDebugMode(const std::string& stageName) const;
    void setDebugMode(const std::string& stageName, const bool mode);

    void setViewport(const glm::ivec4 viewport);
    void setClearColor(const Color& color);
    void captureScreenshot(const char* filename,GLuint format = GL_RGB);
};

#endif // RENDERER_H