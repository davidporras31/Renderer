#ifndef TRIANGLETEST_H
#define TRIANGLETEST_H

#include <glad/gl.h>
#include "../Drawable.h"


class TriangleTest : public Drawable
{
private:
    unsigned int VAO;
public:
    TriangleTest();
    ~TriangleTest();
    void draw(ShaderProgram* shader) override;
};

#endif // TRIANGLETEST_H