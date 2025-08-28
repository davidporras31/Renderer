#ifndef TRIANGLETEST_H
#define TRIANGLETEST_H

#include <glad/gl.h>
#include "../Drawable.h"


class TriangleTest : public Drawable
{
private:
    unsigned int VAO, VBO;
public:
    TriangleTest();
    ~TriangleTest();
    void draw() override;
};

#endif // TRIANGLETEST_H