#include "../include/Camera.h"

Camera::Camera(float near, float far): near(near), far(far), dirty(true)
{
}

glm::mat4 &Camera::getProjection()
{
    if (dirty) {
        recalculateProjection();
        dirty = false;
    }
    return projection;
}
void Camera::lookAt(const glm::vec3 &target, const glm::vec3 &up)
{
    glm::vec3 position = getGlobalPosition();
    projection = glm::lookAt(position, target, up);
    glm::mat4 localTransform = Transformable::toLocalTransform(projection, getTransform());
    setRotation(Transformable::getRotationFromTransform(localTransform));
    dirty = false; // we just updated the projection, so we need to set dirty to false to avoid unnecessary recalculations
}