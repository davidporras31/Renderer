#ifndef DRAWCALL_H
#define DRAWCALL_H


#include "Drawable.h"
#include "ShaderProgram.h"
#include "Material.h"

struct DrawCall
{
    Drawable* drawable;
    ShaderProgram* custom_shader;
    Material* material;
    DrawCall(Drawable* drawable, ShaderProgram* custom_shader = nullptr, Material* material = nullptr):
    drawable(drawable), custom_shader(custom_shader), material(material){}
};


#endif //DRAWCALL_H