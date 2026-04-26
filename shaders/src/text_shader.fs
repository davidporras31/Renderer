#version 430 core
#include "fragment_io.glsl"
#include "material.glsl"
#include "light.glsl"

uniform vec4 text_color;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(material.albedoMap, uv).r);
    FragColor = sampled * text_color;
}