
#include "../../include/lights/LightContainer.h"

LightContainer::LightContainer()
{
    lightDebugProxies.reserve(16);
    
}

LightContainer::~LightContainer()
{
    clearAllLights();
}

void LightContainer::addLight(Light* light)
{
    lightDataArray.pushBack(light->getLightData());
    if (debugMode)
    {
        lightDebugProxies.emplaceBack();
        lightDebugProxies.last().setPosition(glm::vec3(light->getLightData().position));
        lightDebugProxies.last().setScale(glm::vec3(10.0f));
    }
}

void LightContainer::sendLightData()
{
    lightDataArray.bindData();
}
void LightContainer::clearAllLights()
{
    lightDataArray.clear();
    lightDebugProxies.safeClear();
}
   