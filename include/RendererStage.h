#ifndef RENDERERSTAGE_H
#define RENDERERSTAGE_H

#include <string>
#include "DrawCall.h"
class Renderer;

class RendererStage {
    bool debugMode = false;
public:
    virtual ~RendererStage() = default;
    virtual std::string getName() = 0;
    virtual void initialize(Renderer* renderer) = 0;
    virtual void execute(Renderer* renderer) = 0;

    bool getDebugMode() const { return debugMode; }
    void setDebugMode(bool mode) { debugMode = mode; }
    virtual void pushDrawCall(DrawCall* drawCall) = 0;
};
#endif // RENDERERSTAGE_H