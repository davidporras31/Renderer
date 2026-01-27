
#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "../Color.h"

struct alignas(16) LightData // Ensure 16-byte alignment for GPU compatibility
{
    glm::vec4 position = glm::vec4(0.0f);        // w component can be used for different purposes (e.g., type of light)
    glm::vec4 direction = glm::vec4(0.0f);       // w component is unused
    Color color = Color(1.0f, 1.0f, 1.0f, 1.0f); // RGBA color
    glm::vec4 data1 = glm::vec4(1.0f);           // Additional data (e.g., intensity, range)
};

enum class LightType
{
    Directional,
    Point,
    Spot,
    Area
};

class Light
{
private:
    LightData lightData;

public:
    Light(LightType type);
    ~Light();

    virtual bool afectsDrawable(const glm::vec3 &pos, const float radius) const = 0;

    void setPosition(const glm::vec3 &pos);
    glm::vec3 getPosition() const;
    void setDirection(const glm::vec3 &dir);
    glm::vec3 getDirection() const;
    void setColor(const Color &col);
    Color getColor() const;

    LightData &getLightData() { return lightData; }
    const LightData &getLightData() const { return lightData; }
};

#endif // LIGHT_H
