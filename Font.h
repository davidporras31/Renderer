#ifndef FONT_H
#define FONT_H


#include <ft2build.h>
#include FT_FREETYPE_H

#include <filesystem>
#include <stdexcept>
#include <glm/glm.hpp>
#include <map>
#include "Texture.h"

#include "Color.h"
#include "ShaderProgram.h"

struct Character {
    Texture* texture;
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class Font
{
private:
    static FT_Library library;
    FT_Face face;
    std::map<char,Character> cash;
public:
    Font(std::filesystem::path path);
    ~Font();
    FT_Face* getFace();
    Character genChar(const char c);
    static void init();
    static const char* errorName(FT_Error error);
};

#endif //FONT_H