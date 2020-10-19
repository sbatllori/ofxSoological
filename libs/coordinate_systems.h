#include "ofMain.h"

namespace soo {
namespace coord {
ofVec2f Polar2Cartesian(const ofVec2f center, const float r,
                        const float theta) {
  ofVec2f cartesian;
  cartesian.x = center.x + r * cos(TWO_PI * theta);
  cartesian.y = center.y + r * sin(TWO_PI * theta);
  return cartesian;
}
}  // namespace coord
}  // namespace soo
