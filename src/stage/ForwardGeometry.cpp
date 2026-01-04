#include "../../include/stage/ForwardGeometry.h"

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

    if(drawCall->material) {
        shader->setMaterial("material", *drawCall->material);
    }
    else {
        shader->setMaterial("material", defaultMaterial);
    }

    drawCall->drawable->draw(shader);
}