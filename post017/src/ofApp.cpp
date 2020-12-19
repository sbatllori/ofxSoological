#include "ofApp.h"
#include "soo_export.h"

namespace {

void CenterPath(ofPath& path, const float x_offset, const float y_offset) {
  const ofRectangle& bbox = path.getOutline()[0].getBoundingBox();
  const float x = (ofGetWidth() - bbox.width) / 2.f;
  const float y = (ofGetHeight() + bbox.height) / 2.f;
  path.translate({x + x_offset, y + y_offset});
}

}  // namespace

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup canvas
  ofSetWindowShape(kWidth_, kHeight_);
  ofSetFrameRate(30);

  // Setup the video grabber
  video_grabber_.setDeviceID(1);
  video_grabber_.setup(kWidth_, kHeight_);

  // Load the shaders
  glitch_shader_.load("shaders/glitch");
  stroke_shader_.load("shaders/stroke");
  hole_shader_.load("shaders/holes");

  // Load the text, i.e. the 1 and the 7 to define a 17
  ofTrueTypeFont font;
  font.load("Lato-Bold.ttf", 470, true, true, true);
  shape_1_ = font.getCharacterAsPoints('1', true, false);
  shape_7_ = font.getCharacterAsPoints('7', true, false);

  // Translate the shapes to define a 17 centered on the canvas
  CenterPath(shape_1_, -200, 0);
  CenterPath(shape_7_, +200, 0);

  // Define the holes:
  // - They are uniformly distributed inside the rectangle defined by the 1's
  // bounding box top-left corner, and the 7's bounding box bottom-right corner
  // - They do not intersect, and the horizontal and vertical distance between
  // them slighly varies randomly
  // - They are placed inside the outline of either the 1 or the 7, or close
  // enough to them
  // - They are defined through a deformed circle representing the hole stroke,
  // and a similar smaller deformed circle representing the hole itself
  const auto& outline1 = shape_1_.getOutline()[0].getResampledBySpacing(1);
  const auto& outline7 = shape_7_.getOutline()[0].getResampledBySpacing(1);

  const auto& bbox1 = outline1.getBoundingBox();
  const auto& bbox7 = outline7.getBoundingBox();

  const ofVec2f top_left{bbox1.x, bbox1.y};
  const ofVec2f bottom_right{bbox7.x + bbox7.width, bbox7.y + bbox7.height};

  constexpr int min_dist_between_holes{50};
  constexpr int max_dist_between_holes{60};
  constexpr int max_dist_to_outline{20};

  constexpr float stroke_min_radius{25};
  constexpr float stroke_max_radius{35};
  constexpr float stroke_width{3};

  for (float x{top_left.x}; x < bottom_right.x;
       x += ofRandom(min_dist_between_holes, max_dist_between_holes)) {
    for (float y{top_left.y}; y < bottom_right.y;
         y += ofRandom(min_dist_between_holes, max_dist_between_holes)) {
      // Check if the point (x, y) is inside the 17 or close enough to it
      const bool inside_outline =
          outline1.inside(x, y) || outline7.inside(x, y);

      const ofVec2f closest1 = outline1.getClosestPoint({x, y, 0});
      const ofVec2f closest7 = outline7.getClosestPoint({x, y, 0});
      const bool close_enough_to_outline =
          closest1.distance({x, y}) <= max_dist_to_outline ||
          closest7.distance({x, y}) <= max_dist_to_outline;

      if (inside_outline || close_enough_to_outline) {
        // Define the hole parameters
        const ofVec2f center{x, y};
        constexpr int num_layers{1};
        constexpr float layers_spacing{0};
        unsigned long resolution = static_cast<unsigned long>(ofRandom(7, 10));

        // Define the radii of the stroke
        std::vector<float> stroke_radii;
        stroke_radii.reserve(resolution);
        std::generate_n(std::back_inserter(stroke_radii), resolution,
                        [stroke_min_radius, stroke_max_radius]() {
                          return ofRandom(stroke_min_radius, stroke_max_radius);
                        });

        // Define the radii of the hole
        std::vector<float> hole_radii;
        hole_radii.reserve(resolution);
        std::transform(stroke_radii.begin(), stroke_radii.end(),
                       std::back_inserter(hole_radii), [](const float radius) {
                         return radius - stroke_width;
                       });

        // Add the stroke and the hole to the lists
        strokes_.emplace_back(center, num_layers, layers_spacing, stroke_radii);
        holes_.emplace_back(center, num_layers, layers_spacing, hole_radii);
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  video_grabber_.update();

  //  if (ofGetFrameNum() >= 10) soo::SaveFrame(ofGetFrameNum() - 10);
}

//--------------------------------------------------------------
void ofApp::draw() {
  // Apply the glitch shader to the video grabber
  glitch_shader_.begin();
  glitch_shader_.setUniformTexture("webcam", video_grabber_.getTexture(), 0);
  video_grabber_.draw(0, 0);
  glitch_shader_.end();

  // Apply the stroke shader to each hole stroke
  stroke_shader_.begin();
  stroke_shader_.setUniformTexture("webcam", video_grabber_.getTexture(), 0);
  for (auto& stroke : strokes_) {
    for (auto& layer : stroke.layers_mutable()) {
      layer.setFilled(true);
      layer.draw();
    }
  }
  stroke_shader_.end();

  // Apply the hole shader to each hole
  hole_shader_.begin();
  hole_shader_.setUniformTexture("webcam", video_grabber_.getTexture(), 0);
  for (auto& hole : holes_) {
    for (auto& layer : hole.layers_mutable()) {
      layer.setFilled(true);
      layer.draw();
    }
  }
  hole_shader_.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
