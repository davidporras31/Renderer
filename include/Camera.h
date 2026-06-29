#ifndef CAMERA_H
#define CAMERA_H

#include "Transformable.h"

class Camera : public Transformable
{
protected:
    float near, far;
    glm::mat4 projection;
private:
    bool dirty;
public:
    Camera(float near = 0.f, float far = 0.0f);
    virtual void recalculateProjection() = 0;
    glm::mat4& getProjection();
    /// @brief Make the camera look at a target point in world space.
    /// @param target The target point to look at.
    /// @param up The up direction for the camera. Defaults to (0, 1, 0).
    void lookAt(const glm::vec3& target, const glm::vec3& up = {0, 1, 0});
};

#endif // CAMERA_H