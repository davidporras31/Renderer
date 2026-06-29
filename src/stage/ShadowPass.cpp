
#include "../../include/stage/ShadowPass.h"

ShadowPass::ShadowPass()
{
}

ShadowPass::~ShadowPass()
{
    delete depthShader;
    delete shadowMapFBO;
}

Camera *ShadowPass::generateLightCamera(size_t lightIndex)
{
    // Get the light's position and direction
    LightData *lightData = &forwardGeometry->getLightDataArray()[lightIndex];
    LightType type = (LightType)lightData->position.w;
    glm::vec3 lightPosition = lightData->position;
    glm::vec3 lightDirection = lightData->direction;

    // Create a new camera for the light
    Camera *lightCamera = nullptr;
    switch (type)
    {
    case LightType::Spot:
        lightCamera = new PerspectiveCamera(lightData->data1.y, 1.0f, 0.1f, lightData->data1.x);
        lightCamera->setPosition(lightPosition);
        lightCamera->lookAt(lightPosition + lightDirection);
        break;

    default:
        lightCamera = new PerspectiveCamera(45.0f, 1.0f, 0.1f, 100.0f);
        break;
    }

    return lightCamera;
}

void ShadowPass::draw(DrawCall *drawCall, Camera *lightCamera)
{
    depthShader->use();
    depthShader->setMat4("projection", lightCamera->getProjection());
    depthShader->setMat4("view", lightCamera->getTransform());
    depthShader->setMat4("model", drawCall->drawable->getTransform());

    drawCall->drawable->draw(depthShader);
}
