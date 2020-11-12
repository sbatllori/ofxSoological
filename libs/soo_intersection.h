#pragma once

#include "ofMain.h"

namespace soo {
namespace intersection {

/**
 * @brief HorizontalAxis_ClosedPolyline Computes the intersection points between
 * an horizontal axis defined by a Y-value, and a closed polygon defined by a
 * polyline.
 *
 * @param y float defining the horizontal axis
 * @param closed_polyline ofPolyline defining the closed polygon
 * @param spacing float defining the intersection precision error
 * @return the intersection points
 */
inline std::vector<ofVec2f> HorizontalAxis_ClosedPolyline(
    const float y, const ofPolyline& closed_polyline,
    const float spacing = 1.f) {
  // Consider an arbitrary closed polygon, and an horizontal line that might be
  // cutting its border in 2^n or no point. This function returns the
  // intersection points between the horizontal axis and the closed polygon.
  //
  //       +---------------+
  //       |   . .     .   |
  //       |   .    . .  . |
  //       |   .          .|
  //       |.           .  |
  //       |   .       .   |
  //  y ---A---X-------X---B---
  //       |   .        .  |
  //       |   .     . .   |
  //       |     . .       |
  //       +---------------+

  // Consider only the horizontal line segment that is inside the bounding box
  // of the polygon
  const ofRectangle polygon_bbox = closed_polyline.getBoundingBox();
  ofPolyline segment;
  segment.addVertex(polygon_bbox.x - spacing, y);                       // A
  segment.addVertex(polygon_bbox.x + polygon_bbox.width + spacing, y);  // B
  segment = segment.getResampledBySpacing(spacing);

  // Iterate over the segment vertices and find pairs of consecutive points such
  // that one point is inside the polygon, and the other one outside the
  // polygon. When this disparity happens, we found an intersection point
  // between the segment and the polygon.
  std::vector<ofVec2f> intersection_points;

  // Use transform as a first filter step to find the intersection points.
  // Return NAN for the non-intersection values.
  const ofVec2f point_to_remove(std::numeric_limits<float>::quiet_NaN());
  std::transform(
      segment.begin(), --segment.end(), ++segment.begin(),
      std::back_inserter(intersection_points),
      [&closed_polyline, &point_to_remove](const ofVec2f& current,
                                           const ofVec2f& next) {
        const bool is_current_in = closed_polyline.inside(current.x, current.y);
        const bool is_next_in = closed_polyline.inside(next.x, next.y);

        return (is_current_in ^ is_next_in) ? current : point_to_remove;
      });

  // Use remove as a second filter step to erase the NAN values and keep only
  // the intersection points.
  intersection_points.erase(
      std::remove_if(intersection_points.begin(), intersection_points.end(),
                     [](const ofVec2f& point) { return std::isnan(point.x); }),
      intersection_points.end());

  return intersection_points;
}

}  // namespace intersection
}  // namespace soo
