#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformable
{
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    bool dirty;
    glm::mat4 transform;
public:
    Transformable() : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), dirty(true) {}
    void setPosition(const glm::vec3& pos) { position = pos; dirty = true; }
    glm::vec3 getPosition() const { return position; }
    void setRotation(const glm::vec3& rot) { rotation = rot; dirty = true; }
    glm::vec3 getRotation() const { return rotation; }
    void setScale(const glm::vec3& scl) { scale = scl; dirty = true; }
    glm::vec3 getScale() const { return scale; }
    glm::mat4& getTransform();
};

#endif // TRANSFORMABLE_H