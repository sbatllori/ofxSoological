#include "LevyCCurve.h"

namespace soo {

void LevyCCurve::Init() {
  // Reset the curve data
  line_.clear();

  // Add the first segment
  line_.addVertex({0, 0, 0});
  line_.addVertex({edge_length_, 0, 0});
}

void LevyCCurve::Iterate() {
  ofPolyline line_copy{line_};
  auto pivot = line_copy.getVertices().back();

  line_copy.translate({0, 0});
  line_copy.rotateDeg(rotation_angle_, {0, 0, 1});
  line_copy.translate(pivot);

  line_.addVertices(line_copy.getVertices());
}
}  // namespace soo
