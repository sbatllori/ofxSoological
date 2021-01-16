#version 150
#define PI 3.14159265358979323846
#define BLUR 0.01
#define erase(scene, mask) scene *(1. - mask)
#define add(scene, object, color) erase(scene, object) + object *color
#define rad(deg) deg *PI / 180.0

in vec4 vposition;
out vec4 fcolor;

uniform vec2 u_resolution;

mat2 rotate2dmat(float angle) {
  return mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
}

float sdCircle(vec2 p, vec2 c, float r) {
  float d = length(c - p);
  return smoothstep(r + BLUR, r, d);
}

float sdEquilateralTriangle(vec2 p, vec2 c, float scale_factor = 1.0,
                            float rotate_deg = 0.0) {

  p /= scale_factor;
  c /= scale_factor;

  p *= rotate2dmat(rad(rotate_deg));
  c *= rotate2dmat(rad(rotate_deg));

  p += vec2(0.5);
  p = (2.0 * p * u_resolution - u_resolution.xy) / u_resolution.y;
  p *= -2.0;
  p += 4.0 * c;

  const float k = sqrt(3.0);
  p.x = abs(p.x) - 1.0;
  p.y = p.y + 1.0 / k;
  if (p.x + k * p.y > 0.0)
    p = vec2(p.x - k * p.y, -k * p.x - p.y) / 2.0;
  p.x -= clamp(p.x, -2.0, 0.0);

  float d = -length(p) * sign(p.y);
  return smoothstep(BLUR, 0, d);
}

void main() {
  vec2 p = vposition.xy / u_resolution;
  vec3 scene = vec3(0.0);

  // Grid
  p *= 10.0;
  p = fract(p);

  // Tile
  scene = add(scene, sdEquilateralTriangle(p, vec2(0.0, 0.5), 1.5, -90.0),
              vec3(1.0));

  scene = add(scene, sdEquilateralTriangle(p, vec2(1.0, 0.5), 1.5, 90.0),
              vec3(1.0));

  scene = add(scene, sdEquilateralTriangle(p, vec2(0.5, 0.0), 1.5, 180.0),
              vec3(1.0));

  scene =
      add(scene, sdEquilateralTriangle(p, vec2(0.5, 1.0), 1.5, 0.0), vec3(1.0));

  fcolor = vec4(scene, 1.0);
}