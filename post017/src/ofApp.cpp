#include "ofApp.h"
#include "soo_export.h"

namespace {

void CenterPath(ofPath& path, const float x_offset, const float y_offset) {
  const ofRectangle& bbox = path.getOutline()[0].getBoundingBox();
  const float x = (ofGetWidth() - bbox.width) / 2.f;
  const float y = (ofGetHeight() + bbox.height) / 2.f;
  path.translate({x + x_offset, y + y_offset});
}

std::vector<float> GenerateRadii(const float min_radius, const float max_radius,
                                 const unsigned long resolution) {
  std::vector<float> radii;
  radii.reserve(resolution);

  std::generate_n(
      std::back_inserter(radii), resolution,
      [min_radius, max_radius]() { return ofRandom(min_radius, max_radius); });

  return radii;
}
}  // namespace

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFrameRate(30);
  ofSetWindowShape(kWidth_, kHeight_);

  // Load the text
  ofTrueTypeFont font;
  font.load("Lato-Bold.ttf", 470, true, true, true);
  shape_1_ = font.getCharacterAsPoints('1', true, false);
  shape_7_ = font.getCharacterAsPoints('7', true, false);

  // Translate the shapes to define a 17 centered on the canvas
  CenterPath(shape_1_, -200, 0);
  CenterPath(shape_7_, +200, 0);

  // Define the holes
  // They are uniformly distributed inside the 17, so that they do not intersect
  const auto& outline1 = shape_1_.getOutline()[0].getResampledBySpacing(1);
  const auto& outline7 = shape_7_.getOutline()[0].getResampledBySpacing(1);
  const auto& bbox1 = outline1.getBoundingBox();
  const auto& bbox7 = outline7.getBoundingBox();

  for (float x = bbox1.x; x < bbox7.x + bbox7.width; x += ofRandom(50, 60)) {
    for (float y = bbox1.y; y < bbox7.y + bbox7.height; y += ofRandom(50, 60)) {
      const bool inside = outline1.inside(x, y) || outline7.inside(x, y);

      const ofVec2f closest1 = outline1.getClosestPoint({x, y, 0});
      const ofVec2f closest7 = outline7.getClosestPoint({x, y, 0});
      const bool close_enough =
          closest1.distance({x, y}) <= 20 || closest7.distance({x, y}) <= 20;

      if (inside || close_enough) {
        // Define the stroke of the hole
        std::vector<float> radii =
            GenerateRadii(25, 35, static_cast<unsigned long>(ofRandom(7, 10)));
        strokes_.emplace_back(ofVec2f{x, y}, 1, 0, radii);

        // Define the holes while decreasing the stroke radii
        std::vector<float> decreased_radii;

        std::transform(radii.begin(), radii.end(),
                       std::back_inserter(decreased_radii),
                       [](const float radius) { return radius - 3; });
        holes_.emplace_back(ofVec2f{x, y}, 1, 0, decreased_radii);
      }
    }
  }

  // Setup the video grabber
  video_grabber_.setDeviceID(1);
  video_grabber_.setup(kWidth_, kHeight_);

  // Load the shaders
  shader_glitch_.load("shaders/glitch");
  shader_stroke_.load("shaders/stroke");
  shader_holes_.load("shaders/holes");
}

//--------------------------------------------------------------
void ofApp::update() {
  video_grabber_.update();

  //  if (ofGetFrameNum() >= 10) soo::SaveFrame(ofGetFrameNum() - 10);
}

//--------------------------------------------------------------
void ofApp::draw() {
  shader_glitch_.begin();
  {
    shader_glitch_.setUniformTexture("webcam", video_grabber_.getTexture(), 0);
    shader_glitch_.setUniform2i("resolution", kWidth_, kHeight_);
    shader_glitch_.setUniform1f("time", ofGetElapsedTimef());

    video_grabber_.draw(0, 0);
  }
  shader_glitch_.end();

  shader_stroke_.begin();
  {
    shader_stroke_.setUniformTexture("webcam", video_grabber_.getTexture(), 0);

    for (auto& hole : strokes_) {
      for (auto& layer : hole.layers_mutable()) {
        layer.setFilled(true);
        layer.draw();
      }
    }
  }
  shader_stroke_.end();

  shader_holes_.begin();
  {
    shader_holes_.setUniformTexture("webcam", video_grabber_.getTexture(), 0);

    for (auto& hole : holes_) {
      for (auto& layer : hole.layers_mutable()) {
        layer.setFilled(true);
        layer.draw();
      }
    }
  }
  shader_holes_.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
