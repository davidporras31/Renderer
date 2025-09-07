#version 430 core
layout (location = 0)in vec3 aPos;
layout (location = 1)in vec2 uvPos;
out vec2 uv; // output a color to the fragment shader
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    uv = uvPos; // set ourColor to the input color we got from the vertex data
}