#version 330 core
in vec3 fragmentColor;
out vec4 color;

void main()
{
    color = vec4 (fragmentColor.x, fragmentColor.y, fragmentColor.z, 1.0f);
}
