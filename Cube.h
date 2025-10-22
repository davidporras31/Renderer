#ifndef Cube_h
#define Cube_h
#include "Drawable.h"
#include <glad/gl.h>

class Cube: public Drawable
{
private:
    unsigned int VAO,VBO,EBO;
public:
    Cube();
    ~Cube();
    void draw(ShaderProgram* shader) override;
};

#endif // Cube_h