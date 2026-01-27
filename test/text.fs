#version 430 core
in vec2 uv;
in vec3 worldPos;

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
};

layout(std140, binding = 0) uniform LightDataUBO {
    Light lights[16];
    Light count;
};

out vec4 FragColor;

uniform Material material;
uniform vec4 text_color;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(material.albedoMap, uv).r);
    FragColor = sampled * text_color;
}