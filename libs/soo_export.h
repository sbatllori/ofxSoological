#pragma once

#include "ofMain.h"

namespace soo {

inline void SaveFrame(std::string out_path = "screenshot_" +
                                             ofGetTimestampString() + ".png") {
  glReadBuffer(GL_FRONT);
  ofSaveScreen(out_path);
}

inline void SaveFrame(const unsigned long num) {
  std::string zeroes = "00000000";
  zeroes = zeroes.substr(0, zeroes.length() - (ofToString(num).length()));
  std::string file_name = "./frames/f" + zeroes + ofToString(num) + ".png";

  SaveFrame(file_name);
}
}  // namespace soo
