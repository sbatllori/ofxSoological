#version 150
#define TOON_COLORS 7

in vec4 vposition;
out vec4 fcolor;

uniform sampler2DRect webcam;

void main() {
  vec2 uv = vposition.xy;
  vec3 webcam_color = texture(webcam, uv).rgb;

  float illumination = (webcam_color.r + webcam_color.g + webcam_color.b) / 3.f;

  int toon_colors = TOON_COLORS;
  float toon_gray =
      (1.0 / (toon_colors - 1)) * floor(illumination / (1.0 / toon_colors));

  fcolor = vec4(vec3(toon_gray), 1.0);
}
