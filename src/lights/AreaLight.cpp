
#include "../../include/lights/AreaLight.h"

AreaLight::AreaLight()
{
    // Constructor implementation
}

AreaLight::~AreaLight()
{
    // Destructor implementation
}

void AreaLight::setSize(const glm::vec3 &s)
{
    size = s;
}

glm::vec3 AreaLight::getSize() const
{
    return size;
}

bool AreaLight::afectsDrawable(const glm::vec3 &pos, const float radius) const
{
    glm::vec3 radpoint = {size.x / 2, size.y / 2, size.z / 2};
    return glm::distance(this->getPosition() + radpoint, pos) <= glm::distance({0, 0, 0}, radpoint) + radius;
}
