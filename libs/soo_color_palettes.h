#pragma once

#include <vector>

namespace soo {
namespace colors {

using Palette = std::vector<int>;

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

}  // namespace colors
}  // namespace soo
