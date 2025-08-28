#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Transformable.h"

class Drawable : public Transformable
{
private:
    /* data */
public:
    virtual void draw() = 0;
};

#endif // DRAWABLE_H