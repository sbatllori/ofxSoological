#pragma once

#include "ofMain.h"

namespace soo {
namespace vectors {

inline ofVec2f GetRandomUnitVec2() {
  return ofVec2f{ofRandom(-1.f, 1.f), ofRandom(-1.f, 1.f)}.normalize();
}
}  // namespace vectors
}  // namespace soo
