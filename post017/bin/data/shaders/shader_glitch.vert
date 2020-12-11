#version 150

in vec4 position;
out vec4 vposition;
out vec4 fposition;

uniform mat4 modelViewProjectionMatrix;

void main()
{
    vposition = position;
    fposition = modelViewProjectionMatrix * position;
    gl_Position = modelViewProjectionMatrix * position;
}
