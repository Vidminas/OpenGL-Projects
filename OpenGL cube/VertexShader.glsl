#version 330 core
in vec3 coords;
in vec3 colors;
uniform mat4 MVP;

out vec3 fragmentColor;

void main()
{
    gl_Position = MVP * vec4 (coords, 1.0);
    fragmentColor = colors;
}
