#include "ofApp.h"
#include "soo_export.h"

void ofApp::ResetRandomRectangles() {
  rectangles_.clear();
  rectangles_.reserve(Params::kRectangles);

  std::generate_n(std::back_inserter(rectangles_), Params::kRectangles, []() {
    return ofRectangle(
        ofRandom(-Params::kMaxRectangleSize.x, ofGetWidth()),
        ofRandom(-Params::kMaxRectangleSize.y, ofGetHeight()),
        ofRandom(Params::kMinRectangleSize.x, Params::kMaxRectangleSize.x),
        ofRandom(Params::kMinRectangleSize.y, Params::kMaxRectangleSize.y));
  });
}

void ofApp::ResetRandomBoxes() {
  top_outline_29_ =
      top_outline_29_.getResampledBySpacing(Params::kOutlineSpacing);

  const auto num_boxes = top_outline_29_.getVertices().size();

  boxes_.clear();
  boxes_.reserve(num_boxes);

  std::generate_n(std::back_inserter(boxes_), num_boxes, []() {
    return ofVec3f{ofRandom(Params::kMinBoxSize.x, Params::kMaxBoxSize.x),
                   ofRandom(Params::kMinBoxSize.y, Params::kMaxBoxSize.y),
                   ofRandom(Params::kMinBoxSize.z, Params::kMaxBoxSize.z)};
  });
}

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup canvas
  ofSetFrameRate(30);
  ofSetCircleResolution(72);
  ofBackgroundHex(SOO_WHITE);

  // Define a weighted color palette, so that each color is added several times
  // to define their probability to be randomly chosen. E.g. if the color
  // palette has 100 elements and a color is added 10 times, the probability of
  // this color to be chosen is 10%.
  std::generate_n(std::back_inserter(color_palette_), Params::kBlack,
                  []() { return SOO_BLACK; });
  std::generate_n(std::back_inserter(color_palette_), Params::kWhite,
                  []() { return SOO_WHITE; });
  std::generate_n(std::back_inserter(color_palette_), Params::kRed,
                  []() { return SOO_RED; });
  std::generate_n(std::back_inserter(color_palette_), Params::kYellow,
                  []() { return SOO_YELLOW; });
  std::generate_n(std::back_inserter(color_palette_), Params::kGreen,
                  []() { return SOO_GREEN; });
  std::random_shuffle(color_palette_.begin(), color_palette_.end());

  // Define random rectangles to fill in the background
  ResetRandomRectangles();

  // Define the top outline of the 29
  // - Load the font and the outlines of each number
  // - Translate the number positions so that they draw a 29
  // - Get only the vertices that define the top part of the outline
  //    - Vertices definining the top outline of the number 2: 74 - 0
  //    - Vertices definining the top outline of the number 9: 33 - end
  font_.load("Lato-Light.ttf", 800, true, true, true);
  auto outline_2 = font_.getCharacterAsPoints('2', true, false).getOutline()[0];
  auto outline_9 = font_.getCharacterAsPoints('9', true, false).getOutline()[0];

  outline_2.translate({0, 80});
  outline_9.translate({550, 0});

  std::for_each(outline_2.getVertices().begin() + 74,
                outline_2.getVertices().end(), [this](const auto& vertex) {
                  top_outline_29_.addVertex(vertex);
                });                                       // 74 - end
  top_outline_29_.addVertex(outline_2.getVertices()[0]);  // 0

  std::for_each(outline_9.getVertices().begin() + 33,
                outline_9.getVertices().end(), [this](const auto& vertex) {
                  top_outline_29_.addVertex(vertex);
                });  // 33 - end

  // Define random boxes that will be drawn along the top outline of the 29
  ResetRandomBoxes();

  // Define the lights for the 3D scene
  {
    ofLight light;
    light.setDiffuseColor(ofColor{200});
    light.setPosition({0, 0, -200});
    light.setPointLight();
    lights_.push_back(light);
  }
  {
    ofLight light;
    light.setDiffuseColor(ofColor{200});
    light.setPosition({.8f * ofGetWidth(), 0, -100});
    light.setPointLight();
    lights_.push_back(light);
  }
  {
    ofLight light;
    light.setDiffuseColor(ofColor{90});
    light.setPosition({.5f * ofGetWidth(), ofGetHeight(), -100});
    light.setPointLight();
    lights_.push_back(light);
  }
  {
    ofLight light;
    light.setDiffuseColor(ofColor{200});
    light.setPosition({1.5 * ofGetWidth(), .35f * ofGetHeight(), -100});
    light.setPointLight();
    lights_.push_back(light);
  }
  {
    ofLight light;
    light.setDiffuseColor(ofColor{100});
    light.setPosition({0, .25f * ofGetHeight(), -50});
    light.setPointLight();
    lights_.push_back(light);
  }
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {
  // Independent light for the background
  ofLight screen_light;
  screen_light.setOrientation({0, 180, 0});
  screen_light.setDirectional();
  screen_light.enable();

  // Draw the background: predefined random rectangles
  // - Draw the rectangles filling with a different color
  // - Draw the outline of the boxes always with the same color
  ofSetLineWidth(2);
  for (const auto& rectangle : rectangles_) {
    // Use the integral and fractional part of the rectangle area to define the
    // probability to pick each filling color
    float integral;
    const float fractional =
        modf(rectangle.width * rectangle.height, &integral);

    ofFill();
    ofSetHexColor(SOO_WHITE);
    if (fractional < 0.05) ofSetHexColor(SOO_BLACK);
    if (fractional < 0.005) ofSetHexColor(SOO_YELLOW);
    if (fractional < 0.002)
      static_cast<int>(integral) % 2 == 0 ? ofSetHexColor(SOO_RED)
                                          : ofSetHexColor(SOO_GREEN);
    ofDrawRectangle(rectangle);

    ofNoFill();
    ofSetHexColor(SOO_BLACK);
    ofDrawRectangle(rectangle);
  }

  // Draw a translucent layer to lower the intensity of the background
  ofFill();
  ofSetColor(255, Params::kAlpha);
  ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

  screen_light.disable();

  // Enable the lights
  for (auto& light : lights_) light.enable();

  // Draw the foreground: boxes along the top outline of the 29
  // - Center the 29 on the screen
  // - Draw a box for each size with the proper color of the palette
  ofPushMatrix();
  {
    const ofRectangle bbox = top_outline_29_.getBoundingBox();
    const float x = ofGetWidth() / 2 - (bbox.x + bbox.width / 2) - 10;
    const float y = ofGetHeight() / 2 - (bbox.y + bbox.height / 2) - 50;
    ofTranslate(x, y);

    for (unsigned long i{0}; i < boxes_.size(); i++) {
      const float width = boxes_[i].x;
      const float height = boxes_[i].y;
      const float depth = boxes_[i].z;

      auto vertex = top_outline_29_.getVertices()[i];
      vertex.y += .5f * height;

      const int color_idx = static_cast<int>(height) % color_palette_.size();

      ofFill();
      ofSetHexColor(color_palette_[color_idx]);
      ofDrawBox(vertex, width, height, depth);
    }
  }
  ofPopMatrix();

  // Disable the lights
  for (auto& light : lights_) light.disable();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
  if (key == 'f') {
    ResetRandomBoxes();
  }
  if (key == 'b') {
    ResetRandomRectangles();
  }
}
