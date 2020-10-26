#pragma once

namespace soo {
namespace motion {

template <typename Vec>
inline Vec UniformLinear(const Vec& position, const Vec& direction,
                         const float speed) {
  return position + speed * direction;
}

}  // namespace motion
}  // namespace soo
