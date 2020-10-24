#include "ofMain.h"

namespace soo {
namespace coord {
ofVec2f Polar2Cartesian(const ofVec2f center, const float r,
                        const float theta) {
  return ofVec2f{center.x + r * cos(TWO_PI * theta),
                 center.y + r * sin(TWO_PI * theta)};
}
}  // namespace coord
}  // namespace soo
