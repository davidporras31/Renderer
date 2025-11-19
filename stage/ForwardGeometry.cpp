#include "ForwardGeometry.h"

void ForwardGeometry::draw(DrawCall *drawCall)
{
    ShaderProgram* shader = drawCall->custom_shader;
    if(!shader) {
        shader = defaultShader;
    }
    shader->use();
    shader->setMat4("projection", camera->getProjection());
    shader->setMat4("view", camera->getTransform());
    shader->setMat4("model", drawCall->drawable->getTransform());

    for(size_t i = 0; i < drawCall->textures.size(); ++i) {
        drawCall->textures[i]->use(i);
    }

    drawCall->drawable->draw(shader);
}