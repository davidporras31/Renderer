
#ifndef AREALIGHT_H
#define AREALIGHT_H

#include "Light.h"

// Represents an area light source
// with specified width and height.
class AreaLight : public Light {
private:
public:
    AreaLight();
    ~AreaLight();

    void setSize(const glm::vec3& s);
    glm::vec3 getSize() const;

    virtual bool afectsDrawable(const glm::vec3 &pos, const float radius) const override;
};

#endif // AREALIGHT_H
