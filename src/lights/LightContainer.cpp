
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
    lightDataArray.emplaceBack(light);
    if (debugMode)
    {
        lightDebugProxies.emplaceBack(light->getDebugProxies());
        switch (light->getType())
        {
            case LightType::Directional:
                lightDebugProxies.last()->setScale(glm::vec3(1.0f));
                break;
            case LightType::Point:
                lightDebugProxies.last()->setScale(glm::vec3(1.0f));
                break;
            case LightType::Spot:
                lightDebugProxies.last()->setScale(glm::vec3(1.0f));
                break;
            case LightType::Area:
                lightDebugProxies.last()->setScale(glm::vec3(1.0f));
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
   