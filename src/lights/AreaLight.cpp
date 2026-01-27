
#include "../../include/lights/AreaLight.h"

AreaLight::AreaLight()
    : Light(LightType::Area)
{
    // Constructor implementation
}

AreaLight::~AreaLight()
{
    // Destructor implementation
}

void AreaLight::setSize(const glm::vec3 &s)
{
    getLightData().data1 = glm::vec4(s, 0.0f);
}

glm::vec3 AreaLight::getSize() const
{
    return glm::vec3(getLightData().data1);
}

bool AreaLight::afectsDrawable(const glm::vec3 &pos, const float radius) const
{
    glm::vec3 radpoint = {getLightData().data1.x / 2, getLightData().data1.y / 2, getLightData().data1.z / 2};
    return glm::distance(this->getPosition() + radpoint, pos) <= glm::distance({0, 0, 0}, radpoint) + radius;
}
