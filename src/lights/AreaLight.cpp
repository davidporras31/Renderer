
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
    this->getData() = glm::vec4(s, 0.0f);
}

glm::vec3 AreaLight::getSize() const
{
    return glm::vec3(this->getData());
}

bool AreaLight::afectsDrawable(const glm::vec3 &pos, const float radius) const
{
    glm::vec3 radpoint = {this->getData().x / 2, this->getData().y / 2, this->getData().z / 2};
    return glm::distance(this->getPosition() + radpoint, pos) <= glm::distance({0, 0, 0}, radpoint) + radius;
}
