#include "DeformedLayeredCircle.h"
#include "soo_coordinates.h"

namespace soo {

DeformedLayeredCircle::DeformedLayeredCircle(const ofVec2f& center,
                                             const unsigned long num_layers,
                                             const float spacing_between_layers,
                                             std::vector<float>& radii)
    : center_(center) {
  layers_.reserve(num_layers);

  for (unsigned long i{0}; i < num_layers; i++) {
    ofPath layer = this->GenerateLayer(radii);
    layers_.push_back(layer);

    bool next_layer = this->DecreaseRadii(radii, spacing_between_layers);
    if (!next_layer) {
      break;
    }
  }
}

ofPath DeformedLayeredCircle::GenerateLayer(const std::vector<float>& radii) {
  ofPath path;

  ofVec2f first_vertex = coord::Polar2Cartesian(center_, radii[0], 0.f);
  path.curveTo(first_vertex);  // this opens the path
  path.curveTo(first_vertex);  // this fixes an OF bug in ofPath::moveTo

  auto resolution = radii.size();
  for (unsigned long i{1}; i < resolution; i++) {
    const float theta = (1.f * i) / resolution;
    path.curveTo(coord::Polar2Cartesian(center_, radii[i], theta));
  }

  path.curveTo(first_vertex);  // this closes the path
  path.curveTo(first_vertex);  // this fixes an OF bug in ofPath::moveTo

  path.close();

  return path;
}

bool DeformedLayeredCircle::DecreaseRadii(std::vector<float>& radii,
                                          const float spacing_between_layers) {
  // Decrese the radii only if they will remain positive, otherwise return
  // false
  auto it = std::min_element(radii.begin(), radii.end());
  if (*it - spacing_between_layers <= 0) {
    return false;
  }

  std::transform(radii.begin(), radii.end(), radii.begin(),
                 [spacing_between_layers](float radius) {
                   return radius - spacing_between_layers;
                 });
  return true;
}
}  // namespace soo
