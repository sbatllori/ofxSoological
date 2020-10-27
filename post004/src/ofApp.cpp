#include "ofApp.h"
namespace {

std::vector<float> GenerateExternalRadii(const float min_external_radius,
                                         const float max_external_radius,
                                         const unsigned long resolution) {
  std::vector<float> external_radii;
  external_radii.reserve(resolution);

  std::generate_n(std::back_inserter(external_radii), resolution,
                  [min_external_radius, max_external_radius]() {
                    return ofRandom(min_external_radius, max_external_radius);
                  });

  return external_radii;
}

void SetPathDefaultDrawingSettings(ofPath& path) {
  path.setFilled(true);
  path.setFillColor(ofColor::white);
  path.setStrokeColor(ofColor::black);
  path.setStrokeWidth(2);
  path.setCurveResolution(72);
}

}  // namespace
//--------------------------------------------------------------
void ofApp::setup() {
  // Canvas settings
  ofSetFrameRate(30);
  ofSetCurveResolution(72);

  //--------------------------------------------------------------
  // TEXT
  //--------------------------------------------------------------
  // Setup and load the font
  font_.load(kFontName, 30, true, true, true);
  font_.setLineHeight(34.f);

  //--------------------------------------------------------------
  // SKY
  //--------------------------------------------------------------
  // Define the sky border as a vertical ellipse centered on the canvas
  const float w = ofGetWidth();
  const float h = ofGetHeight();
  sky_border_.ellipse(w / 2, h / 2, 2 * w / 3, 3 * h / 4);

  // Define the stars to be inside the ellipse that delimites the sky
  constexpr unsigned long kNumStars = 40;
  stars_.reserve(kNumStars);

  std::generate_n(std::back_inserter(stars_), kNumStars, [this]() {
    Star star;

    float x, y;
    do {
      x = ofRandomWidth();
      y = ofRandomHeight();
    } while (!sky_border_.getOutline()[0].inside(x, y));

    star.center_ = ofVec2f{x, y};
    star.radius_ = ofRandom(1, 2.5);

    return star;
  });

  //--------------------------------------------------------------
  // ROCKS
  //--------------------------------------------------------------
  // Define the ground rocks to be outside the ellipse that delimites the sky
  constexpr unsigned long kNumRocks = 700;
  ground_rocks_.reserve(kNumRocks);

  std::generate_n(std::back_inserter(ground_rocks_), kNumRocks, [this]() {
    // Define shape geometry
    float x, y;
    do {
      x = ofRandomWidth();
      y = ofRandomHeight();
    } while (sky_border_.getOutline()[0].inside(x, y));

    const ofVec2f center{x, y};
    const unsigned long num_layers{9};
    const float spacing_between_layers{7.f};

    const float min_external_radius = ofRandom(52, 60);
    const float max_external_radius = min_external_radius + 10;
    const auto kResolution = static_cast<unsigned long>(ofRandom(6, 12));

    std::vector<float> external_radii = GenerateExternalRadii(
        min_external_radius, max_external_radius, kResolution);

    Rock rock(center, num_layers, spacing_between_layers, external_radii);

    // Define shape drawing settings
    for (auto& layer : rock.layers_mutable()) {
      SetPathDefaultDrawingSettings(layer);
    }

    return rock;
  });

  // Define the flying rock
  // - geometry
  std::vector<float> external_radii = GenerateExternalRadii(20, 25, 10);
  flying_rock_ = Rock({0, 65}, 5, 4.5, external_radii);

  // - drawing settings
  for (auto& layer : flying_rock_.layers_mutable()) {
    SetPathDefaultDrawingSettings(layer);
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  // Define the fire rock with changing radii to generate the fire animation
  // - geometry
  std::vector<float> external_radii = GenerateExternalRadii(15, 18, 8);
  fire_rock_ = Rock({0, -45}, 3, 5.f, external_radii);

  // - drawing settings
  for (auto& layer : fire_rock_.layers_mutable()) {
    SetPathDefaultDrawingSettings(layer);
  }
  fire_rock_.layers_mutable()[0].setColor(ofColor::yellow);
  fire_rock_.layers_mutable()[1].setColor(ofColor::orange);
  fire_rock_.layers_mutable()[2].setColor(ofColor::red);
}

//--------------------------------------------------------------
void ofApp::draw() {
  // Draw the sky as the background gradient
  ofBackgroundGradient(ofColor{0, 30, 160}, ofColor{0}, OF_GRADIENT_CIRCULAR);

  // Draw the stars with changing radius to simulate them shining
  ofSetColor(ofColor::white);
  for (const auto& star : stars_) {
    ofDrawCircle(star.center_, star.radius_ + ofRandom(-0.5, 0.5));
  }

  ofPushMatrix();
  {
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2 + 20);
    ofScale(1.4f);

    // Draw a person
    {
      ofFill();
      ofSetLineWidth(2);
      ofSetColor(ofColor::black);

      // Head
      ofDrawEllipse(0, 0, 10, 12);

      // Body
      ofDrawTriangle(0, -5, -8, 30, 8, 30);

      // Left arm
      ofPath leftArm;
      leftArm.setFilled(false);
      leftArm.setStrokeColor(ofColor::black);
      leftArm.setStrokeWidth(2);
      leftArm.arc(0, -5, 10, 15, 90, 200);
      leftArm.draw();

      // Right arm
      ofPushMatrix();
      {
        ofRotateYDeg(180);
        leftArm.draw();
      }
      ofPopMatrix();

      // Left leg
      ofDrawLine(-3, 25, -3, 45);

      // Right leg
      ofDrawLine(3, 25, 3, 45);
    }

    // Draw the fire rock
    for (const auto& layer : fire_rock_.layers()) {
      layer.draw();
    }

    // Draw the flying rock
    for (const auto& layer : flying_rock_.layers()) {
      layer.draw();
    }
  }
  ofPopMatrix();

  // Draw the ground
  for (const auto& rock : ground_rocks_) {
    for (const auto& layer : rock.layers()) {
      layer.draw();
    }
  }

  // Draw the text
  ofSetColor(ofColor::white);
  ofRectangle bbox = font_.getStringBoundingBox(kText, 0, 0);
  const float x = (ofGetWidth() - bbox.width) / 2;
  const float y = ofGetHeight() / 3;
  font_.drawString(kText, x, y);
}
