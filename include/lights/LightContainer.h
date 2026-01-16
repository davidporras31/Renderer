
#ifndef LIGHTCONTAINER_H
#define LIGHTCONTAINER_H

#include "../Vector.h"
#include "AreaLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "../ShaderProgram.h"
#include "../Drawable.h"

class LightContainer {
private:
    Vector<AreaLight*> areaLights;
    Vector<DirectionalLight*> directionalLights;
    Vector<PointLight*> pointLights;
    Vector<SpotLight*> spotLights;

    void senderAreaLightDataToShader(ShaderProgram& shader, Drawable* receiver);
    void senderDirectionalLightDataToShader(ShaderProgram& shader, Drawable* receiver);
    void senderPointLightDataToShader(ShaderProgram& shader, Drawable* receiver);
    void senderSpotLightDataToShader(ShaderProgram& shader, Drawable* receiver);
public:
    LightContainer();
    ~LightContainer();

    void addLight(AreaLight* light);
    void addLight(DirectionalLight* light);
    void addLight(PointLight* light);
    void addLight(SpotLight* light);

    void sendLightDataToShader(ShaderProgram& shader, Drawable* receiver);

    void clearAllLights();
};

#endif // LIGHTCONTAINER_H
    