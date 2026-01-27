#include "../include/Model.h"

Assimp::Importer *Model::importer = nullptr;

glm::vec3 Model::processNode(aiNode *node, const aiScene *scene)
{
    glm::vec3 maxPos(0.0f);
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.emplaceBack(mesh, &maxPos);
        meshes.last().setParent(this);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        glm::vec3 childMaxPos = processNode(node->mChildren[i], scene);
        maxPos.x = std::max(maxPos.x, childMaxPos.x);
        maxPos.y = std::max(maxPos.y, childMaxPos.y);
        maxPos.z = std::max(maxPos.z, childMaxPos.z);
    }

    return maxPos;
}

void Model::loadMaterial(aiMaterial *aiMat)
{
    this->materials.emplaceBack();
    Material& material = this->materials.last();

    aiColor4D color(0.f, 0.f, 0.f, 1.f);
    aiString texPath;
    float value;

    if (aiGetMaterialColor(aiMat, AI_MATKEY_COLOR_DIFFUSE, &color) == AI_SUCCESS)
    {
        material.albedo = glm::vec3(color.r, color.g, color.b);
    }
    if (aiMat->GetTexture(aiTextureType_BASE_COLOR, 0, &texPath) == AI_SUCCESS)
    {
        material.albedo.emplace<Texture>().load(texPath.C_Str());
    }else if (aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &texPath) == AI_SUCCESS)
    {
        material.albedo.emplace<Texture>().load(texPath.C_Str());
    }

    if (aiMat->Get(AI_MATKEY_METALLIC_FACTOR, value) == AI_SUCCESS)
    {
        material.metallic = value;
    }
    if (aiMat->GetTexture(aiTextureType_METALNESS, 0, &texPath) == AI_SUCCESS)
    {
        material.metallic.emplace<Texture>().load(texPath.C_Str());
    }

    if (aiMat->Get(AI_MATKEY_ROUGHNESS_FACTOR, value) == AI_SUCCESS)
    {
        material.roughness = value;
    }
    if (aiMat->GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, 0, &texPath) == AI_SUCCESS)
    {
        material.roughness.emplace<Texture>().load(texPath.C_Str());
    }

#define AI_MATKEY_AMBIENT_OCCLUSION_FACTOR "$mat.ao_factor", 0, 0
    if (aiMat->Get(AI_MATKEY_AMBIENT_OCCLUSION_FACTOR, value) == AI_SUCCESS)
    {
        material.ao = value;
    }
#undef AI_MATKEY_AMBIENT_OCCLUSION_FACTOR
    if (aiMat->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &texPath) == AI_SUCCESS)
    {
        material.ao.emplace<Texture>().load(texPath.C_Str());
    }

    if (aiGetMaterialColor(aiMat, AI_MATKEY_COLOR_EMISSIVE, &color) == AI_SUCCESS)
    {
        material.emissive = glm::vec3(color.r, color.g, color.b);
    }
    if (aiMat->GetTexture(aiTextureType_EMISSIVE, 0, &texPath) == AI_SUCCESS)
    {
        material.emissive.emplace<Texture>().load(texPath.C_Str());
    }

    if (aiMat->GetTexture(aiTextureType_NORMALS, 0, &texPath) == AI_SUCCESS)
    {
        material.normalMap.emplace().load(texPath.C_Str());
    }
}

void Model::init()
{
    importer = new Assimp::Importer();
}

void Model::draw(ShaderProgram *shader)
{
    for (unsigned int i = 0; i < meshes.getSize(); i++)
    {
        try
        {
            shader->setMaterial("material", materials[meshes[i].getMaterialIndex()]);
        }
        catch(...)
        {
            //do nothing
        }
        
        shader->setMat4("model", meshes[i].getTransform());
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
        loadMaterial(aiMat);
    }
    glm::vec3 maxPos = processNode(scene->mRootNode, scene);
    setModelMaxSize(std::max(maxPos.x, std::max(maxPos.y, maxPos.z)));

    importer->FreeScene();
}
