#include "LevyCCurve.h"

namespace soo {

LevyCCurve::LevyCCurve() : edge_length_(10.f), rotation_angle_(90.f) {}

LevyCCurve::LevyCCurve(const float rotation_angle)
    : edge_length_(10.f), rotation_angle_(rotation_angle) {}

LevyCCurve::LevyCCurve(const float edge_length, const float rotation_angle)
    : edge_length_(edge_length), rotation_angle_(rotation_angle) {}

void LevyCCurve::GenerateRecursive(unsigned int iteration) {
  if (iteration > 0) {
    GenerateNextIteration();
    GenerateRecursive(--iteration);
  }
}

void LevyCCurve::GenerateNextIteration() {
  line_.getVertices().empty() ? Init() : Iterate();
}

void LevyCCurve::draw(const float margin) {
  ofPushMatrix();
  {
    const ofRectangle& bbox = line_.getBoundingBox();

    // Define scaling parameters
    float scaleFactor = bbox.width > bbox.height
                            ? (ofGetWidth() - 2 * margin) / bbox.width
                            : (ofGetHeight() - 2 * margin) / bbox.height;

    // Define translation parameters
    float x = ofGetWidth() / 2 - scaleFactor * (bbox.x + bbox.width / 2);
    float y = ofGetHeight() / 2 - scaleFactor * (bbox.y + bbox.height / 2);

    ofTranslate(x, y);
    ofScale(scaleFactor);

    line_.draw();
  }
  ofPopMatrix();
}

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
