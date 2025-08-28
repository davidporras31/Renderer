#include "Transformable.h"

glm::mat4 *Transformable::getTransform()
{ 
    if (dirty) {
        transform = glm::mat4(1.0f);
        transform = glm::scale(transform, scale);
        transform = glm::rotate(transform, rotation.x, glm::vec3(1, 0, 0));
        transform = glm::rotate(transform, rotation.y, glm::vec3(0, 1, 0));
        transform = glm::rotate(transform, rotation.z, glm::vec3(0, 0, 1));
        transform = glm::translate(transform, position);
        dirty = false;
    }
    return &transform; 
}