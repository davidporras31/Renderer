#ifndef UIRENDER_H
#define UIRENDER_H

#include "../RendererStage.h"
#include "../Vector.h"
#include "../Camera.h"
#include "../ShaderProgram.h"

class UIRender : public RendererStage
{
    private:
        Vector<DrawCall*,unsigned int> drawCalls;
        Camera* camera;
        ShaderProgram* defaultShader;
    public:
        ~UIRender() {
            delete defaultShader;
        }

        std::string getName() override {
            return "UIRender";
        }

        void initialize(Renderer* renderer) override {
            defaultShader = new ShaderProgram("default_ui_shader",
                {
                    {"./shaders/ui_shader.vs", GL_VERTEX_SHADER},
                    {"./shaders/ui_shader.fs", GL_FRAGMENT_SHADER}
                },
                "bin");
        }

        void execute(Renderer* renderer) override {
            for(size_t i = 0; i < drawCalls.getSize(); ++i) {
                DrawCall* drawCall = drawCalls[i];
                
                draw(drawCall);
                
            }

        }

        void pushDrawCall(DrawCall* drawCall) override {
            drawCalls.pushBack(drawCall);
        }

        void clearDrawCalls() {
            drawCalls.clear();
        }

        void draw(DrawCall* drawCall);
};


#endif //UIRENDER_H