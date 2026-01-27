
#include "../../include/lights/LightContainer.h"

LightContainer::LightContainer()
{
    lightDataArray.reserve(17); // Reserve space for 16 lights + light count
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
    LightData count;
    count.data1.r = lightDataArray.getSize();
    lightDataArray[16] = count;
    lightDataUBO.bindData(lightDataArray.getData(), lightDataArray.getCapacity() * sizeof(LightData));
}
void LightContainer::clearAllLights()
{
    lightDataArray.clear();
    lightDebugProxies.clear();
}
   