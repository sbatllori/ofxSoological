#pragma once

#include "ofMain.h"

namespace soo {

class Brush {
 public:
  virtual ~Brush() = default;
  virtual void draw(const ofVec2f& center) = 0;
};
}  // namespace soo
