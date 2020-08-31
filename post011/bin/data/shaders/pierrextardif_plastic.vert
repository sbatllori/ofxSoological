#version 150

/**
  * This shader was originally written by Pierre Tardif and me, Sonia Batllori,
  * have got it from his public github repository ofxPlasticTexture. Find it here:
  * https://github.com/pierrextardif/ofxPlasticTexture
 **/

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;

out vec2 texCoordVarying;


void main(void)
{
    // ==> The following lines have been modified by @sbatllori
    texCoordVarying = 0.5*position.xy;
    // <== The previous lines have been modified by @sbatllori

    gl_Position = modelViewProjectionMatrix * position;
}
