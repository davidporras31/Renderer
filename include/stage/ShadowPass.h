
#ifndef SHADOWPASS_H
#define SHADOWPASS_H

#include "../RendererStage.h"
#include "ForwardGeometry.h"
#include "../TextureArray.h"

class ShadowPass : public RendererStage
{
private:
    ForwardGeometry *forwardGeometry;
    ShaderProgram *depthShader;
    TextureArray shadowMapArray;
public:
    ShadowPass();
    ~ShadowPass();
    std::string getName() override
    {
        return "ShadowPass";
    }
    void initialize(Renderer *renderer, Parameters params) override
    {
        forwardGeometry = static_cast<ForwardGeometry *>(renderer->getStage("ForwardGeometry"));
        
        std::map<std::string, std::string> ShaderDefines = generateParameterMap(params);
        depthShader = new ShaderProgram("shadow_depth_shader.shader", &ShaderDefines);
        shadowMapArray.makeEmpty(GL_DEPTH_COMPONENT, glm::ivec3(params.shadowMapResolution, params.shadowMapResolution, params.maxLights));
    }
    void execute(Renderer *renderer) override
    {
        for (size_t i = 0; i < forwardGeometry->getLightCount(); i++)
        {
            
        }
        
    }

    void pushDrawCall(DrawCall *drawCall) override
    {

    };

    void cleanup(Renderer *renderer) override
    {

    }
};

#endif // SHADOWPASS_H
