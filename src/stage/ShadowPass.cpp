
#include "../../include/stage/ShadowPass.h"

ShadowPass::ShadowPass()
{
    
}

ShadowPass::~ShadowPass()
{
    delete depthShader;
    delete shadowMapFBO;
}

Camera * ShadowPass::generateLightCamera(size_t lightIndex)
{
    // Get the light's position and direction
    glm::vec3 lightPosition = forwardGeometry->getLightDataArray()[lightIndex].position;
    glm::vec3 lightDirection = forwardGeometry->getLightDataArray()[lightIndex].direction;

    // Create a new camera for the light
    Camera *lightCamera = nullptr;
    if (forwardGeometry->getLightDataArray()[lightIndex].data1.w == 0.0f) // Directional light
    {
        lightCamera = new OrthographicCamera(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    }
    //TODO: Add support for other light types (point lights, spotlights)
    else
    {
        lightCamera = new PerspectiveCamera(45.0f, 1.0f, 0.1f, 100.0f);
    }


    return lightCamera;
}

void ShadowPass::draw(DrawCall *drawCall, Camera *lightCamera)
{
    depthShader->use();
    depthShader->setMat4("projection", lightCamera->getProjection());
    depthShader->setMat4("view", lightCamera->getTransform());
    depthShader->setMat4("model", drawCall->drawable->getTransform());

    //drawCall->drawable->draw(depthShader);
}
