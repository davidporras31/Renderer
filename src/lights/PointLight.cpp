
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
    return this->getData().x;
}
void PointLight::setRange(float r)
{
    this->getData().x = r;
}

bool PointLight::afectsDrawable(const glm::vec3 &pos, const float radius) const
{
    return glm::distance(this->getPosition(), pos) <= this->getData().x + radius;
}