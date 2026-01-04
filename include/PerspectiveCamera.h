#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "Camera.h"

class PerspectiveCamera : public Camera
{
private:
    float fov, aspect;
public:
    PerspectiveCamera(float fov = 45.f, float aspect = 1.0f, float near = 0.1f, float far = 100.0f);
    void recalculateProjection() override;
};
#endif // PERSPECTIVECAMERA_H