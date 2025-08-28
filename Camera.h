#ifndef CAMERA_H
#define CAMERA_H

#include "Transformable.h"

class Camera : public Transformable
{
private:
    glm::mat4 projection;
    float near, far;
    bool dirty;
public:
    virtual void recalculateProjection() = 0;
    glm::mat4* getProjection();
};

#endif // CAMERA_H