#version 150

in vec4 vposition;
in vec4 fposition;
out vec4 fcolor;

uniform sampler2DRect webcam;
uniform vec2 resolution;
uniform float time;

void main()
{
    vec2 st = fposition.xy / (1.0 * resolution);

    vec2 uv = vposition.xy;
    vec3 webcam_color = texture(webcam, uv).rgb;

    float illumination = (webcam_color.r + webcam_color.g + webcam_color.b) / 3.f;
//    vec3 color = illumination > 0.6
//            ? vec3(1)
//            : illumination > 0.3
//              ? vec3(0.5)
//              : vec3(0);

    vec3 value;
    value = webcam_color;
    value = value * ceil(100 + 0.05 * uv.y);
    value = sin(0.5 * value);

    vec3 color = smoothstep(0.0, 0.5, value);
    fcolor = vec4(color, 1.0);
}
