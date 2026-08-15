
#include "../../include/lights/Light.h"

Light::Light(LightType type)
    :dirty(false)
{
    switch (type)
    {
    case LightType::Directional:
        debugProxies = new DebugProxy::Directional();
        break;
    case LightType::Point:
        debugProxies = new DebugProxy::Point();
        break;
    case LightType::Spot:
        debugProxies = new DebugProxy::Spot();
        break;
    case LightType::Area:
        debugProxies = new DebugProxy::Area();
        break;
    }
    debugProxies->setParent(this);
}

Light::~Light() {
    delete debugProxies;
}

void Light::setColor(const Color &col)
{
    this->color = col;
}

Color Light::getColor() const
{
    return this->color;
}
   