#include "ofApp.h"
#include "DeformedLayeredCircle.h"
#include "Particle.h"

namespace {
void soo_assert(bool statement, const std::string& unit_test,
                const std::string& msg = "") {
  if (!statement) {
    std::string out = "\033[1;31m[FAILED] " + unit_test +
                      "\033[0m\n    \033[;31m" + msg + "\033[0m\n";
    std::cout << out;
    exit(EXIT_SUCCESS);
  }
}

void soo_passed(const std::string& unit_test) {
  std::string out = "\033[1;32m[PASSED] " + unit_test + "\033[0m\n";
  std::cout << out;
}
}  // namespace

//--------------------------------------------------------------
void ofApp::run_unit_tests() {
  // Unit tests for Particle
  test_Particle_Constructor_position();
  test_Particle_Constructor_position_direction();
  test_Particle_SetRandomDirection();

  // Unit tests for DeformedLayeredCircle
  test_DeformedLayeredCircle_Constructor();
}

//--------------------------------------------------------------
void ofApp::draw() {
  // Drawing tests for DeformedLayeredCircle
  draw_DeformedLayeredCircle();
}

//--------------------------------------------------------------
// UNIT TESTS
//--------------------------------------------------------------
struct Properties {};

//--------------------------------------------------------------
// Particle
//--------------------------------------------------------------
void ofApp::test_Particle_Constructor_position() {
  std::string unit_test = "test_Particle_Constructor_position";

  ofVec2f position(2.f, 5.f);
  soo::Particle<Properties> particle(position);

  soo_assert(particle.position() == position, unit_test);
  soo_passed(unit_test);
}

void ofApp::test_Particle_Constructor_position_direction() {
  std::string unit_test = "test_Particle_Constructor_position_direction";

  ofVec2f position(2.f, 5.f);
  ofVec2f direction(4.f, 5.f);
  soo::Particle<Properties> particle(position, direction);

  soo_assert(particle.position() == position, unit_test);
  soo_assert(particle.direction() == direction.getNormalized(), unit_test);
  soo_passed(unit_test);
}

void ofApp::test_Particle_SetRandomDirection() {
  std::string unit_test = "test_Particle_SetRandomDirection";

  soo::Particle<Properties> particle({0.f, 0.f});
  particle.SetRandomDirection();

  soo_assert(particle.direction() == particle.direction().getNormalized(),
             unit_test);
  soo_passed(unit_test);
}

//--------------------------------------------------------------
// DeformedLayerCircle
//--------------------------------------------------------------
void ofApp::test_DeformedLayeredCircle_Constructor() {
  std::string unit_test = "test_DeformedLayeredCircle_Constructor";

  // Case 1: All positive radii
  {
    const ofVec2f center{0.f, 0.f};
    const unsigned long num_layers{3};
    const float spacing_between_layers{1.f};
    std::vector<float> radii{10.f, 11.f, 12.f};
    soo::DeformedLayeredCircle shape = soo::DeformedLayeredCircle(
        center, num_layers, spacing_between_layers, radii);

    soo_assert(shape.center() == center, unit_test);
    soo_assert(shape.layers().size() == num_layers, unit_test,
               "All positive radii: number of layers does not match!");
  }

  // Case 2: Negative radii in inner layers
  {
    const ofVec2f center{0.f, 0.f};
    const unsigned long num_layers{100};
    const float spacing_between_layers{1.f};
    std::vector<float> radii{10.f, 11.f, 12.f};
    soo::DeformedLayeredCircle shape = soo::DeformedLayeredCircle(
        center, num_layers, spacing_between_layers, radii);

    soo_assert(shape.center() == center, unit_test);
    soo_assert(
        shape.layers().size() == 10, unit_test,
        "Negative radii in inner layers: number of layers does not match!");
  }

  soo_passed(unit_test);
}

void ofApp::draw_DeformedLayeredCircle() {
  std::string unit_test = "draw_DeformedLayeredCircle";

  const ofVec2f center{0.f, 0.f};
  const unsigned long num_layers{10};
  const float spacing_between_layers{15.f};
  std::vector<float> radii{200.f, 250.f, 200.f, 150.f, 200.f, 150.f, 200.f};
  soo::DeformedLayeredCircle shape = soo::DeformedLayeredCircle(
      center, num_layers, spacing_between_layers, radii);

  ofPushMatrix();
  {
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    for (auto& layer : shape.GetLayersToModify()) {
      layer.setFilled(true);
      layer.setFillColor(ofColor::white);
      layer.setStrokeColor(ofColor::black);
      layer.setStrokeWidth(2);
      layer.setCurveResolution(72);
      layer.draw();
    }
  }
  ofPopMatrix();
}
