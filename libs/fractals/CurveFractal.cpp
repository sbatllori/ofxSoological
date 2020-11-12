
#include "CurveFractal.h"

namespace soo {

CurveFractal::CurveFractal() : edge_length_(10.f), rotation_angle_(90.f) {}

CurveFractal::CurveFractal(const float rotation_angle)
    : edge_length_(10.f), rotation_angle_(rotation_angle) {}

CurveFractal::CurveFractal(const float edge_length, const float rotation_angle)
    : edge_length_(edge_length), rotation_angle_(rotation_angle) {}

void CurveFractal::GenerateRecursive(unsigned int iteration) {
  if (iteration > 15) {
    std::cout << "[INFO][CurveFractal.h] Maximum iterations allowed: 15. "
                 "Generating the fractal for 15 iterations.\n";
    iteration = 15;
  }
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
    const ofRectangle bbox = line_.getBoundingBox();

    // Define scaling parameters
    const float scale = bbox.width > bbox.height
                            ? (ofGetWidth() - 2.f * margin) / bbox.width
                            : (ofGetHeight() - 2.f * margin) / bbox.height;

    // Define translation parameters
    const float x = ofGetWidth() / 2.f - scale * (bbox.x + bbox.width / 2.f);
    const float y = ofGetHeight() / 2.f - scale * (bbox.y + bbox.height / 2.f);

    ofTranslate(x, y);
    ofScale(scale);
    line_.draw();
  }
  ofPopMatrix();
}
}  // namespace soo
