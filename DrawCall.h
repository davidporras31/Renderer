#ifndef DRAWCALL_H
#define DRAWCALL_H


#include "Drawable.h"
#include "ShaderProgram.h"
#include "Texture.h"

struct DrawCall
{
    Drawable* drawable;
    ShaderProgram* custom_shader;
    std::vector<Texture*> textures;
    DrawCall(Drawable* drawable, ShaderProgram* custom_shader = nullptr):
    drawable(drawable), custom_shader(custom_shader){}
};


#endif //DRAWCALL_H