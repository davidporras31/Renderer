#include "../include/Drawable.h"

float Drawable::getRenderRadius() const
{
    glm::vec3 scale = getScale();
    return std::max({scale.x, scale.y, scale.z}) * modelMaxSize;
}