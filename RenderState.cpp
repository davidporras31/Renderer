#include "RenderState.h"

RenderState::RenderState(Drawable *drawable, ShaderProgram *custom_shader)
    :drawable(drawable),custom_shader(custom_shader)
{

}

void RenderState::addTexture(Texture *texture)
{
    this->textures.push_back(texture);
}

void RenderState::draw()
{
    for (auto &&i : this->textures)
    {
        i->use();
    }
    this->drawable->draw();
}

Drawable *RenderState::getDrawable()
{
    return this->drawable;
}

ShaderProgram *RenderState::getShaderProgram()
{
    return this->custom_shader;
}
