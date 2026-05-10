#version 430 core
#include "fragment_io.glsl"
#include "material.glsl"
#include "light.glsl"

uniform vec3 viewPos;

void main() {
    vec3 N = normalize(normal);
    vec3 V = normalize(viewPos - worldPos);

    vec3 albedo = getAlbedo().rgb;
    float metallic = getMmetallic();
    float roughness = getRoughness();

    vec3 color = calculateLighting(N, V, worldPos, albedo, metallic, roughness);

    vec3 ambient = albedo * getAnbientOclusion() * 0.03;
    color += ambient;
    color += getEmissive();

    FragColor = vec4(albedo, 1.0);
}