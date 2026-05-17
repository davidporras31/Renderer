#include "CamControl.h"

void CamControl::processMouseMovement(double xoffset, double yoffset)
{
    if (clicked)
    {
        glm::vec3 rotation = camera->getRotation();
        rotation.x += static_cast<float>(-yoffset * 0.016) * sensitivity;
        rotation.y += static_cast<float>(-xoffset * 0.016) * sensitivity;
        rotation.x = std::clamp(rotation.x, -glm::half_pi<float>(), glm::half_pi<float>());
        camera->setRotation(rotation);
    }
}

void CamControl::moveCamera(glm::vec2 direction)
{
    glm::vec3 position = camera->getPosition();
    glm::vec3 rotation = camera->getRotation();
    
    glm::vec3 forward = {
        cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y)),
        sin(glm::radians(rotation.x)),
        cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y))
    };
    glm::vec3 right = {
        cos(glm::radians(rotation.y)),
        0,
        -sin(glm::radians(rotation.y))
    };
    position += forward * direction.y * sensitivity * 0.25f;
    position += right * direction.x * sensitivity * 0.25f;
    camera->setPosition(position);
}
