#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/gl.h>
#include <glm/vec3.hpp>

class Texture
{
protected:
    GLuint ID;
public:
    Texture();
    ~Texture();

    static GLint getFromatFromChannels(int channels);
    static GLint getChannelsFromFormat(GLint format);

    virtual void use(GLenum textureUnit = 0) const = 0;
    virtual void resize(glm::ivec3 size) = 0;
    GLuint getID() const;
};

#endif  //TEXTURE_H