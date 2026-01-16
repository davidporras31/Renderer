
#include "../../include/lights/LightContainer.h"

LightContainer::LightContainer() {
    // Constructor implementation
}

LightContainer::~LightContainer() {
    // Destructor implementation
    clearAllLights();
}

void LightContainer::addLight(AreaLight *light)
{
    areaLights.pushBack(light);
}
void LightContainer::addLight(DirectionalLight *light)
{
    directionalLights.pushBack(light);
}
void LightContainer::addLight(PointLight *light)
{
    pointLights.pushBack(light);
}
void LightContainer::addLight(SpotLight *light)
{
    spotLights.pushBack(light);
}
void LightContainer::senderAreaLightDataToShader(ShaderProgram &shader, Drawable *receiver)
{
    Vector<AreaLight*> toSend;
    for (size_t i = 0; i < areaLights.getSize(); ++i)
    {
        if (areaLights[i]->afectsDrawable(receiver->getPosition(),receiver->getRenderRadius()))
        {
            toSend.pushBack(areaLights[i]);
        }
    }
    shader.setLightArray("areaLights",&toSend);
    
}
void LightContainer::senderDirectionalLightDataToShader(ShaderProgram &shader, Drawable *receiver)
{
    Vector<DirectionalLight*> toSend;
    for (size_t i = 0; i < directionalLights.getSize(); ++i)
    {
        if (directionalLights[i]->afectsDrawable(receiver->getPosition(),receiver->getRenderRadius()))
        {
            toSend.pushBack(directionalLights[i]);
        }
    }
    shader.setLightArray("directionalLights",&toSend);
}
void LightContainer::senderPointLightDataToShader(ShaderProgram &shader, Drawable *receiver)
{
    Vector<PointLight*> toSend;
    for (size_t i = 0; i < pointLights.getSize(); ++i)
    {
        if (pointLights[i]->afectsDrawable(receiver->getPosition(),receiver->getRenderRadius()))
        {
            toSend.pushBack(pointLights[i]);
        }
    }
    shader.setLightArray("pointLights",&toSend);
}
void LightContainer::senderSpotLightDataToShader(ShaderProgram &shader, Drawable *receiver)
{
    Vector<SpotLight*> toSend;
    for (size_t i = 0; i < spotLights.getSize(); ++i)
    {
        if (spotLights[i]->afectsDrawable(receiver->getGlobalPosition(),receiver->getRenderRadius()))
        {
            toSend.pushBack(spotLights[i]);
        }
    }
    shader.setLightArray("spotLights",&toSend);
}
void LightContainer::sendLightDataToShader(ShaderProgram &shader, Drawable *receiver)
{
    senderAreaLightDataToShader(shader, receiver);
    senderDirectionalLightDataToShader(shader, receiver);
    senderPointLightDataToShader(shader, receiver);
    senderSpotLightDataToShader(shader, receiver);
}
void LightContainer::clearAllLights()
{
    areaLights.clear();
    directionalLights.clear();
    pointLights.clear();
    spotLights.clear();
}
   