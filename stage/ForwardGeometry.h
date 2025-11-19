#ifndef FORWARDGEOMETRY_H
#define FORWARDGEOMETRY_H

#include "../RendererStage.h"
#include "../Vector.h"
#include "../Camera.h"
#include "../ShaderProgram.h"

class ForwardGeometry : public RendererStage
{
    private:
        Vector<DrawCall*,unsigned int> drawCalls;
        Camera* camera;
        ShaderProgram* defaultShader;
    public:
        ~ForwardGeometry() {
            delete defaultShader;
        }

        std::string getName() override {
            return "ForwardGeometry";
        }

        void initialize(Renderer* renderer) override {
            defaultShader = new ShaderProgram("default_forward_shader",
                {
                    {"./shaders/default_forward_shader.vs", GL_VERTEX_SHADER},
                    {"./shaders/default_forward_shader.fs", GL_FRAGMENT_SHADER}
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

        void draw(DrawCall* drawCall);
        void setCamera(Camera* camera) {
            this->camera = camera;
        }
};

#endif //FORWARDGEOMETRY_H