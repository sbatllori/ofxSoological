#pragma once

#include "ofMain.h"

namespace soo {
namespace colors {

using Palette = std::vector<int>;

inline ofColor GetBlendedColor(const float t, const float t_min,
                               const float t_max, const Palette& palette,
                               const float loops = 1.f) {
  // Get a floating index indicating the corresponding position to the given
  // value in the color palette (understanding the color palette as a continuous
  // range). That way:
  // - The integral part of the index defines the index of the current color
  // - The integral part of the index + 1 defines the index of the next color
  // - The fractional part of the index defines the amount of blending required
  // between the current color and the next color

  const float idx = ofMap(t, t_min, t_max, 0, loops * (palette.size() - 1));

  float integral;
  const float fractional = modf(idx, &integral);

  ofColor color;
  ofColor next_color;

  color.setHex(palette[static_cast<int>(integral) % palette.size()]);
  next_color.setHex(palette[(static_cast<int>(integral) + 1) % palette.size()]);

  color.lerp(next_color, fractional);

  return color;
}

const Palette procreate_flourish{
    0x8DF4A4, 0x67E4AA, 0x72D6BF, 0x7EC6CC, 0x86B3D3, 0x849DD6,
    0x7D87D9, 0x7C74DA, 0x8067D8, 0x6D4FD8, 0xA1F798, 0xA0E792,
    0xC3D59F, 0xDAC0A7, 0xE2A9AF, 0xE090B9, 0xD976C2, 0xCE5FC8,
    0xC34FCE, 0xC139CE, 0xCEF9AD, 0xC8E17B, 0xE0CB6D, 0xEDB066,
    0xF5926E, 0xF4727D, 0xEC5589, 0xE14192, 0xD5379C, 0xC3268A};

// source: https://www.schemecolor.com/orange-and-teal.php
const Palette orange_and_teal{0xFD5901, 0xF78104, 0xFAAB36,
                              0x249EA0, 0x008083, 0x005F60};

// source: https://www.schemecolor.com/hot-with-cold-color-combination.php
const Palette hot_with_cold{0xE23201, 0xFD9415, 0xFEB938,
                            0xFFF2CE, 0x002947, 0x6BBCD1};

// source: https://www.schemecolor.com/blues-of-the-sea.php
const Palette blues_of_the_sea{0x25b4d9, 0xf9fdfd, 0xd7eefc, 0xadd6e9,
                               0x7fb9d4};

// source: https://www.schemecolor.com/teal-monochromatic.php
const Palette teal_monochromatic{0x99E6B3, 0x73CDA7, 0x4DB39C, 0x269A90,
                                 0x008083};

// source: https://www.schemecolor.com/warm-yellow-monochromatic.php
const Palette warm_yellow_monochromatic{0xFFF0C5, 0xFCE7AA, 0xFBDF8D, 0xF8DA77,
                                        0xF3D265};

// source: https://www.schemecolor.com/pinkest-of-roses.php
const Palette pinkest_of_roses{0xfbf3f1, 0xf9dfdb, 0xfdcec7, 0xfec3bb,
                               0xfdb5af};

// source: https://www.schemecolor.com/pearly-whites.php
const Palette pearly_whites{0xEAF2FB, 0xF5F6FF, 0xFFFFFF, 0xFFFAEF, 0xfff4ef};

// source: https://www.schemecolor.com/shiny-black-gradient.php
const Palette shiny_black_gradient{0x000000, 0x1A1A1B, 0x353437, 0x4F4E52,
                                   0x69686D};

// source: https://www.schemecolor.com/comfortably-numb.php
const Palette confortably_numb{0xC56676, 0xEB9577, 0xFCDEA4, 0x9EA2C1,
                               0xB1D4C4};

// source: https://www.schemecolor.com/muted-prints.php
const Palette muted_prints{0xD17373, 0xEDB380, 0xF8EDC9, 0x18BADA, 0x6B6D8C};

// source: https://www.schemecolor.com/retro-blues-and-reds.php
const Palette retro_blues_and_reds{0x723239, 0xB35454, 0xA45E56,
                                   0x92C2C2, 0x73A9C2, 0x4C5676};

// source: https://www.schemecolor.com/80s-retro.php
const Palette retro_80s{0x270245, 0x871A85, 0xFF2941,
                        0xFEFF38, 0xFE18D3, 0x4206F1};
}  // namespace colors
}  // namespace soo
