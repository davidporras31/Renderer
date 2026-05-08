#ifndef DRAWCALL_H
#define DRAWCALL_H


#include "Drawable.h"
#include "ShaderProgram.h"
#include "Material.h"

/// @brief A struct that represents a draw call, containing a drawable object, an optional custom shader program, and an optional material.
struct DrawCall
{
    Drawable* drawable;
    ShaderProgram* custom_shader;
    Material* material;
    DrawCall(Drawable* drawable, ShaderProgram* custom_shader = nullptr, Material* material = nullptr):
    drawable(drawable), custom_shader(custom_shader), material(material){}
};


#endif //DRAWCALL_H