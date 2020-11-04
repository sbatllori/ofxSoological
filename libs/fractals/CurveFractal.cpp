
#include "CurveFractal.h"

namespace soo {

CurveFractal::CurveFractal() : edge_length_(10.f), rotation_angle_(90.f) {}

CurveFractal::CurveFractal(const float rotation_angle)
    : edge_length_(10.f), rotation_angle_(rotation_angle) {}

CurveFractal::CurveFractal(const float edge_length, const float rotation_angle)
    : edge_length_(edge_length), rotation_angle_(rotation_angle) {}

void CurveFractal::GenerateRecursive(unsigned int iteration) {
  if (iteration > 0) {
    GenerateNextIteration();
    GenerateRecursive(--iteration);
  }
}

void CurveFractal::GenerateNextIteration() {
  line_.getVertices().empty() ? Init() : Iterate();
}

void CurveFractal::draw(const float margin) const {
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
}  // namespace soo
