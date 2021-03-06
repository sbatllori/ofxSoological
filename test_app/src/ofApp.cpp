#include "ofApp.h"
#include "brushes/TrianglesOutBrush.h"
#include "fractals/DragonCurve.h"
#include "fractals/LevyCCurve.h"
#include "shapes/Dandelion.h"
#include "shapes/DeformedLayeredCircle.h"
#include "shapes/Triangle.h"
#include "soo_inside.h"
#include "soo_intersection.h"
#include "soo_motion.h"
#include "soo_noise.h"

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
    std::vector<float> radii{200.f, 250.f, 200.f, 150.f, 200.f, 150.f, 250.f};
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
void ofApp::test_TriangleVertices_Constructor_vertices() {
  std::string unit_test = "test_TriangleVertices_Constructor_vertices";

  {
    ofVec2f A{0, 10}, B{20, 0}, C{0, -10};
    soo::TriangleVertices triangle_vertices(A, B, C);
    soo_assert(triangle_vertices.A_ == A, unit_test);
    soo_assert(triangle_vertices.B_ == B, unit_test);
    soo_assert(triangle_vertices.C_ == C, unit_test);
  }

  {
    ofVec2f A{0, 10}, B{20, 0}, C{0, 10};
    bool exception_thrown = false;
    try {
      soo::TriangleVertices triangle_vertices(A, B, C);
    } catch (...) {
      exception_thrown = true;
    }
    soo_assert(exception_thrown, unit_test,
               "Generated with incorrect vertices.");
  }

  {
    ofVec2f A{-10, 0}, B{-10, 0}, C{-10, 0};
    bool exception_thrown = false;
    try {
      soo::TriangleVertices triangle_vertices(A, B, C);
    } catch (...) {
      exception_thrown = true;
    }
    soo_assert(exception_thrown, unit_test,
               "Generated with incorrect vertices.");
  }

  soo_passed(unit_test);
}

void ofApp::test_TriangleVertices_Constructor_edge_lengths() {
  std::string unit_test = "test_TriangleVertices_Constructor_edge_lengths";

  {
    soo::TriangleVertices triangle_vertices(5, 4, 3);
    soo_assert(triangle_vertices.A_ == ofVec2f{0, 2}, unit_test);
    soo_assert(triangle_vertices.B_ == ofVec2f{3, 2}, unit_test);
    soo_assert(triangle_vertices.C_ == ofVec2f{0, -2}, unit_test);
  }

  {
    bool exception_thrown = false;
    try {
      soo::TriangleVertices triangle_vertices(2, 1, 1);
    } catch (...) {
      exception_thrown = true;
    }
    soo_assert(exception_thrown, unit_test,
               "Generated with incorrect edge lengths.");
  }

  {
    bool exception_thrown = false;
    try {
      soo::TriangleVertices triangle_vertices(5, -3, 4);
    } catch (...) {
      exception_thrown = true;
    }
    soo_assert(exception_thrown, unit_test,
               "Generated with incorrect edge lengths.");
  }
  soo_passed(unit_test);
}

void ofApp::test_Triangle_Constructor() {
  std::string unit_test = "test_Triangle_Constructor";

  soo::TriangleVertices triangle_vertices(5, 4, 3);
  soo::Triangle triangle(triangle_vertices);
  soo_assert(triangle.A() == triangle_vertices.A_, unit_test);
  soo_assert(triangle.B() == triangle_vertices.B_, unit_test);
  soo_assert(triangle.C() == triangle_vertices.C_, unit_test);

  soo_passed(unit_test);
}

void ofApp::draw_Triangle(bool run) {
  std::string unit_test = "draw_Triangle";

  if (run) {
    soo::Triangle triangle(soo::TriangleVertices(300, 240, 180));

    ofPushMatrix();
    {
      ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
      ofDrawTriangle(triangle.B(), triangle.C(), triangle.A());
    }
    ofPopMatrix();
  }

  soo_run(run, unit_test);
}

