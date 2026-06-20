#ifndef MATERIAL_GLSL
#define MATERIAL_GLSL

// Material struct definition
// use get functions to access the material values
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
    bool hasNormalMap;
    sampler2D normalMap;
};
uniform Material material;

vec4 getAlbedo() {
    return material.albedo.x != -1 ? vec4(material.albedo, 1.0) : texture(material.albedoMap, uv);
}
float getMetallic() {
    return material.metallic != -1 ? material.metallic : texture(material.metallicMap, uv).r;
}
float getRoughness() {
    return material.roughness != -1 ? material.roughness : texture(material.roughnessMap, uv).r;
}
float getAnbientOclusion() {
    return material.ao != -1 ? material.ao : texture(material.aoMap, uv).r;
}
vec3 getEmissive() {
    return material.emissive.x != -1 ? material.emissive : texture(material.emissiveMap, uv).rgb;
}
// Returns the normal from the normal map if it exists, otherwise returns a default normal
vec3 getNormal() {
    return material.hasNormalMap ? texture(material.normalMap, uv).rgb : vec3(1.0); // TODO: Replace with default normal value
}
#endif // MATERIAL_GLSL