
#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"

// DirectionalLight used to simulate sunlight or other distant light sources
// It has a direction but no specific position, affecting all objects in the scene equally

class DirectionalLight : public Light {
private:
    // data
public:
    DirectionalLight();
    ~DirectionalLight();
    virtual bool afectsDrawable(const glm::vec3 &pos, const float radius) const override;
};

#endif // DIRECTIONALLIGHT_H
    