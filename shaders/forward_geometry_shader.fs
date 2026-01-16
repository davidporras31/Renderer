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

struct Light
{
    vec4 position;      //xyz = position, w = type
    vec4 direction;     //alaign by 4 bytes, w = unused
    vec4 color;
    vec4 data;          //data for light type spec
}

layout(std140, binding = 0) uniform LightBlock
{
    int   lightCount;  // occupies 4 bytes, padded to 16
    vec3  _pad0;            // padding

    Light lights[16];
};


in vec2 uv;

out vec4 FragColor;

uniform Material material;

void main()
{
    vec4 albedoColor = material.albedo.x != -1 ? vec4(material.albedo, 1.0) : texture(material.albedoMap, uv);
    FragColor = albedoColor;
}