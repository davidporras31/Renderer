#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Transformable.h"
#include "ShaderProgram.h"

class Drawable : public Transformable
{
private:
    float modelMaxSize = 1000.0f; // Default maximum size
public:
    virtual void draw(ShaderProgram * shader) = 0;
    float getRenderRadius() const;
    void setModelMaxSize(float size) { modelMaxSize = size; }
};

#endif // DRAWABLE_H