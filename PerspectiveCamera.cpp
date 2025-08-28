#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far)
    : Camera(near, far), fov(fov), aspect(aspect)
{
}
void PerspectiveCamera::recalculateProjection()
{
    projection = glm::perspective(glm::radians(fov), aspect, near, far);
}