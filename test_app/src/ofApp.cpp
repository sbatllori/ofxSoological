#include "ofApp.h"
#include "Particle.h"
#include "shapes/DeformedLayeredCircle.h"
#include "shapes/Triangle.h"

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

void soo_run(bool run, const std::string& unit_test) {
  std::string out;
  if (run) {
    out = "\033[;32m--- running --- " + unit_test + "\033[0m\n";
  } else {
    out = "\033[;31m--- did not run --- " + unit_test + "\033[0m\n";
  }
  std::cout << out;
}
}  // namespace

//--------------------------------------------------------------
void ofApp::run_unit_tests() {
  test_Particle_Constructor_position();
  test_Particle_Constructor_position_direction();
  test_Particle_SetRandomDirection();

  test_DeformedLayeredCircle_Constructor();

  test_TriangleVertices_Generate_from_vertices();
  test_TriangleVertices_Generate_from_edge_lengths();
  test_Triangle_Constructor();
}

//--------------------------------------------------------------
void ofApp::draw() {
  if (ofGetFrameNum() == 10) {
    draw_DeformedLayeredCircle(false);
    draw_Triangle(true);
  }
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

void ofApp::draw_DeformedLayeredCircle(bool run) {
  std::string unit_test = "draw_DeformedLayeredCircle";

  if (run) {
    const ofVec2f center{0.f, 0.f};
    const unsigned long num_layers{10};
    const float spacing_between_layers{15.f};
    std::vector<float> radii{200.f, 250.f, 200.f, 150.f, 200.f, 150.f, 200.f};
    soo::DeformedLayeredCircle shape = soo::DeformedLayeredCircle(
        center, num_layers, spacing_between_layers, radii);

    ofPushMatrix();
    {
      ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

      for (auto& layer : shape.layers_mutable()) {
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

  soo_run(run, unit_test);
}

//--------------------------------------------------------------
// Triangle
//--------------------------------------------------------------
void ofApp::test_TriangleVertices_Generate_from_vertices() {
  std::string unit_test = "test_TriangleVertices_Generate_from_vertices";

  {
    soo::TriangleVertices triangle_vertices;
    ofVec2f v1{-10, 0}, v2{0, 10}, v3{10, 0};
    bool generated = triangle_vertices.Generate(v1, v2, v3);
    soo_assert(generated, unit_test, "Not generated with correct vertices.");
    soo_assert(triangle_vertices.v1_ == v1, unit_test);
    soo_assert(triangle_vertices.v2_ == v2, unit_test);
    soo_assert(triangle_vertices.v3_ == v3, unit_test);
  }

  {
    soo::TriangleVertices triangle_vertices;
    ofVec2f v1{-10, 0}, v2{-10, 0}, v3{10, 0};
    bool generated = triangle_vertices.Generate(v1, v2, v3);
    soo_assert(!generated, unit_test, "Generated with incorrect vertices.");
  }

  {
    soo::TriangleVertices triangle_vertices;
    ofVec2f v1{-10, 0}, v2{-10, 0}, v3{-10, 0};
    bool generated = triangle_vertices.Generate(v1, v2, v3);
    soo_assert(!generated, unit_test, "Generated with incorrect vertices.");
  }

  soo_passed(unit_test);
}

void ofApp::test_TriangleVertices_Generate_from_edge_lengths() {
  std::string unit_test = "test_TriangleVertices_Generate_from_edge_lengths";

  {
    soo::TriangleVertices triangle_vertices;
    float edge_length_1 = 3;  // triangle base
    float edge_length_2 = 4;
    float edge_length_3 = 5;
    bool generated =
        triangle_vertices.Generate(edge_length_1, edge_length_2, edge_length_3);
    soo_assert(generated, unit_test, "Not generated with correct edges.");

    soo_assert(triangle_vertices.v2_ == ofVec2f{-1.5, 0}, unit_test,
               "Wrong v2: " + std::to_string(triangle_vertices.v2_.x) + ", " +
                   std::to_string(triangle_vertices.v2_.y));
    soo_assert(triangle_vertices.v3_ == ofVec2f{1.5, 0}, unit_test,
               "Wrong v3: " + std::to_string(triangle_vertices.v3_.x) + ", " +
                   std::to_string(triangle_vertices.v3_.y));
    soo_assert(triangle_vertices.v1_ == ofVec2f{1.5, 4}, unit_test,
               "Wrong v2: " + std::to_string(triangle_vertices.v1_.x) + ", " +
                   std::to_string(triangle_vertices.v1_.y));
  }

  {
    soo::TriangleVertices triangle_vertices;
    float edge_length_1 = 1;  // triangle base
    float edge_length_2 = 1;
    float edge_length_3 = 2;
    bool generated =
        triangle_vertices.Generate(edge_length_1, edge_length_2, edge_length_3);
    soo_assert(!generated, unit_test, "Generated with incorrect edge lengths.");
  }

  {
    soo::TriangleVertices triangle_vertices;
    float edge_length_1 = -3;  // triangle base
    float edge_length_2 = 4;
    float edge_length_3 = 5;
    bool generated =
        triangle_vertices.Generate(edge_length_1, edge_length_2, edge_length_3);
    soo_assert(!generated, unit_test, "Generated with incorrect edge lengths.");
  }
  soo_passed(unit_test);
}

void ofApp::test_Triangle_Constructor() {
  std::string unit_test = "test_Triangle_Constructor";

  soo::TriangleVertices triangle_vertices;
  float edge_length_1 = 3;  // triangle base
  float edge_length_2 = 4;
  float edge_length_3 = 5;
  bool generated =
      triangle_vertices.Generate(edge_length_1, edge_length_2, edge_length_3);

  if (generated) {
    soo::Triangle triangle(triangle_vertices);
    soo_assert(triangle.v2() == ofVec2f{-1.5, 0}, unit_test);
    soo_assert(triangle.v3() == ofVec2f{1.5, 0}, unit_test);
    soo_assert(triangle.v1() == ofVec2f{1.5, 4}, unit_test);

  } else {
    soo_assert(false, unit_test);
  }
  soo_passed(unit_test);
}

void ofApp::draw_Triangle(bool run) {
  std::string unit_test = "draw_Triangle";

  if (run) {
    soo::TriangleVertices triangle_vertices;
    float edge_length_1 = 3;  // triangle base
    float edge_length_2 = 4;
    float edge_length_3 = 5;
    bool generated =
        triangle_vertices.Generate(edge_length_1, edge_length_2, edge_length_3);

    if (generated) {
      soo::Triangle triangle(triangle_vertices);

      ofPushMatrix();
      {
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        ofScale(50);
        ofDrawTriangle(triangle.v1(), triangle.v2(), triangle.v3());
      }
      ofPopMatrix();
    } else {
      soo_assert(false, unit_test);
    }
  }

  soo_run(run, unit_test);
}
