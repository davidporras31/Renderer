#include "CamControl.h"

void CamControl::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        moveCamera({0, 1});
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        moveCamera({0, -1});
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        moveCamera({1, 0});
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        moveCamera({-1, 0});
}

void CamControl::processMouseMovement(double xoffset, double yoffset)
{
    glm::vec3 rotation = camera->getRotation();
    rotation.x += static_cast<float>(-yoffset * 0.016) * sensitivity;
    rotation.y += static_cast<float>(-xoffset * 0.016) * sensitivity;
    camera->setRotation(rotation);
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
    position += forward * direction.y * sensitivity * 2.f;
    position += right * direction.x * sensitivity * 2.f;
    camera->setPosition(position);
}
