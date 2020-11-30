#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetBackgroundAuto(false);
  ofSetFrameRate(3000);
  ofBackground(255);

  // The following layers define the spirographs that compose the mandala from
  // the exterior to the interior.

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

  // Outer spiral
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 0.55f);
    layer.spirograph_.AddNode({400, 0, 0}, 5.f, true);
    layer.spirograph_.AddNode({50, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
      ofSetLineWidth(2);
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
      ofSetLineWidth(3);
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

  // Circles
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 360.f / 5.f);
    layer.spirograph_.AddNode({295, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofPushMatrix();
      ofRotateZDeg(18.f);
      {
        ofSetLineWidth(2);

        ofSetColor(255);
        ofFill();
        ofDrawCircle(layer.spirograph_.brush_position(), 20.f);

        ofSetColor(0);
        ofNoFill();
        ofDrawCircle(layer.spirograph_.brush_position(), 20.f);

        ofFill();
        ofDrawCircle(layer.spirograph_.brush_position(), 10.f);
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

  // Small flower center
  {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, 1.f);
    layer.spirograph_.AddNode({5, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
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

  // Rotate the spirograph brushes
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
    for (const auto& layer : layers_) {
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
  if (key == 'r') {
    layers_.clear();
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
