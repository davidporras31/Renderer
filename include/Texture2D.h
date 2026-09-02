
#ifndef TEXURE2D_H
#define TEXURE2D_H

#include <stb/stb_image.h>
#include <stdexcept>

#include "Texture.h"

class Texture2D : public Texture
{
public:
    void use(GLenum textureUnit = 0) const override;
    void resize(glm::ivec3 size) override;
    void load(const char *path, bool mipmap = true);
    void loadFromMemory(GLint format, int width, int height, unsigned char *buffer, bool mipmap = true, bool clamp = false);
};

#endif // TEXURE2D_H
