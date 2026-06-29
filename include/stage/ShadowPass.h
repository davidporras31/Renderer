
#ifndef SHADOWPASS_H
#define SHADOWPASS_H

#include "../RendererStage.h"
#include "ForwardGeometry.h"
#include "../FrameBufferTexArray.h"
#include "../OrthographicCamera.h"
#include "../PerspectiveCamera.h"

class ShadowPass : public RendererStage
{
private:
    ForwardGeometry *forwardGeometry;
    ShaderProgram *depthShader;
    FrameBufferTexArray *shadowMapFBO;
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
        shadowMapFBO = new FrameBufferTexArray({1.f,1.f}, GL_DEPTH_ATTACHMENT);
        shadowMapFBO->bind();
        shadowMapFBO->initialize(glm::ivec3(params.shadowMapResolution, params.shadowMapResolution, params.maxLights));
        
        std::map<std::string, std::string> ShaderDefines = generateParameterMap(params);
        depthShader = new ShaderProgram("shadow_depth_shader.shader", &ShaderDefines);
    }
    void execute(Renderer *renderer) override
    {
        shadowMapFBO->bind();
        glClear(GL_DEPTH_BUFFER_BIT);
        glDrawBuffer(GL_NONE);
        for (size_t i = 0; i < forwardGeometry->getLightCount(); i++)
        {
            Camera * lightCamera = generateLightCamera(i);      //TODO Camera reuse
            shadowMapFBO->attach(i);
            auto* drawCalls = &forwardGeometry->getDrawCalls();
            for (size_t j = 0; j < drawCalls->getSize(); ++j)
            {
                draw(drawCalls->operator[](j), lightCamera);
            }
            

            delete lightCamera;
        }
        FrameBuffer::unbind();
    }

    void pushDrawCall(DrawCall *drawCall) override
    {

    };

    void cleanup(Renderer *renderer) override
    {

    }
    Camera * generateLightCamera(size_t lightIndex);
    void draw(DrawCall *drawCall, Camera *lightCamera);
    TextureArray * getShadowMapTextureArray() { return shadowMapFBO->getTextureArray(); }
};

#endif // SHADOWPASS_H
