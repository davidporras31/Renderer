#ifndef RENDERERSTAGE_H
#define RENDERERSTAGE_H

#include <string>
#include "DrawCall.h"
class Renderer;

class RendererStage {
public:
    virtual ~RendererStage() = default;
    virtual std::string getName() = 0;
    virtual void initialize(Renderer* renderer) = 0;
    virtual void execute(Renderer* renderer) = 0;
    virtual void pushDrawCall(DrawCall* drawCall) = 0;
};
#endif // RENDERERSTAGE_H