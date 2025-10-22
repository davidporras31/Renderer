#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Transformable.h"
#include "ShaderProgram.h"

class Drawable : public Transformable
{
private:
    /* data */
public:
    virtual void draw(ShaderProgram * shader) = 0;
};

#endif // DRAWABLE_H