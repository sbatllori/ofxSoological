#version 150

in vec4 vposition;
out vec4 fcolor;

uniform sampler2DRect webcam;

void main()
{
    vec2 uv = vposition.xy;
    vec3 webcam_color = texture(webcam, uv).rgb;
    fcolor = vec4(webcam_color, 1.0);
}
