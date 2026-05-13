#ifndef CAMCONTROL_H
#define CAMCONTROL_H

#include "../include/Renderer.h"
#include <GLFW/glfw3.h>
#include "../include/Camera.h"

/// @brief A class to control the camera using keyboard and mouse input.
/// This class allows the user to move the camera using the WASD keys and rotate it by clicking and dragging the mouse.
class CamControl
{
public:
    /// @brief Construct a new CamControl object
    /// @param camera Pointer to the camera to control
    /// @param sensitivity Mouse movement sensitivity (default is 1.0f)
    CamControl(Camera *camera, float sensitivity = 1.f) : camera(camera), sensitivity(sensitivity) {}
    void processMouseMovement(double xoffset, double yoffset);

    void setSensitivity(float newSensitivity) { sensitivity = newSensitivity; }
    float getSensitivity() const { return sensitivity; }

    void setClicked(bool val){clicked = val;}
    // Move the camera in the specified direction based on its current orientation.
    void moveCamera(glm::vec2 direction);
private:
    Camera *camera;
    float sensitivity;
    bool clicked = false;
};

#endif // CAMCONTROL_H