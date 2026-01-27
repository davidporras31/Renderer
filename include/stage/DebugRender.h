
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
    void initialize(Renderer *renderer) override
    {
        defaultShader = new ShaderProgram("debug_render_shader",
                                           {
                                               {"./shaders/forward_geometry_shader.vs", GL_VERTEX_SHADER},
                                               //{"./shaders/debug_render_shader.fs", GL_FRAGMENT_SHADER}
                                           },
                                           "./shaders");
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
        drawCalls.clear();
    };
    void draw(DrawCall *drawCall);
    void setCamera(Camera *camera)
    {
        this->camera = camera;
    }
};

#endif // DEBUGRENDER_H
