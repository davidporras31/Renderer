#ifndef SPRITE_H
#define SPRITE_H

#include "Drawable.h"
#include <glad/gl.h>

class Sprite: public Drawable
{
private:
    GLuint VAO,VBO,EBO;
public:
    Sprite();
    ~Sprite();
    void draw() override;
};

#endif //SPRITE_H