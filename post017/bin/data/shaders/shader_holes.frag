#version 150

in vec4 vposition;
out vec4 fcolor;

uniform sampler2DRect webcam;

void main()
{
    vec2 uv = vposition.xy;
    vec3 webcam_color = texture(webcam, uv).rgb;

//    float illumination = (webcam_color.r + webcam_color.g + webcam_color.b) / 3.f;
//    vec3 color = illumination > 0.6
//            ? vec3(1)
//            : illumination > 0.3
//              ? vec3(0.5)
//              : vec3(0);

    fcolor = vec4(webcam_color, 1.0);
}