//--------------------------------------------------------------
// TrianglesOutBrush
//--------------------------------------------------------------
void ofApp::draw_TrianglesOutBrush(bool run) {
  std::string unit_test = "draw_TrianglesOutBrush";

  if (run) {
    soo::Triangle triangle(soo::TriangleVertices(150, 30, 150));
    soo::GenerateTriangleParams brush_triangle_params;
    brush_triangle_params.reference_triangle(triangle)
        .num_triangles(1000)
        .min_offset_to_center(0)
        .max_offset_to_center(50);

    soo::GenerateColorParams brush_color_params;
    brush_color_params.color(ofColor{150}).target_color(ofColor{10}).alpha(40);

    soo::TrianglesOutBrush brush(brush_triangle_params, brush_color_params);
    brush.draw({ofGetWidth() / 2.f, ofGetHeight() / 2.f});
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
void ofApp::draw_Intersection_Horizontal_ClosedPolyline(bool run) {
  std::string unit_test = "draw_Intersection_Horizontal_ClosedPolyline";

  if (run) {
    ofPushMatrix();
    {
      ofTranslate(ofGetWidth() / 2, 150);

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
        ofDrawLine(-500, y, 500, y);

        const std::vector<ofVec2f>& intersection_points =
            soo::intersection::HorizontalAxis_ClosedPolyline(y, poly_line, 1.f);

        for (const auto& p : intersection_points) {
          ofDrawCircle(p, 5);
        }
      }

      ofSetLineWidth(2);
      poly_line.draw();
    }
    ofPopMatrix();
  }

  soo_run(run, unit_test);
}

//--------------------------------------------------------------
// Fractals
//--------------------------------------------------------------
void ofApp::draw_DragonCurve(bool run) {
  std::string unit_test = "draw_DragonCurve";

  if (run) {
    soo::DragonCurve curve(90.f);
    curve.GenerateRecursive(13);
    curve.draw();
  }

  soo_run(run, unit_test);
}

void ofApp::draw_LevyCCurve(bool run) {
  std::string unit_test = "draw_LevyCCurve";

  if (run) {
    soo::LevyCCurve curve(90.f);
    curve.GenerateRecursive(13);
    curve.draw();
  }

  soo_run(run, unit_test);
}

//--------------------------------------------------------------
// soo_noise
//--------------------------------------------------------------
void ofApp::draw_Noise_Rectagle(bool run) {
  std::string unit_test = "draw_noise_Rectagle";

  if (run) {
    soo::GenerateNoiseParams noise_params;
    const ofRectangle noise_bbox =
        ofRectangle(50, 100, ofGetWidth() - 100, ofGetHeight() - 200);

    soo::Noise screen_noise = soo::noise::Rectangle(
        noise_bbox, noise_params.amount(ofGetWidth() * ofGetHeight())
                        .min_radius(.01f)
                        .max_radius(.5f)
                        .min_alpha(10)
                        .max_alpha(50)
                        .color(ofColor::black));

    screen_noise.draw();
  }

  soo_run(run, unit_test);
}

//--------------------------------------------------------------
// Spirograph
//--------------------------------------------------------------
void ofApp::setup_Spirograph() {
  spirograph.AddNode({0, 0, 0}, 1.5f);
  spirograph.AddNode({100, 0, 0}, 7, true);
  spirograph.AddNode({100, 0, 0}, 0, true);
}

void ofApp::draw_Spirograph(bool run) {
  std::string unit_test = "draw_Spirograph";

  if (run) {
    ofPushMatrix();
    {
      ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
      ofVec3f previous{spirograph.brush_position()};
      std::for_each(spirograph.nodes_mutable().begin(),
                    --spirograph.nodes_mutable().end(),
                    [](auto& node) { node->RotateZ(); });
      ofVec3f current{spirograph.brush_position()};

      ofColor(0);
      ofDrawLine(previous, current);
    }
    ofPopMatrix();
  }

  soo_run(run, unit_test);
}
