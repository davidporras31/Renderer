#ifndef MESH_H
#define MESH_H

#include "Drawable.h"
#include "Vector.h"
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <assimp/mesh.h>

class Mesh : public Drawable
{
private:
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };
    unsigned int VAO, VBO, EBO, size, materialIndex;
public:
    Mesh() = default;
    Mesh(aiMesh* mesh, glm::vec3 *maxPos);
    virtual ~Mesh();
    void draw(ShaderProgram *shader) override;

    unsigned int getMaterialIndex() const { return materialIndex; }
};

#endif // MESH_H