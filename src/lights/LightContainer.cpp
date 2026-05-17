
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
        if(light->getLightData().position.w == float(LightType::Point))
            lightDebugProxies.last().setScale(glm::vec3(light->getLightData().data1.x));
        else
            lightDebugProxies.last().setScale(glm::vec3(1.0f));
    }
}

void LightContainer::setMaxLights(size_t maxLights)
{
    lightDataArray.setMaxSize(maxLights);
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
   