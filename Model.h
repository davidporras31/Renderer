#ifndef MODEL_H
#define MODEL_H

#include "Drawable.h"
#include "Vector.h"
#include "Mesh.h"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model : public Drawable {
private:
    Vector<Mesh, unsigned int> meshes;
    Vector<Material, unsigned int> materials;
    static Assimp::Importer* importer;
    void processNode(aiNode* node, const aiScene* scene);
    Material loadMaterial(aiMaterial* aiMat);
public:
    Model() = default;
    virtual ~Model() = default;

    static void init();

    void draw(ShaderProgram* shader) override;
    void open(const std::string& path);
};

#endif // MODEL_H