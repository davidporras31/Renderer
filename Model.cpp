#include "Model.h"

void Model::draw(ShaderProgram *shader)
{
    for (unsigned int i = 0; i < meshes.getSize(); i++)
    {
        shader->setMat4("model", meshes[i].getTransform());
        meshes[i].draw(shader);
    }
}