#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture2D.h"
#include <variant>
#include <optional>
#include <glm/glm.hpp>

struct Material
{
    std::variant<glm::vec3, Texture2D> albedo = glm::vec3(1.0f);
    std::variant<float, Texture2D> metallic = 0.0f;
    std::variant<float, Texture2D> roughness = 1.0f;
    std::variant<float, Texture2D> ao = 1.0f;
    std::variant<glm::vec3, Texture2D> emissive = glm::vec3(0.0f);
    std::optional<Texture2D> normalMap;
    Material() = default;
};


#endif // MATERIAL_H