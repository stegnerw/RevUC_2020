#ifndef PROCESSED_FRAME_HPP
#define PROCESSED_FRAME_HPP

#include <vector>

struct ProcessedFrame {
  std::vector<float>  breathGraph();
  std::uint16_t       periodMS;
};

#endif
