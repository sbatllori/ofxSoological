#include "ofApp.h"
#include "shapes/Triangle.h"
#include "soo_export.h"

void ofApp::GenerateBalls() {
  // Reset the vetor of balls
  balls_.clear();
  balls_.reserve(kNumBalls_);

  // Define a box to initialize the ball positions
  ofRectangle grown_seven_bbox = seven_.contour_.getBoundingBox();
  grown_seven_bbox.translate(-grown_seven_bbox.width / 4.f,
                             -grown_seven_bbox.height / 4.f);
  grown_seven_bbox.scale(1.5);

  // Define the common brush parameters for all the balls
  soo::GenerateTriangleParams brush_triangle_params;
  soo::GenerateColorParams brush_color_params;

  brush_triangle_params.num_triangles(5)
      .min_offset_to_center(0)
      .max_offset_to_center(15);
  brush_color_params.color(ofColor{0}).alpha(50);

  std::generate_n(
      std::back_inserter(balls_), kNumBalls_,
      [this, &grown_seven_bbox, &brush_triangle_params, &brush_color_params]() {
        HairyShape ball;

        // Define the ball contour for the hairy shape, such that:
        // - the ball is placed inside the grown bounding box of the seven, but
        // outside the seven itself and not too close to it
        // - the contour of a ball is defined as a circle with a random radius
        constexpr float min_distance = 50;
        bool inside;
        bool not_too_close;
        float x, y;
        do {
          x = ofRandomWidth();
          y = ofRandomHeight();
          const ofVec2f closest = seven_.contour_.getClosestPoint({x, y, 0});
          inside = grown_seven_bbox.inside(x, y);
          not_too_close = closest.distance({x, y}) >= min_distance;

        } while (!(inside && not_too_close));

        const float radius = ofRandom(20, 40);
        ball.contour_.arc({x, y, 0}, radius, radius, 0, 360);

        // Define the ball brush with the specific parameters
        const soo::Triangle reference_triangle(soo::TriangleVertices(
            {0, 0.15f * radius}, {radius, 0}, {0, -0.15f * radius}));

        ball.brush_ = soo::TrianglesOutBrush(
            brush_triangle_params.reference_triangle(reference_triangle),
            brush_color_params.target_color(ofColor{ofRandom(5, 40)}));

        return ball;
      });
}

//--------------------------------------------------------------
void ofApp::setup() {
  // Canvas settings
  ofSetBackgroundAuto(false);  // Do not refresh canvas
  ofEnableAlphaBlending();
  ofSetFrameRate(60);
  ofBackground(204, 75, 20);

  // Setup the hairy shape for the seven
  // - load the character, retrieve its contour, resample it and translate it to
  // the center of the canvas
  // - define a brush for the hairy shape

  // Setup contour
  font_.load(font_name_, 500, true, true, true);
  seven_.contour_ = font_.getCharacterAsPoints(char_, true, false)
                        .getOutline()[0]
                        .getResampledBySpacing(1);

  const ofRectangle bbox = seven_.contour_.getBoundingBox();
  const float x = ofGetWidth() / 2 - (bbox.x + bbox.width / 2);
  const float y = ofGetHeight() / 2 - (bbox.y + bbox.height / 2);
  seven_.contour_.translate({x, y});

  // Setup brush
  soo::GenerateTriangleParams brush_triangle_params;
  soo::GenerateColorParams brush_color_params;
  seven_.brush_ = soo::TrianglesOutBrush(
      brush_triangle_params
          .reference_triangle(
              soo::Triangle(soo::TriangleVertices({0, 15}, {50, 0}, {0, -15})))
          .num_triangles(50)
          .min_offset_to_center(10)
          .max_offset_to_center(20),
      brush_color_params.color(ofColor::white)
          .target_color(ofColor{ofColor::cadetBlue + 20})
          .alpha(50));

  // Setup hairy shapes for the balls
  GenerateBalls();
}

//--------------------------------------------------------------
void ofApp::update() {
  // soo::SaveFrame(ofGetFrameNum());
}

//--------------------------------------------------------------
void ofApp::draw() {
  // Draw the scene when pressing the left button of the mouse
  if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
    seven_.draw();
    for (const auto& ball : balls_) {
      ball.draw();
    }
  }

  // Reset the screen and the balls when pressing the right button of the mouse
  if (ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT)) {
    ofBackground(204, 75, 20);
    GenerateBalls();
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
