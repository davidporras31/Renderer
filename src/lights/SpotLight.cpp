
#include "../../include/lights/SpotLight.h"

SpotLight::SpotLight()
    : Light(LightType::Spot)
{
    // Constructor implementation
}

SpotLight::~SpotLight() {
    // Destructor implementation
}

void SpotLight::setRange(float r) {
    this->getData().x = r;
}
float SpotLight::getRange() const {
    return this->getData().x;
}
void SpotLight::setAngle(float a) {
    this->getData().y = a;
}
float SpotLight::getAngle() const {
    return this->getData().y;
}
bool SpotLight::afectsDrawable(const glm::vec3 &pos, const float radius) const {
    // Simple distance-based check for spotlight effect
    // In a real implementation, you would also consider the spotlight's direction and or angle if it's not take too much performance
    return glm::distance(this->getPosition(), pos) <= this->getData().x + radius;
}