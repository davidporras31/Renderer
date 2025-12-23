#include "Model.h"

Assimp::Importer *Model::importer = nullptr;

void Model::processNode(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.pushBack(Mesh(mesh));
        meshes[meshes.getSize() - 1].setParent(this);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Material Model::loadMaterial(aiMaterial *aiMat)
{
    Material material;

    aiColor4D color(0.f, 0.f, 0.f, 1.f);
    aiString texPath;
    float value;

    if (aiGetMaterialColor(aiMat, AI_MATKEY_COLOR_DIFFUSE, &color) == AI_SUCCESS)
    {
        material.albedo = glm::vec3(color.r, color.g, color.b);
    }else if (aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &texPath) == AI_SUCCESS)
    {
        Texture albedoTex;
        albedoTex.load(texPath.C_Str());
        material.albedo = albedoTex;
    }
    
    if (aiMat->Get(AI_MATKEY_METALLIC_FACTOR, value) == AI_SUCCESS)
    {
        material.metallic = value;
    }else if (aiMat->GetTexture(aiTextureType_METALNESS, 0, &texPath) == AI_SUCCESS)
    {
        Texture metallicTex;
        metallicTex.load(texPath.C_Str());
        material.metallic = metallicTex;
    }
    
    if (aiMat->Get(AI_MATKEY_ROUGHNESS_FACTOR, value) == AI_SUCCESS)
    {
        material.roughness = value;
    }else if (aiMat->GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, 0, &texPath) == AI_SUCCESS)
    {
        Texture roughnessTex;
        roughnessTex.load(texPath.C_Str());
        material.roughness = roughnessTex;
    }
    
#define AI_MATKEY_AMBIENT_OCCLUSION_FACTOR "$mat.ao_factor", 0, 0
    if (aiMat->Get(AI_MATKEY_AMBIENT_OCCLUSION_FACTOR, value) == AI_SUCCESS)
    {
        material.ao = value;
    }else if (aiMat->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &texPath) == AI_SUCCESS)
    {
        Texture aoTex;
        aoTex.load(texPath.C_Str());
        material.ao = aoTex;
    }
    if (aiGetMaterialColor(aiMat, AI_MATKEY_COLOR_EMISSIVE, &color) == AI_SUCCESS)
    {
        material.emissive = glm::vec3(color.r, color.g, color.b);
    }else if (aiMat->GetTexture(aiTextureType_EMISSIVE, 0, &texPath) == AI_SUCCESS)
    {
        Texture emissiveTex;
        emissiveTex.load(texPath.C_Str());
        material.emissive = emissiveTex;
    }

    if (aiMat->GetTexture(aiTextureType_NORMALS, 0, &texPath) == AI_SUCCESS)
    {
        Texture normalMap;
        normalMap.load(texPath.C_Str());
        material.normalMap = normalMap;
    }

    return material;
}

void Model::init()
{
    importer = new Assimp::Importer();
}

void Model::draw(ShaderProgram *shader)
{
    for (unsigned int i = 0; i < meshes.getSize(); i++)
    {
        shader->setMat4("model", meshes[i].getTransform());
        shader->setMaterial("material", materials[meshes[i].getMaterialIndex()]);
        meshes[i].draw(shader);
    }
}

void Model::open(const std::string &path)
{
    const aiScene *scene = importer->ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        throw std::runtime_error("Failed to load model: " + path + " Error: " + importer->GetErrorString());
    }
    meshes.reserve(scene->mNumMeshes);
    materials.reserve(scene->mNumMaterials);
    for (unsigned int i = 0; i < scene->mNumMaterials; i++)
    {
        aiMaterial *aiMat = scene->mMaterials[i];
        materials.pushBack(loadMaterial(aiMat));
    }
    processNode(scene->mRootNode, scene);

    importer->FreeScene();
}
