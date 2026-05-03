#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <algorithm>

/// @brief A class representing an object that can be transformed in 3D space, with support for hierarchical transformations.
/// The Transformable class allows you to set and get the position, rotation, and scale of an object, as well as its parent-child relationships. It also provides methods to retrieve the global transformation of the object, which takes into account the transformations of its parent objects.
class Transformable
{
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    bool dirty;
    glm::mat4 transform;
    Transformable* parent;
    std::vector<Transformable*> children;
public:
    Transformable() : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), dirty(true), parent(nullptr) {}
    ~Transformable();

    void setPosition(const glm::vec3& pos) { position = pos; dirty = true; }
    glm::vec3 getPosition() const { return position; }
    void setRotation(const glm::vec3& rot) { rotation = rot; dirty = true; }
    glm::vec3 getRotation() const { return rotation; }
    void setScale(const glm::vec3& scl) { scale = scl; dirty = true; }
    glm::vec3 getScale() const { return scale; }

    /// @brief Get the global position of the object, taking into account its parent's transformations.
    /// @return The global position of the object.
    glm::vec3 getGlobalPosition();
    /// @brief Get the global rotation of the object, taking into account its parent's transformations.
    /// @return The global rotation of the object.
    glm::vec3 getGlobalRotation();
    /// @brief Get the global scale of the object, taking into account its parent's transformations.
    /// @return The global scale of the object.
    glm::vec3 getGlobalScale();

    /// @brief Set the parent of the transformable object.
    /// @param par The parent transformable object. If set to nullptr, the object will have no parent.
    void setParent(Transformable* par);
    Transformable* getParent() const { return parent; }

    glm::mat4& getTransform();

    static glm::vec3 getPositionFromTransform(const glm::mat4& mat);
    static glm::vec3 getRotationFromTransform(const glm::mat4& mat);
    static glm::vec3 getScaleFromTransform(const glm::mat4& mat);
    static glm::mat4 toLocalTransform(const glm::mat4& global, const glm::mat4& parentGlobal);
};

#endif // TRANSFORMABLE_H