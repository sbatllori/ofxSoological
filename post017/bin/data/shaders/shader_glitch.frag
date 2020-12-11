#version 150

in vec4 vposition;
out vec4 fcolor;

uniform sampler2DRect webcam;
uniform vec2 resolution;
uniform float time;

void main()
{
    vec2 uv = vposition.xy;
    vec3 webcam_color = texture(webcam, uv).rgb;

    vec3 value = webcam_color;
    value = value * ceil(100 + 0.05 * uv.y);
    value = sin(0.5 * value);

    vec3 color = smoothstep(0.0, 0.5, value);
    fcolor = vec4(color, 1.0);
}
