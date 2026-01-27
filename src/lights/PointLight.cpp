
#include "../../include/lights/PointLight.h"

PointLight::PointLight()
    : Light(LightType::Point)
{
    // Constructor implementation
}

PointLight::~PointLight() {
    // Destructor implementation
}

float PointLight::getRange() const
{
    return getLightData().data1.x;
}
void PointLight::setRange(float r)
{
    getLightData().data1.x = r;
}

bool PointLight::afectsDrawable(const glm::vec3 &pos, const float radius) const
{
    return glm::distance(this->getPosition(), pos) <= getLightData().data1.x + radius;
}