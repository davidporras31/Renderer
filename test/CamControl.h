#ifndef CAMCONTROL_H
#define CAMCONTROL_H

#include "../include/Renderer.h"
#include <GLFW/glfw3.h>
#include "../include/Camera.h"

class CamControl
{
public:
    CamControl(Camera *camera, float sensitivity = 1.f) : camera(camera), sensitivity(sensitivity) {}
    void processInput(GLFWwindow *window);
    void processMouseMovement(double xoffset, double yoffset);

    void setSensitivity(float newSensitivity) { sensitivity = newSensitivity; }
    float getSensitivity() const { return sensitivity; }
private:
    // Move the camera in the specified direction based on its current orientation.
    void moveCamera(glm::vec2 direction);
    Camera *camera;
    float sensitivity;
};

#endif // CAMCONTROL_H