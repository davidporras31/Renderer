#include "../../include/stage/UIRender.h"

void UIRender::draw(DrawCall *drawCall)
{
    ShaderProgram* shader = drawCall->custom_shader;
    if(!shader) {
        shader = defaultShader;
    }
    shader->use();
    shader->setMat4("projection", camera->getProjection());
    shader->setMat4("view", camera->getTransform());
    shader->setMat4("model", drawCall->drawable->getTransform());


    shader->setMaterial("material", *drawCall->material);

    drawCall->drawable->draw(shader);
}
