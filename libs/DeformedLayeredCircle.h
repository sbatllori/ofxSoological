#pragma once

#include "ofMain.h"

namespace soo {

class DeformedLayeredCircle {
 public:
  DeformedLayeredCircle(const ofVec2f& center, const unsigned long num_layers,
                        const float spacing_between_layers,
                        std::vector<float>& radii);

  const ofVec2f& center() const { return center_; }
  const std::vector<ofPath>& layers() const { return layers_; }

  std::vector<ofPath>& GetLayersToModify() { return layers_; }

 private:
  ofPath GenerateLayer(const std::vector<float>& radii);
  bool DecreaseRadii(std::vector<float>& radii,
                     const float spacing_between_layers);

 private:
  ofVec2f center_;
  std::vector<ofPath> layers_;
};
}  // namespace soo
