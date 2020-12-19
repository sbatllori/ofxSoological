#version 150

in vec4 vposition;
out vec4 fcolor;

uniform sampler2DRect webcam;

void main() {
  vec2 uv = vposition.xy;
  vec3 webcam_color = texture(webcam, uv).rgb;

  vec3 glitch = webcam_color;
  glitch = glitch * ceil(100 + 0.05 * uv.y);
  glitch = sin(0.5 * glitch);

  vec3 color = smoothstep(0.0, 0.5, glitch);
  fcolor = vec4(color, 1.0);
}
