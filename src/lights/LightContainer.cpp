
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
        switch (static_cast<LightType>(light->getLightData().position.w))
        {
            case LightType::Directional:
                lightDebugProxies.last().setScale(glm::vec3(1.0f));
                break;
            case LightType::Point:
                lightDebugProxies.last().setScale(glm::vec3(light->getLightData().data1.x));
                break;
            case LightType::Spot:
                lightDebugProxies.last().setScale(glm::vec3(light->getLightData().data1.x));
                break;
            case LightType::Area:
                lightDebugProxies.last().setScale(glm::vec3(light->getLightData().data1.x));
                break;
        }
    }
}

void LightContainer::setMaxLights(size_t maxLights)
{
    lightDataArray.reserve(maxLights);
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
   