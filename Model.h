#ifndef MODEL_H
#define MODEL_H

#include "Drawable.h"
#include "Vector.h"
#include "Mesh.h"

class Model : public Drawable {
private:
    Vector<Mesh, unsigned int> meshes;
public:
    Model() = default;
    virtual ~Model() = default;
    void draw(ShaderProgram* shader) override;
};

#endif // MODEL_H