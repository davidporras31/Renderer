
#ifndef LIGHTCONTAINER_H
#define LIGHTCONTAINER_H

#include "../Vector.h"
#include "../UBO.h"
#include "Light.h"
#include "../Cube.h"
#include "../DrawCall.h"

class LightContainer
{
private:
    Vector<LightData> lightDataArray;

    UBO lightDataUBO;
    bool debugMode = false;
    Vector<Cube> lightDebugProxies;
public:
    LightContainer();
    ~LightContainer();

    void addLight(Light *light);

    void sendLightData();

    void clearAllLights();

    UBO &getLightDataUBO() { return lightDataUBO; }

    void setDebugLightMode(bool debugMode) { this->debugMode = debugMode; }
    bool getDebugLightMode() const { return debugMode; }
    const Vector<Cube> &getLightDebugProxies() const { return lightDebugProxies; }
};

#endif // LIGHTCONTAINER_H
