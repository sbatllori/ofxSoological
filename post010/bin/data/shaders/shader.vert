#version 150

in vec4 position;
out vec4 vposition;

uniform mat4 modelViewProjectionMatrix;

void main()
{
    vposition = position;
	gl_Position = modelViewProjectionMatrix * position;
}
