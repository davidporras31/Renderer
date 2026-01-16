#ifndef FORWARDGEOMETRY_H
#define FORWARDGEOMETRY_H

#include "../RendererStage.h"
#include "../Vector.h"
#include "../Camera.h"
#include "../ShaderProgram.h"
#include "../Material.h"
#include "../lights/LightContainer.h"

#ifndef FORWARDGEOMETRY_SHADER_PATH
#define FORWARDGEOMETRY_SHADER_PATH "./shaders/forward_geometry_shader"
#endif //FORWARDGEOMETRY_SHADER_PATH

class ForwardGeometry : public RendererStage, public LightContainer
{
    private:
        Vector<DrawCall*,unsigned int> drawCalls;
        Camera* camera;
        ShaderProgram* defaultShader;
        Material defaultMaterial;
    public:
        ~ForwardGeometry() {
            delete defaultShader;
        }

        std::string getName() override {
            return "ForwardGeometry";
        }

        void initialize(Renderer* renderer) override {
            defaultShader = new ShaderProgram("forward_geometry_shader",
                {
                    {FORWARDGEOMETRY_SHADER_PATH ".vs", GL_VERTEX_SHADER},
                    {FORWARDGEOMETRY_SHADER_PATH ".fs", GL_FRAGMENT_SHADER}
                },
                "./shaders");

            defaultMaterial = Material();
        }

        void execute(Renderer* renderer) override {
            for(size_t i = 0; i < drawCalls.getSize(); ++i) {
                DrawCall* drawCall = drawCalls[i];
                
                draw(drawCall);
                
            }
            clearDrawCalls();
            clearAllLights();
        }

        void pushDrawCall(DrawCall* drawCall) override {
            drawCalls.pushBack(drawCall);
        }
        void clearDrawCalls() {
            drawCalls.clear();
        }

        void draw(DrawCall* drawCall);
        void setCamera(Camera* camera) {
            this->camera = camera;
        }
};

#endif //FORWARDGEOMETRY_H