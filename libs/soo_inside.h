#pragma once

namespace soo {
namespace inside {

template <typename Vec>
inline bool InCircle(const Vec& point, const Vec& center, const float radius) {
    return point.distance(center) < radius;
}

}  // namespace inside
}  // namespace soo
