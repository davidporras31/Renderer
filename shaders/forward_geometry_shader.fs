#version 430 core

struct Material {
    vec3 albedo;
    sampler2D albedoMap;
    float metallic;
    sampler2D metallicMap;
    float roughness;
    sampler2D roughnessMap;
    float ao;
    sampler2D aoMap;
    vec3 emissive;
    sampler2D emissiveMap;
    sampler2D normalMap;
};

in vec2 uv;

out vec4 FragColor;

uniform Material material;

void main()
{
    vec4 albedoColor = material.albedo.x != -1 ? vec4(material.albedo, 1.0) : texture(material.albedoMap, uv);
    FragColor = albedoColor;
}