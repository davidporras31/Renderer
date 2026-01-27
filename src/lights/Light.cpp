
#include "../../include/lights/Light.h"

Light::Light(LightType type) {
    lightData.position.w = static_cast<float>(type);
}

Light::~Light() {
    // Destructor implementation
}

void Light::setPosition(const glm::vec3 &pos)
{
    lightData.position = glm::vec4(pos, lightData.position.w);
}

glm::vec3 Light::getPosition() const
{
    return glm::vec3(lightData.position);
}

void Light::setDirection(const glm::vec3 &dir)
{
    lightData.direction = glm::vec4(dir, lightData.direction.w);
}

glm::vec3 Light::getDirection() const
{
    return glm::vec3(lightData.direction);
}

void Light::setColor(const Color &col)
{
    lightData.color = col;
}

Color Light::getColor() const
{
    return lightData.color;
}
   