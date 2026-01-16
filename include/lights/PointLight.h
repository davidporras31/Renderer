
#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

// Represents a point light source
class PointLight : public Light {
private:
    float range;
public:
    PointLight();
    ~PointLight();

    void setRange(float r);
    float getRange() const;

    virtual bool afectsDrawable(const glm::vec3 &pos, const float radius) const override;
};

#endif // POINTLIGHT_H
    