
#include "../../include/lights/PointLight.h"

PointLight::PointLight() {
    // Constructor implementation
}

PointLight::~PointLight() {
    // Destructor implementation
}

float PointLight::getRange() const
{
    return range;
}
void PointLight::setRange(float r)
{
    range = r;
}

bool PointLight::afectsDrawable(const glm::vec3 &pos, const float radius) const
{
    return glm::distance(this->getPosition(), pos) <= range + radius;
}