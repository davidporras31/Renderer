
#include "../../include/stage/DebugRender.h"

DebugRender::DebugRender() {
    // Constructor implementation
}

DebugRender::~DebugRender() {
    // Destructor implementation
}

void DebugRender::draw(DrawCall *drawCall)
{
    ShaderProgram* shader = defaultShader;
    shader->use();
    //TODO use UBO for camera
    shader->setMat4("projection", camera->getProjection());
    shader->setMat4("view", camera->getTransform());
    shader->setMat4("model", drawCall->drawable->getTransform());

    

    drawCall->drawable->draw(shader);
}
   