#ifndef COLOR_H
#define COLOR_H

#include <glm/glm.hpp>

typedef glm::vec4 Color; 


// Common color constants
namespace ConstColor
{
    const Color Black      = Color(0.0f, 0.0f, 0.0f, 1.0f);
    const Color White      = Color(1.0f, 1.0f, 1.0f, 1.0f);
    const Color Red        = Color(1.0f, 0.0f, 0.0f, 1.0f);
    const Color Green      = Color(0.0f, 1.0f, 0.0f, 1.0f);
    const Color Blue       = Color(0.0f, 0.0f, 1.0f, 1.0f);
    const Color Yellow     = Color(1.0f, 1.0f, 0.0f, 1.0f);
    const Color Magenta    = Color(1.0f, 0.0f, 1.0f, 1.0f);
    const Color Cyan       = Color(0.0f, 1.0f, 1.0f, 1.0f);
    const Color Dark_Modern_Gray = Color(0.2f,0.3f,0.3f, 1.0f);
    const Color Transparent= Color(0.0f, 0.0f, 0.0f, 0.0f);
};

#endif // COLOR_H