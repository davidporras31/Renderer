
#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "Light.h"

// Represents a spotlight light source
class SpotLight : public Light {
private:
    float range;
    float angle;
public:
    SpotLight();
    ~SpotLight();

    void setRange(float r);
    float getRange() const;
    void setAngle(float a);
    float getAngle() const;

    virtual bool afectsDrawable(const glm::vec3 &pos, const float radius) const override;
};

#endif // SPOTLIGHT_H
    