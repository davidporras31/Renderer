#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 uv; // output a color to the fragment shader
out vec3 normal;
out vec3 worldPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    vec4 world = model * vec4(aPos, 1.0);
    worldPos = world.xyz;
    gl_Position = projection * view * world;
    uv = aTexCoord; // set ourColor to the input color we got from the vertex data
    normal = aNormal;
}