#version 430 core
in vec2 uv;

out vec4 FragColor;

uniform sampler2D texture1;
uniform vec4 text_color;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(texture1, uv).r);
    FragColor = sampled * text_color;
}