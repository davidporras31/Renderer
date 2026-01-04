#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <vector>
#include "Drawable.h"
#include "Color.h"
#include "Font.h"
#include "Square.h"

class Text : public Drawable
{
private:
    struct DrawText
    {
        Texture* texture;
        Square square;
    };
    
    Font* font;
    std::string text;
    size_t size;
    Color color;
    bool dirty;
    std::vector<DrawText> chars;
    void remakeChars();
public:
    Text(Font* font, std::string text);
    //~Text();
    void draw(ShaderProgram* shader) override;
    void setColor(const Color& color);
};

#endif //TEXT_H