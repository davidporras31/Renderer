
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
    getLightData().data1.x = r;
}
float SpotLight::getRange() const {
    return getLightData().data1.x;
}
void SpotLight::setAngle(float a) {
    getLightData().data1.y = a;
}
float SpotLight::getAngle() const {
    return getLightData().data1.y;
}
bool SpotLight::afectsDrawable(const glm::vec3 &pos, const float radius) const {
    // Simple distance-based check for spotlight effect
    // In a real implementation, you would also consider the spotlight's direction and or angle if it's not take too much performance
    return glm::distance(this->getPosition(), pos) <= getLightData().data1.x + radius;
}