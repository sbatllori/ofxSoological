#include "ofApp.h"
#include "brushes/TrianglesOutBrush.h"
#include "shapes/Dandelion.h"
#include "shapes/DeformedLayeredCircle.h"
#include "shapes/Triangle.h"
#include "soo_inside.h"
#include "soo_intersection.h"
#include "soo_motion.h"

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
    out = "\033[;33m--- did not run --- " + unit_test + "\033[0m\n";
  }
  std::cout << out;
}
}  // namespace

//--------------------------------------------------------------
// UNIT TESTS
//--------------------------------------------------------------
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
    ofVec2f A{0, 10}, B{20, 0}, C{0, -10};
    bool generated = triangle_vertices.Generate(A, B, C);
    soo_assert(generated, unit_test, "Not generated with correct vertices.");
    soo_assert(triangle_vertices.A_ == A, unit_test);
    soo_assert(triangle_vertices.B_ == B, unit_test);
    soo_assert(triangle_vertices.C_ == C, unit_test);
  }

  {
    soo::TriangleVertices triangle_vertices;
    ofVec2f A{0, 10}, B{20, 0}, C{0, 10};
    bool generated = triangle_vertices.Generate(A, B, C);
    soo_assert(!generated, unit_test, "Generated with incorrect vertices.");
  }

  {
    soo::TriangleVertices triangle_vertices;
    ofVec2f A{-10, 0}, B{-10, 0}, C{-10, 0};
    bool generated = triangle_vertices.Generate(A, B, C);
    soo_assert(!generated, unit_test, "Generated with incorrect vertices.");
  }

  soo_passed(unit_test);
}

void ofApp::test_TriangleVertices_Generate_from_edge_lengths() {
  std::string unit_test = "test_TriangleVertices_Generate_from_edge_lengths";

  {
    soo::TriangleVertices triangle_vertices;
    bool generated = triangle_vertices.Generate(5, 4, 3);
    soo_assert(generated, unit_test, "Not generated with correct edges.");
    soo_assert(triangle_vertices.A_ == ofVec2f{0, 2}, unit_test,
               "Wrong A: " + std::to_string(triangle_vertices.A_.x) + ", " +
                   std::to_string(triangle_vertices.A_.y));
    soo_assert(triangle_vertices.B_ == ofVec2f{3, 2}, unit_test,
               "Wrong B: " + std::to_string(triangle_vertices.B_.x) + ", " +
                   std::to_string(triangle_vertices.B_.y));
    soo_assert(triangle_vertices.C_ == ofVec2f{0, -2}, unit_test,
               "Wrong C: " + std::to_string(triangle_vertices.C_.x) + ", " +
                   std::to_string(triangle_vertices.C_.y));
  }

  {
    soo::TriangleVertices triangle_vertices;
    bool generated = triangle_vertices.Generate(2, 1, 1);
    soo_assert(!generated, unit_test, "Generated with incorrect edge lengths.");
  }

  {
    soo::TriangleVertices triangle_vertices;
    bool generated = triangle_vertices.Generate(5, -3, 4);
    soo_assert(!generated, unit_test, "Generated with incorrect edge lengths.");
  }
  soo_passed(unit_test);
}

void ofApp::test_Triangle_Constructor() {
  std::string unit_test = "test_Triangle_Constructor";

  soo::TriangleVertices triangle_vertices;
  if (triangle_vertices.Generate(5, 4, 3)) {
    soo::Triangle triangle(triangle_vertices);
    soo_assert(triangle.A() == triangle_vertices.A_, unit_test);
    soo_assert(triangle.B() == triangle_vertices.B_, unit_test);
    soo_assert(triangle.C() == triangle_vertices.C_, unit_test);

  } else {
    soo_assert(false, unit_test);
  }
  soo_passed(unit_test);
}

void ofApp::draw_Triangle(bool run) {
  std::string unit_test = "draw_Triangle";

  if (run) {
    soo::TriangleVertices triangle_vertices;
    if (triangle_vertices.Generate(5, 4, 3)) {
      soo::Triangle triangle(triangle_vertices);

      ofPushMatrix();
      {
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        ofScale(50);
        ofDrawTriangle(triangle.B(), triangle.C(), triangle.A());
      }
      ofPopMatrix();
    } else {
      soo_assert(false, unit_test);
    }
  }

  soo_run(run, unit_test);
}

