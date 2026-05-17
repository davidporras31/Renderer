
#ifndef LIGHTCONTAINER_H
#define LIGHTCONTAINER_H

#include "../Vector.h"
#include "../VectorUBO.h"
#include "../UBO.h"
#include "Light.h"
#include "../Cube.h"
#include "../DrawCall.h"

class LightContainer
{
private:
    VectorUBO<LightData> lightDataArray;

    bool debugMode = false;
    Vector<Cube> lightDebugProxies;
public:
    LightContainer();
    ~LightContainer();

    void addLight(Light *light);
    void setMaxLights(size_t maxLights);

    void sendLightData();

    void clearAllLights();

    UBO &getLightDataUBO() { return lightDataArray.getUBO(); }

    void setDebugLightMode(bool debugMode) { this->debugMode = debugMode; }
    bool getDebugLightMode() const { return debugMode; }
    const Vector<Cube> &getLightDebugProxies() const { return lightDebugProxies; }
};

#endif // LIGHTCONTAINER_H
