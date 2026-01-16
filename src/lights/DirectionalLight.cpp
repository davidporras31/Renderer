
#include "../../include/lights/DirectionalLight.h"

DirectionalLight::DirectionalLight() {
    // Constructor implementation
}

DirectionalLight::~DirectionalLight() {
    // Destructor implementation
}

bool DirectionalLight::afectsDrawable(const glm::vec3 &pos, const float radius) const
{
    // Directional lights affect all drawables in the scene
    return true;
}
   