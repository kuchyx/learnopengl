#version 330 core
out vec4 FragColor;
uniform vec4 ourColor; // set in OGL code
void main()
{
    FragColor = ourColor;
}