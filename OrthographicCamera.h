#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "Camera.h"

class OrthographicCamera : public Camera
{
private:
    float left,right,bottom,top;
public:
    OrthographicCamera(float left, float right, float bottom, float top, float near, float far);
    void recalculateProjection() override;
};

#endif // ORTHOGRAPHICCAMERA_H