#include "DeformedLayeredCircle.h"
#include "soo_coordinates.h"

namespace soo {

DeformedLayeredCircle::DeformedLayeredCircle(const ofVec2f& center,
                                             const int num_layers,
                                             const float spacing_between_layers,
                                             std::vector<float>& radii)
    : center_(center) {
  layers_.reserve(static_cast<unsigned long>(num_layers));

  for (int _{0}; _ < num_layers; _++) {
    layers_.push_back(this->GenerateLayer(radii));
    if (!this->DecreaseRadii(radii, spacing_between_layers)) break;
  }
}

ofPath DeformedLayeredCircle::GenerateLayer(const std::vector<float>& radii) {
  ofPath path;

  const ofVec2f first_vertex = coord::Polar2Cartesian(center_, radii[0], 0.f);
  path.curveTo(first_vertex);  // this opens the path
  path.curveTo(first_vertex);  // this fixes an OF bug in ofPath::moveTo

  const float resolution(radii.size());
  for (unsigned long i{1}; i < radii.size(); i++) {
    const float fragment(i);
    const float theta = fragment / resolution;
    path.curveTo(coord::Polar2Cartesian(center_, radii[i], theta));
  }

  path.curveTo(first_vertex);  // this closes the path
  path.curveTo(first_vertex);  // this fixes an OF bug in ofPath::moveTo

  path.close();

  return path;
}

bool DeformedLayeredCircle::DecreaseRadii(std::vector<float>& radii,
                                          const float spacing_between_layers) {
  // Decrease the radii and return true only if they will remain positive,
  // otherwise return false without decreasing the radii
  const auto it = std::min_element(radii.begin(), radii.end());

  if (*it - spacing_between_layers <= 0) {
    return false;
  }

  std::transform(radii.begin(), radii.end(), radii.begin(),
                 [spacing_between_layers](const float radius) {
                   return radius - spacing_between_layers;
                 });
  return true;
}
}  // namespace soo
