#include "Text.h"

Text::Text(Font *font, std::string text)
    :font(font),text(text),size(150),color(ConstColor::Black),dirty(true)
{
    remakeChars();
}

void Text::draw(ShaderProgram* shader) 
{
    if(dirty)
        remakeChars();
    
    shader->setVec4("text_color", color);
    
    for (auto &&i : chars)
    {
        i.texture->use();
        shader->setMat4("model", i.square.getTransform());
        i.square.draw(shader);
    }
    
}

void Text::setColor(const Color &color)
{
    this->color = color;
}

void Text::remakeChars()
{
    chars.clear();
    chars.resize(text.length());
    FT_Set_Pixel_Sizes(*font->getFace(),0,size);
    glm::vec2 pos = {0,0};
    for (size_t i = 0; i < chars.size(); i++)
    {
        char c = text[i];
        Character ch = font->genChar(c);
        Square* square = &chars[i].square;
        chars[i].texture = ch.texture;
        square->setParent(this);
        
        if(c == '\n')
        {
            square->setScale({0,0,0});
            pos.y -= 2;
            pos.x = 0;
            continue;
        }
        if(c == ' ')
        {
            square->setScale({0,0,0});
            pos.x += 1;
            continue;
        }

        glm::vec2 cpos = pos;
        cpos += glm::vec2(ch.Bearing) / (float)size;
        square->setPosition({cpos,0});
        //if(ch.Size.y != 0)
        square->setScale({ch.Size.x / (float)size,(ch.Size.y) / (float)size,1});
        int x = (ch.Advance>>6) + ch.Bearing.y;
        pos.x += x/(float)size;
    }
    
    
    dirty = false;
}
