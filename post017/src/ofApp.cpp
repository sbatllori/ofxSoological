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
  font.load("FreeSans.ttf", 400, true, true, true);
  shape_1_ = font.getCharacterAsPoints('1', true, false);
  shape_7_ = font.getCharacterAsPoints('7', true, false);

  // Translate the shapes to define a 17 centered on the canvas
  CenterPath(shape_1_, -150, 0);
  CenterPath(shape_7_, +150, 0);

  // Define the holes inside the 17
  const auto num_holes = 50l;
  holes_.reserve(num_holes);

  std::generate_n(std::back_inserter(holes_), num_holes, [this]() {
    // Define the center of the holes to be either inside the 1 or inside the 7
    float x, y;
    const auto& outline1 = shape_1_.getOutline()[0];
    const auto& outline7 = shape_7_.getOutline()[0];
    const auto& bbox1 = outline1.getBoundingBox();
    const auto& bbox7 = outline7.getBoundingBox();
    do {
      x = ofRandom(bbox1.x, bbox7.x + bbox7.width);
      y = ofRandom(bbox1.y, bbox7.y + bbox7.height);
    } while (!outline1.inside(x, y) && !outline7.inside(x, y));

    // Define the radii of the holes
    std::vector<float> radii =
        GenerateRadii(30, 40, static_cast<unsigned long>(ofRandom(7, 10)));

    soo::DeformedLayeredCircle hole({x, y}, 1, 0, radii);

    // Set the holes to be filled
    for (auto& layer : hole.layers_mutable()) {
      layer.setFilled(true);
    }

    return hole;
  });

  // Setup the video grabber
  video_grabber_.setDeviceID(1);
  video_grabber_.setup(kWidth_, kHeight_);

  // Load the shaders
  shader_glitch_.load("shaders/shader_glitch");
  shader_holes_.load("shaders/shader_holes");
}

//--------------------------------------------------------------
void ofApp::update() {
  video_grabber_.update();

  //  if (ofGetFrameNum() > 5) soo::SaveFrame(ofGetFrameNum() - 5);
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

  shader_holes_.begin();
  {
    shader_holes_.setUniformTexture("webcam", video_grabber_.getTexture(), 0);
    //    shape_1_.draw();
    //    shape_7_.draw();
    for (const auto& hole : holes_) {
      for (const auto& layer : hole.layers()) {
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
