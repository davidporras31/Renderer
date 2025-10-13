#ifndef SQUARE_H
#define SQUARE_H

#include "Drawable.h"
#include <glad/gl.h>

class Square: public Drawable
{
private:
    GLuint VAO,VBO,EBO;
public:
    Square();
    ~Square();
    void draw() override;
};

#endif //SQUARE_H