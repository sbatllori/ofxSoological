#version 150

in vec4 vposition;
out vec4 fcolor;

uniform sampler2DRect webcam;

void main()
{
    vec2 uv = vposition.xy;
    vec3 webcam_color = texture(webcam, uv).rgb;

    vec3 glitch = webcam_color;
    glitch = glitch * ceil(100 + 0.05 * uv.y);
    glitch = cos(0.5 * glitch);

    float illumination = (
                webcam_color.r +
                webcam_color.g +
                webcam_color.b) / 3.f;


    vec3 red = vec3(1, 0, 0);
    vec3 yellow = vec3(1, 1, 0);

    vec3 color = 0.5 * smoothstep(0.0, 0.5, glitch)
            + 0.5 * mix(red, yellow, illumination);

    fcolor = vec4(color, 1.0);
}