//--------------------------------------------------------------
// TrianglesOutBrush
//--------------------------------------------------------------
void ofApp::draw_TrianglesOutBrush(bool run) {
  std::string unit_test = "draw_TrianglesOutBrush";

  if (run) {
    soo::TriangleVertices triangle_vertices;
    if (triangle_vertices.Generate(50, 30, 50)) {
      soo::Triangle triangle(triangle_vertices);
      soo::TrianglesOutBrush brush(triangle, 500, 0, 100, ofColor::cyan,
                                   ofColor::magenta, 70);

      brush.draw({ofGetWidth() / 2.f, ofGetHeight() / 2.f});

    } else {
      soo_assert(false, unit_test);
    }
  }

  soo_run(run, unit_test);
}

//--------------------------------------------------------------
// Dandelion
//--------------------------------------------------------------
void ofApp::draw_Dandelion(bool run) {
  std::string unit_test = "draw_Dandelion";

  if (run) {
    soo::Dandelion dandelion(ofVec2f{0.f, 0.f}, 400.f);

    float x = ofGetWidth() / 2 - dandelion.center().x;
    float y = ofGetHeight() / 2 - dandelion.center().y;

    ofNoFill();
    ofSetColor(0);
    ofSetLineWidth(2);

    dandelion.DrawBbox(x, y);
    dandelion.DrawCircle(x, y);
    dandelion.DrawTrunk(x, y);
    dandelion.DrawLines(x, y);

    ofFill();
    dandelion.DrawEllipse(x, y);
  }

  soo_run(run, unit_test);
}

//--------------------------------------------------------------
// soo_motion
//--------------------------------------------------------------
void ofApp::test_Motion_UniformLinear() {
  std::string unit_test = "test_Motion_UniformLinear";

  const ofVec2f position_0{0.f, 0.f};
  const ofVec2f direction{1.f, 0.f};
  const float speed = 1.f;

  ofVec2f position = position_0;

  for (int i{1}; i < 10; i++) {
    position = soo::motion::UniformLinear(position, direction, speed);

    soo_assert(fabs(position.x - (position_0.x + i * direction.x)) <
                   std::numeric_limits<float>::epsilon(),
               unit_test);
    soo_assert(fabs(position.y - (position_0.y + i * direction.y)) <
                   std::numeric_limits<float>::epsilon(),
               unit_test);
  }

  soo_passed(unit_test);
}

//--------------------------------------------------------------
// soo_inside
//--------------------------------------------------------------
void ofApp::test_Inside_InCircle() {
  std::string unit_test = "test_Inside_InCircle";

  soo_assert(soo::inside::InCircle(ofVec2f{0, 0}, ofVec2f{0, 0}, 10), unit_test,
             "Inside");
  soo_assert(!soo::inside::InCircle(ofVec2f{0, 2}, ofVec2f{0, 0}, 1), unit_test,
             "Outside");
  soo_assert(!soo::inside::InCircle(ofVec2f{0, 1}, ofVec2f{0, 0}, 1), unit_test,
             "Boundary");

  soo_passed(unit_test);
}

//--------------------------------------------------------------
// soo_intersection
//--------------------------------------------------------------
void ofApp::draw_Intersection_Horizontal_PolylineClosed(bool run) {
  std::string unit_test = "draw_Intersection_Horizontal_PolylineClosed";

  if (run) {
    ofPushMatrix();
    {
      ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

      ofPolyline poly_line;
      poly_line.addVertex(0, 0);
      poly_line.addVertex(100, 0);
      poly_line.addVertex(200, 100);
      poly_line.addVertex(200, 150);
      poly_line.addVertex(50, 200);
      poly_line.addVertex(-100, 200);
      poly_line.addVertex(-150, 150);
      poly_line.addVertex(-100, 50);
      poly_line.close();

      for (int y{-20}; y < 250; y += 17) {
        ofSetLineWidth(1);
        ofSetColor(0, 0, 255);
        ofDrawLine(-500, y, 500, y);

        const std::vector<ofVec2f>& intersection_points =
            soo::intersection::HorizontalAxis_PolylineClosed(y, poly_line, 1.f);

        ofSetColor(255, 0, 0);
        for (const auto& p : intersection_points) {
          ofDrawCircle(p, 5);
        }
      }

      ofSetLineWidth(2);
      ofSetColor(0);
      poly_line.draw();
    }
    ofPopMatrix();
  }

  soo_run(run, unit_test);
}
