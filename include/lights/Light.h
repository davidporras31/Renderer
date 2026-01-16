
#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "../Color.h"


class Light
{
private:
    glm::vec3 position;
    glm::vec3 direction;
    Color color;

public:
    Light();
    ~Light();

    virtual bool afectsDrawable(const glm::vec3 &pos, const float radius) const = 0;

    void setPosition(const glm::vec3 &pos);
    glm::vec3 getPosition() const;
    void setDirection(const glm::vec3 &dir);
    glm::vec3 getDirection() const;
    void setColor(const Color &col);
    Color getColor() const;
};

#endif // LIGHT_H
