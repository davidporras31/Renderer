#include "Camera.h"

glm::mat4 *Camera::getProjection()
{
    if (dirty) {
        recalculateProjection();
        dirty = false;
    }
    return &projection;
}