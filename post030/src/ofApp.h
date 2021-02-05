#pragma once

#include "ofMain.h"
#include "soo_color_palettes.h"

struct ColorSettings {
  ofColor background_;
  ofColor moon_;
  soo::colors::Palette waves_;

  ColorSettings(const ofColor& background, const ofColor& moon,
                const soo::colors::Palette& waves)
      : background_(background), moon_(moon), waves_(waves) {}
};

const ColorSettings kDaySettings(ofColor(132, 215, 250), ofColor(255, 221, 0),
                                 soo::colors::pinkest_of_roses);

const ColorSettings kNightSettings(ofColor(0), ofColor(255),
                                   soo::colors::orange_and_teal);
class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  const ColorSettings color_settings_ = kDaySettings;
};
