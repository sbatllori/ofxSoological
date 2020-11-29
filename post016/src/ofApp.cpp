#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetBackgroundAuto(false);
  ofSetFrameRate(3000);
  ofBackground(255);

  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, .55f);
    layer.spirograph_.AddNode({415, 0, 0}, 5.f, true);
    layer.spirograph_.AddNode({50, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(80);
      ofSetLineWidth(2);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.2f);
    layer.spirograph_.AddNode({280, 0, 0}, 4.f, true);
    layer.spirograph_.AddNode({100, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(80);
      ofSetLineWidth(8);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());

      ofSetColor(255);
      ofSetLineWidth(4);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.f);
    layer.spirograph_.AddNode({210, 0, 0}, 10.f, true);
    layer.spirograph_.AddNode({10, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(80);
      ofSetLineWidth(2);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 20.f);
    layer.spirograph_.AddNode({150, 0, 0}, 1.f, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(80);
      ofSetLineWidth(2);
      ofNoFill();

      const float radius = layer.previous_brush_position_.distance(
                               layer.spirograph_.brush_position()) /
                           8.f;
      ofDrawCircle(layer.previous_brush_position_, radius);
      ofDrawCircle(layer.spirograph_.brush_position(), radius);
    };
  }

  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.f);
    layer.spirograph_.AddNode({150, 0, 0}, 1.f, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0, 100);
      ofSetLineWidth(2);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }

  {
    Layer layer;
    layer.spirograph_.nodes_mutable().clear();
    layer.spirograph_.AddNode({0, 0, 0}, 1.1f);
    layer.spirograph_.AddNode({80, 0, 0}, 5.f, true);
    layer.spirograph_.AddNode({50, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0, 100);
      ofSetLineWidth(2);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  if (ofGetFrameNum() > 10) {
    //  Remove the closed spirographs
    layers_.erase(std::remove_if(layers_.begin(), layers_.end(),
                                 [](const Layer& layer) {
                                   return layer.spirograph_.IsCicleStart();
                                 }),
                  layers_.end());
  }

  for (auto& layer : layers_) {
    layer.previous_brush_position_ = layer.spirograph_.brush_position();
    layer.spirograph_.nodes_mutable()[0]->RotateZ();
    layer.spirograph_.nodes_mutable()[1]->RotateZ();
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofPushMatrix();
  ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  {
    for (auto& layer : layers_) {
      layer.draw();
    }
  }
  ofPopMatrix();
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
