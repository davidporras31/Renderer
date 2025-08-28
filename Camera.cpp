#include "Camera.h"

Camera::Camera(float near, float far): near(near), far(far), dirty(true)
{
}

glm::mat4 *Camera::getProjection()
{
    if (dirty) {
        recalculateProjection();
        dirty = false;
    }
    return &projection;
}