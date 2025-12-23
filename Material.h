#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include <variant>
#include <optional>
#include <glm/glm.hpp>

struct Material
{
    std::variant<glm::vec3, Texture> albedo = glm::vec3(1.0f);
    std::variant<float, Texture> metallic = 0.0f;
    std::variant<float, Texture> roughness = 1.0f;
    std::variant<float, Texture> ao = 1.0f;
    std::variant<glm::vec3, Texture> emissive = glm::vec3(0.0f);
    std::optional<Texture> normalMap;
};


#endif // MATERIAL_H