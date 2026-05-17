
#ifndef DEBUGRENDER_H
#define DEBUGRENDER_H

#include "../Renderer.h"
#include "../RendererStage.h"
#include "../Vector.h"
#include "../DrawCall.h"
#include "../Camera.h"

class DebugRender : public RendererStage
{
private:
    Vector<DrawCall *> drawCalls;
    Camera *camera;
    ShaderProgram *defaultShader;

public:
    DebugRender();
    ~DebugRender();

    void pushDrawCall(DrawCall *drawCall) override
    {
        drawCalls.pushBack(drawCall);
    };
    std::string getName() override
    {
        return "DebugRender";
    };
    void initialize(Renderer *renderer, Parameters params) override
    {
        std::map<std::string, std::string> ShaderDefines = generateParameterMap(params);
        defaultShader = new ShaderProgram("debug_render_shader.shader", &ShaderDefines);
    };
    void execute(Renderer *renderer) override
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        for (size_t i = 0; i < drawCalls.getSize(); ++i)
        {
            DrawCall *drawCall = drawCalls[i];

            draw(drawCall);
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    };
    void cleanup(Renderer *renderer) override
    {
        drawCalls.clear();
    }
    void draw(DrawCall *drawCall);
    void setCamera(Camera *camera)
    {
        this->camera = camera;
    }
};

#endif // DEBUGRENDER_H
