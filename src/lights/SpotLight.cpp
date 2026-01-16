
#include "../../include/lights/SpotLight.h"

SpotLight::SpotLight() {
    // Constructor implementation
}

SpotLight::~SpotLight() {
    // Destructor implementation
}

void SpotLight::setRange(float r) {
    range = r;
}
float SpotLight::getRange() const {
    return range;
}
void SpotLight::setAngle(float a) {
    angle = a;
}
float SpotLight::getAngle() const {
    return angle;
}
bool SpotLight::afectsDrawable(const glm::vec3 &pos, const float radius) const {
    // Simple distance-based check for spotlight effect
    // In a real implementation, you would also consider the spotlight's direction and or angle if it's not take too much performance 
    return glm::distance(this->getPosition(), pos) <= this->range + radius;
}