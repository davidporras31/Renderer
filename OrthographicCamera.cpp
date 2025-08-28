#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
    : Camera(near, far), left(left), right(right), bottom(bottom), top(top)
{
}

void OrthographicCamera::recalculateProjection()
{
    this->projection = glm::ortho(left, right, bottom, top, near, far);
}
