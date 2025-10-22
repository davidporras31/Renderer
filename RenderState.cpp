#include "RenderState.h"

RenderState::RenderState(Drawable *drawable, ShaderProgram *custom_shader)
    :drawable(drawable),custom_shader(custom_shader)
{

}

void RenderState::addTexture(Texture *texture)
{
    this->textures.push_back(texture);
}

void RenderState::draw(Camera * camera, ShaderProgram* global)
{
    for (size_t i = 0; i < this->textures.size(); i++)
    {
        this->textures[i]->use(i);
    }
    ShaderProgram * tmp = global;
    if(this->custom_shader)
        tmp = this->custom_shader;
    tmp->use();
    tmp->setMat4("projection", camera->getProjection());
    tmp->setMat4("view", camera->getTransform());
    tmp->setMat4("model", this->drawable->getTransform());
    this->drawable->draw(tmp);
}

Drawable *RenderState::getDrawable()
{
    return this->drawable;
}

ShaderProgram *RenderState::getShaderProgram()
{
    return this->custom_shader;
}
