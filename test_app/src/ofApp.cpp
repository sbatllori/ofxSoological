#include "ofApp.h"
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

void ofApp::run_unit_tests() {
  // Unit tests for Particle.h
  test_Particle_Constructor_position();
  test_Particle_Constructor_position_direction();
  test_Particle_SetRandomDirection();
}

//--------------------------------------------------------------
// UNIT TESTS
//--------------------------------------------------------------
struct Properties {};

void ofApp::test_Particle_Constructor_position() {
  std::string unit_test = "test_Particle_Constructor_position";

  ofVec2f position(2.f, 5.f);
  soo::Particle<Properties> particle(position);
  soo_assert(particle.position() == position, unit_test,
             "Wrong position: (" + std::to_string(particle.position().x) +
                 ", " + std::to_string(particle.position().y) + ")" +
                 "; Expected: (" + std::to_string(position.x) + ", " +
                 std::to_string(position.y) + ")");
  soo_passed(unit_test);
}

void ofApp::test_Particle_Constructor_position_direction() {
  std::string unit_test = "test_Particle_Constructor_position_direction";

  ofVec2f position(2.f, 5.f);
  ofVec2f direction(4.f, 5.f);
  soo::Particle<Properties> particle(position, direction);
  soo_assert(particle.position() == position, unit_test,
             "Wrong position: (" + std::to_string(particle.position().x) +
                 ", " + std::to_string(particle.position().y) + ")" +
                 "; Expected: (" + std::to_string(position.x) + ", " +
                 std::to_string(position.y) + ")");
  soo_assert(particle.direction() == direction.getNormalized(), unit_test,
             "Wrong direction: (" + std::to_string(particle.direction().x) +
                 ", " + std::to_string(particle.direction().y) + ")" +
                 "; Expected: (" + std::to_string(direction.getNormalized().x) +
                 ", " + std::to_string(direction.getNormalized().y) + ")");
  soo_passed(unit_test);
}

void ofApp::test_Particle_SetRandomDirection() {
  std::string unit_test = "test_Particle_SetRandomDirection";

  soo::Particle<Properties> particle({0.f, 0.f});
  particle.SetRandomDirection();
  soo_assert(
      particle.direction() == particle.direction().getNormalized(), unit_test,
      "Wrong direction: (" + std::to_string(particle.direction().x) + ", " +
          std::to_string(particle.direction().y) + ")" + "; Expected: (" +
          std::to_string(particle.direction().getNormalized().x) + ", " +
          std::to_string(particle.direction().getNormalized().y) + ")");
  soo_passed(unit_test);
}
