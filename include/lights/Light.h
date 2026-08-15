
#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "../Color.h"
#include "../Transformable.h"
#include "DebugProxy.h"

enum class LightType
{
    Directional,
    Point,
    Spot,
    Area
};

class Light : public Transformable
{
private:
    LightType type;
    bool dirty;
    Color color;
    glm::vec4 data;
    Drawable* debugProxies;
public:
    Light(LightType type);
    ~Light();

    LightType getType() const { return type; }

    virtual bool afectsDrawable(const glm::vec3 &pos, const float radius) const = 0;

    void setColor(const Color &col);
    Color getColor() const;

    glm::vec4 &getData() { return data; }
    const glm::vec4 &getData() const { return data; }

    Drawable* getDebugProxies() const { return debugProxies; }
};

struct alignas(16) LightData // Ensure 16-byte alignment for GPU compatibility
{
    glm::vec4 position = glm::vec4(0.0f);        // w component can be used for different purposes (e.g., type of light)
    glm::vec4 direction = glm::vec4(0.0f);       // w component is unused
    Color color = Color(1.0f, 1.0f, 1.0f, 1.0f); // RGBA color
    glm::vec4 data1 = glm::vec4(1.0f);           // Additional data (e.g., intensity, range)
 
    LightData() = default;
    LightData(Light *light) : position(light->getGlobalPosition(), (float)light->getType()),
                              direction(light->getGlobalRotation(), 0.f),
                              color(light->getColor()),
                              data1(light->getData())
    {};
};

#endif // LIGHT_H
