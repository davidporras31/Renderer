#include "../../include/stage/ForwardGeometry.h"

void ForwardGeometry::draw(DrawCall *drawCall)
{
    ShaderProgram* shader = drawCall->custom_shader;
    if(!shader) {
        shader = defaultShader;
    }
    shader->use();
    //TODO use UBO for camera
    shader->setMat4("projection", camera->getProjection());
    shader->setMat4("view", camera->getTransform());
    shader->setMat4("model", drawCall->drawable->getTransform());

    try {
        shader->setVec3("viewPos", camera->getGlobalPosition());
    } catch (...) {
        // Ignore if the shader does not have viewPos uniform
    }
    shader->setUBO("LightDataUBO", getLightDataUBO());

    if(drawCall->material) {
        shader->setMaterial("material", *drawCall->material);
    }
    else {
        shader->setMaterial("material", defaultMaterial);
    }

    drawCall->drawable->draw(shader);
}