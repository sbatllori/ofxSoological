#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup the canvas
  ofSetBackgroundAuto(false);
  ofSetFrameRate(600);
  ofSetCircleResolution(72);
  ofColor bg_color(245, 242, 235);
  ofBackground(bg_color);

  // Define noise covering the whole screen
  const ofRectangle screen = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());

  soo::GenerateNoiseParams noise_params;
  noise_params.min_radius(.01f).max_radius(.5f).min_alpha(10).max_alpha(50);

  screen_noise_.push_back(soo::noise::Rectangle(
      screen,
      noise_params.color(ofColor::black).amount(ofGetWidth() * ofGetHeight())));

  screen_noise_.push_back(soo::noise::Rectangle(
      screen,
      noise_params.color(bg_color).amount(2 * ofGetWidth() * ofGetHeight())));

  noise_params.min_radius(.1f).max_radius(5.f).min_alpha(10).max_alpha(150);
  screen_noise_.push_back(soo::noise::Rectangle(
      screen, noise_params.color(ofColor::black).amount(50)));

  screen_noise_.push_back(
      soo::noise::Rectangle(screen, noise_params.color(bg_color).amount(1000)));

  // Define the spirograph layers to compose a mandala. The layers are defined
  // bellow in the following order: from the external one to the internal one.

  // Triangles pointing out
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.f);
    layer.spirograph_.AddNode({470, 0, 0}, 240.f, true);
    layer.spirograph_.AddNode({20, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
      ofSetLineWidth(2);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  // External circle
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.f);
    layer.spirograph_.AddNode({450, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
      ofSetLineWidth(4);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  // External dense spirograph
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 0.55f);
    layer.spirograph_.AddNode({400, 0, 0}, 5.f, true);
    layer.spirograph_.AddNode({50, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
      ofSetLineWidth(1);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  // External large flower layer
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.2f);
    layer.spirograph_.AddNode({295, 0, 0}, 4.f, true);
    layer.spirograph_.AddNode({70, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
      ofSetLineWidth(4);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  // Middle large flower layer
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.2f);
    layer.spirograph_.AddNode({285, 0, 0}, 4.f, true);
    layer.spirograph_.AddNode({60, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
      ofSetLineWidth(2);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  // Internal large flower layer
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.2f);
    layer.spirograph_.AddNode({290, 0, 0}, 4.f, true);
    layer.spirograph_.AddNode({65, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
      ofSetLineWidth(1);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  // Large circles
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 360.f / 5.f);
    layer.spirograph_.AddNode({305, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofPushMatrix();
      ofRotateZDeg(18.f);
      {
        ofSetColor(0);
        ofSetLineWidth(2);

        ofNoFill();
        ofDrawCircle(layer.spirograph_.brush_position(), 20.f);

        ofFill();
        ofDrawCircle(layer.spirograph_.brush_position(), 10.f);
      }
      ofPopMatrix();
    };
  }

  // Middle circles
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 360.f / 5.f);
    layer.spirograph_.AddNode({272, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofPushMatrix();
      ofRotateZDeg(18.f);
      {
        ofSetColor(0);
        ofSetLineWidth(2);
        ofNoFill();
        ofDrawCircle(layer.spirograph_.brush_position(), 5.f);
      }
      ofPopMatrix();
    };
  }

  // Small circles
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 360.f / 5.f);
    layer.spirograph_.AddNode({257, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofPushMatrix();
      ofRotateZDeg(18.f);
      {
        ofSetColor(0);
        ofSetLineWidth(2);
        ofNoFill();
        ofDrawCircle(layer.spirograph_.brush_position(), 3.f);
      }
      ofPopMatrix();
    };
  }

  // External layer of the center flower
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.f);
    layer.spirograph_.AddNode({220, 0, 0}, 20.f, true);
    layer.spirograph_.AddNode({5, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
      ofSetLineWidth(4);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  // Middle layer of the center flower
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.2f);
    layer.spirograph_.AddNode({190, 0, 0}, 5.f, true);
    layer.spirograph_.AddNode({20, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
      ofSetLineWidth(1);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  // Interal layer of the center flower 4
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.f);
    layer.spirograph_.AddNode({160, 0, 0}, 20.f, true);
    layer.spirograph_.AddNode({5, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
      ofSetLineWidth(3);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  // Interal layer of the center flower 3
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.f);
    layer.spirograph_.AddNode({150, 0, 0}, 20.f, true);
    layer.spirograph_.AddNode({5, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofPushMatrix();
      ofRotateZDeg(360.f / 40.f);
      {
        ofSetColor(0);
        ofSetLineWidth(2);
        ofDrawLine(layer.previous_brush_position_,
                   layer.spirograph_.brush_position());
      }
      ofPopMatrix();
    };
  }

  // Interal layer of the center flower 2
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.f);
    layer.spirograph_.AddNode({140, 0, 0}, 20.f, true);
    layer.spirograph_.AddNode({5, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
      ofSetLineWidth(2);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  // Interal layer of the center flower 1
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.f);
    layer.spirograph_.AddNode({130, 0, 0}, 20.f, true);
    layer.spirograph_.AddNode({5, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofPushMatrix();
      ofRotateZDeg(360.f / 40.f);
      {
        ofSetColor(0);
        ofSetLineWidth(2);
        ofDrawLine(layer.previous_brush_position_,
                   layer.spirograph_.brush_position());
      }
      ofPopMatrix();
    };
  }

  // Internal dense spirograph
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.1f);
    layer.spirograph_.AddNode({75, 0, 0}, 5.f, true);
    layer.spirograph_.AddNode({50, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
      ofSetLineWidth(1);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  // Small flower
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.f);
    layer.spirograph_.AddNode({20, 0, 0}, 5.f, true);
    layer.spirograph_.AddNode({10, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
      ofSetLineWidth(2);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  // Center of the small flower
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 300.f);
    layer.spirograph_.AddNode({2, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
      ofSetLineWidth(2);

      ofNoFill();
      ofDrawCircle({0, 0}, 7);

      ofFill();
      ofDrawCircle({0, 0}, 4);
    };
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  // Process the layers in order, from the inner to the outer one
  // - If the current layer is already closed, remove it from the list
  // - Then, rotate the spirograph nodes accordingly
  if (!layers_.empty()) {
    if (layers_.back().spirograph_.IsCicleStart() && !init_cicle_) {
      layers_.pop_back();
      init_cicle_ = true;
    } else {
      init_cicle_ = false;
    }
  }

  if (!layers_.empty()) {
    auto& layer = layers_.back();
    layer.previous_brush_position_ = layer.spirograph_.brush_position();
    layer.spirograph_.nodes_mutable()[0]->RotateZ();
    layer.spirograph_.nodes_mutable()[1]->RotateZ();
  }

  soo::SaveFrame(ofGetFrameNum());
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofPushMatrix();
  ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  {
    if (!layers_.empty()) {
      layers_.back().draw();
    }
  }
  ofPopMatrix();

  if (layers_.empty() && !is_noise_drawn_) {
    for (const auto& noise : screen_noise_) {
      noise.draw();
    }
    is_noise_drawn_ = true;
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
