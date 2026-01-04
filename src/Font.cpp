#include "../include/Font.h"
FT_Library Font::library;
Font::Font(std::filesystem::path path)
{
    FT_Error error = FT_New_Face(library,
                                 path.c_str(),
                                 0,
                                 &face);
    if (error)
    {
        throw std::runtime_error(std::string("FT2 fail to load font: ").append(path).append(" ").append(errorName(error)));
    }
}
Font::~Font()
{
    FT_Done_Face(face);
    for (auto &&i : cash)
    {
        delete i.second.texture;
    }
}
FT_Face *Font::getFace()
{
    return &face;
}
Character Font::genChar(const char c)
{
    auto it = cash.find(c);
    if (it != cash.end())
        return it->second;
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
        throw std::runtime_error(std::string("FT2 Failed to load Glyph: ") + c);
    }

    int width = face->glyph->bitmap.width;
    int height = face->glyph->bitmap.rows;

    unsigned char *flipped_buffer = new unsigned char[width * height];
    for (int y = 0; y < height; y++)
    {
        memcpy(
            flipped_buffer + y * width,
            face->glyph->bitmap.buffer + (height - 1 - y) * width,
            width);
    }

    Texture *texture = new Texture();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    texture->loadFromMemory(GL_RED, width, height, flipped_buffer);
    delete[] flipped_buffer;
    return cash.insert({c,
                        Character{
                            texture,
                            glm::ivec2(width, height),
                            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                            (unsigned int)face->glyph->advance.x}})
        .first->second;
}
void Font::init()
{
    FT_Error error = FT_Init_FreeType(&library);
    if (error)
    {
        throw std::runtime_error(std::string("FT2 fail to load: ").append(errorName(error)));
    }
}

void Font::uninit()
{
    FT_Done_FreeType(library);
}

const char *Font::errorName(FT_Error error)
{
#define FT_ERRORDEF_(name, value, reson) \
    case value:                          \
        ret = reson;                     \
        break;
#define FT_NOERRORDEF_(name, value, reson)

    const char *ret;
    switch (error)
    {
#include <freetype/fterrdef.h>
    }
#undef FT_ERRORDEF_
#undef FT_NOERRORDEF_
    return ret;
}

#ifdef TESTMODE
static GLFWwindow *initTestFontGL()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(1, 1, "LearnOpenGL", NULL, NULL);
    gladLoadGL((GLADloadfunc)glfwGetProcAddress);
    glfwMakeContextCurrent(window);
    Font::init();
    return window;
}
TEST("Font", "Font init")
{
    GLFWwindow *window = initTestFontGL();
    REC_NOT_NULL(window);
}
TEST("Font", "Character generation")
{
    initTestFontGL();
    Font font("./test/FreeSans.ttf");
    Character c = font.genChar('A');
    REC_NOT_NULL(c.texture);
}
TEST("Font", "Character caching")
{
    initTestFontGL();
    Font font("./test/FreeSans.ttf");
    Character c1 = font.genChar('A');
    Character c2 = font.genChar('A');
    REC_NOT_NULL(c1.texture);
    REC_NOT_NULL(c2.texture);
    REC_EQL(c1.texture, c2.texture);
}
#endif // TESTMODE