#ifndef UIRENDER_H
#define UIRENDER_H

#include "../RendererStage.h"
#include "../Vector.h"
#include "../Camera.h"
#include "../ShaderProgram.h"

class UIRender : public RendererStage
{
private:
    Vector<DrawCall *, unsigned int> drawCalls;
    Camera *camera;
    ShaderProgram *defaultShader;

public:
    ~UIRender()
    {
        delete defaultShader;
    }

    std::string getName() override
    {
        return "UIRender";
    }

    void initialize(Renderer *renderer, Parameters params) override
    {
        std::map<std::string, std::string> ShaderDefines = generateParameterMap(params);
        defaultShader = new ShaderProgram("ui_shader.shader", &ShaderDefines);
    }

    void execute(Renderer *renderer) override
    {
        for (size_t i = 0; i < drawCalls.getSize(); ++i)
        {
            DrawCall *drawCall = drawCalls[i];

            draw(drawCall);
        }
    }

    void cleanup(Renderer *renderer) override
    {
        drawCalls.clear();
    }

    void pushDrawCall(DrawCall *drawCall) override
    {
        drawCalls.pushBack(drawCall);
    }

    void draw(DrawCall *drawCall);
};

#endif // UIRENDER_H