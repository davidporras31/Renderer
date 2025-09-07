#version 430 core
in vec2 uv;

out vec4 FragColor;
void main()
{
    FragColor = vec4(uv.x,uv.y,1.f,1.f);
}