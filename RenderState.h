#ifndef RENDERSTATE_H
#define RENDERSTATE_H

#include "ShaderProgram.h"
#include "Texture.h"
#include "Drawable.h"
#include <vector>

class RenderState
{
private:
    Drawable* drawable;
    ShaderProgram* custom_shader;
    std::vector<Texture*> textures;
public:
    RenderState(Drawable* drawable, ShaderProgram* custom_shader = nullptr);
    //~RenderState();
    void addTexture(Texture* texture);
    void draw();
    Drawable* getDrawable();
    ShaderProgram* getShaderProgram();
};

#endif //RENDERSTATE_H