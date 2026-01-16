
#include "../../include/lights/Light.h"

Light::Light() {
    // Constructor implementation
}

Light::~Light() {
    // Destructor implementation
}

void Light::setPosition(const glm::vec3 &pos)
{
    position = pos;
}

glm::vec3 Light::getPosition() const
{
    return position;
}

void Light::setDirection(const glm::vec3 &dir)
{
    direction = dir;
}

glm::vec3 Light::getDirection() const
{
    return direction;
}

void Light::setColor(const Color &col)
{
    color = col;
}

Color Light::getColor() const
{
    return color;
}
   