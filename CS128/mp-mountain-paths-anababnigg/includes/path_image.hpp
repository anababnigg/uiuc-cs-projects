#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cmath>
#include <cstdlib>  // for size_t
#include <fstream>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

class PathImage {
public:
  // functions
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  // getters + more
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color>>& GetPathImage() const;
  void ToPpm(const std::string& name) const;
  // helpers:
  void ColorPath();

private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  // helpers
  const Color kRed = {252, 25, 63};
  const Color kGreen = {31, 253, 13};
};

#endif