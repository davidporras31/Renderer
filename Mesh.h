#ifndef MESH_H
#define MESH_H

#include "Drawable.h"
#include "Vector.h"
#include <glad/gl.h>
#include <glm/glm.hpp>

class Mesh : public Drawable
{
private:
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };
    Vector<Vertex, unsigned int> vertices;
    Vector<unsigned int, unsigned int> indices;
    unsigned int VAO, VBO, EBO;
public:
    Mesh() = default;
    virtual ~Mesh() = default;
    void draw(ShaderProgram *shader) override;
};

#endif // MESH_H