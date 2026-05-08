#ifndef RENDERERSTAGE_H
#define RENDERERSTAGE_H

#include <string>
#include "DrawCall.h"
class Renderer;

/// @brief an abstract class that represents a stage in the rendering pipeline. Each stage is responsible for executing a specific part of the rendering process, such as geometry processing, lighting, or post-processing. The renderer manages the stages and executes them in order during the rendering loop.
class RendererStage {
    bool debugMode = false;
public:
    virtual ~RendererStage() = default;
    virtual std::string getName() = 0;
    virtual void initialize(Renderer* renderer) = 0;
    virtual void execute(Renderer* renderer) = 0;
    virtual void cleanup(Renderer* renderer) = 0;

    bool getDebugMode() const { return debugMode; }
    void setDebugMode(bool mode) { debugMode = mode; }
    virtual void pushDrawCall(DrawCall* drawCall) = 0;
};
#endif // RENDERERSTAGE_H