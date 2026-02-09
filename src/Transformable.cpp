#include "../include/Transformable.h"

Transformable::~Transformable()
{
    if(!parent)
        return;
    auto it = std::find(parent->children.begin(),parent->children.end(),this);
    if(it != parent->children.end())
        parent->children.erase(it);
        
}

glm::vec3 Transformable::getGlobalPosition()
{
    return getPositionFromTransform(this->getTransform());
}

glm::vec3 Transformable::getGlobalRotation()
{
    return getRotationFromTransform(this->getTransform());
}
glm::vec3 Transformable::getGlobalScale()
{
    return getScaleFromTransform(this->getTransform());
}
void Transformable::setParent(Transformable *par)
{
    if(par == this)
        return;
    parent = par;
    dirty = true;
    if(par) par->children.push_back(this);
}

glm::mat4& Transformable::getTransform()
{ 
    if (dirty) {
        if(children.size()!= 0)
        for (size_t i = 0; i < children.size(); i++)
        {
            children[i]->dirty = true;
        }
        
        
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, position);
        transform = glm::rotate(transform, rotation.x, glm::vec3(1, 0, 0));
        transform = glm::rotate(transform, rotation.y, glm::vec3(0, 1, 0));
        transform = glm::rotate(transform, rotation.z, glm::vec3(0, 0, 1));
        transform = glm::scale(transform, scale);
        if(parent)
        {
            transform = parent->getTransform() * transform; 
        }
        dirty = false;
    }
    return transform; 
}

glm::vec3 Transformable::getPositionFromTransform(const glm::mat4 &mat)
{
    return glm::vec3(mat[3][0],mat[3][1],mat[3][2]);
}

glm::vec3 Transformable::getRotationFromTransform(const glm::mat4 &mat)
{
    return glm::vec3(glm::eulerAngles(glm::quat(mat)));
}

glm::vec3 Transformable::getScaleFromTransform(const glm::mat4 &mat)
{
    return glm::vec3(glm::length(mat[0]), glm::length(mat[1]), glm::length(mat[2]));
}

glm::mat4 Transformable::toLocalTransform(const glm::mat4 &global, const glm::mat4 &parentGlobal)
{
    return glm::inverse(parentGlobal) * global;
}
