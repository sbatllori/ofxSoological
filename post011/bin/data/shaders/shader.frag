#version 150

in vec4 vposition;
out vec4 fcolor;

//uniform float time;

void main()
{
    vec3 color = vposition.xyz;
//    color.r += 0.5 * cos(time);
    fcolor = vec4(color, 1.);
}
