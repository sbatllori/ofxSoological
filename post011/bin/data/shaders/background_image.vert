#version 150

in vec4 position;
in vec2 texcoord;

out vec4 vposition;
out vec2 vtexcoord;

uniform mat4 modelViewProjectionMatrix;


void main()
{
    vposition = position;
    vtexcoord = texcoord;

    gl_Position = modelViewProjectionMatrix * position;
}
