#ifndef COLOR_H
#define COLOR_H



struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
    Color(float red, float green, float blue, float alpha = 1.0f)
        : r(red), g(green), b(blue), a(alpha) {}
};

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