#include "grayscale_image.hpp"

// note for these functions, maybe change order of if statement?

// >> MAIN FUNCTIONS <<
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  // initalizing:
  Color grey;
  height_ = dataset.Height();
  width_ = dataset.Width();
  std::vector<std::vector<Color>> grey_data;
  std::vector<Color> grey_row;
  // populating:
  for (unsigned int h = 0; h < height_; h++) {
    for (unsigned int w = 0; w < width_; w++) {
      // initialize
      auto elevation_point = static_cast<double>(dataset.GetData().at(h).at(w));
      auto min_ele = dataset.MinEle();
      auto max_ele = dataset.MaxEle();
      double double_sog =
          std::abs(static_cast<double>(elevation_point - min_ele) /
                   (max_ele - min_ele) * kMaxColorValue);
      int shade_of_grey = static_cast<int>(std::round(double_sog));
      // check conditions
      if (max_ele == min_ele) {
        shade_of_grey = 0;
      }
      grey = {shade_of_grey, shade_of_grey, shade_of_grey};
      grey_row.push_back(grey);
    }
    grey_data.push_back(grey_row);
    grey_row.clear();
  }
  image_ = grey_data;
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height) {
  Color grey;
  ElevationDataset fileset = {filename, width, height};
  height_ = fileset.Height();
  width_ = fileset.Width();
  std::vector<std::vector<Color>> grey_data;
  std::vector<Color> grey_row;
  // populating
  for (unsigned int h = 0; h < height_; h++) {
    for (unsigned int w = 0; w < width_; w++) {
      auto elevation_point = static_cast<double>(fileset.GetData().at(h).at(w));
      auto min_ele = fileset.MinEle();
      auto max_ele = fileset.MaxEle();
      double double_sog =
          std::abs(static_cast<double>(elevation_point - min_ele) /
                   (max_ele - min_ele) * kMaxColorValue);
      int shade_of_grey = static_cast<int>(std::round(double_sog));
      // check conditions
      if (max_ele == min_ele) {
        shade_of_grey = 0;
      }
      grey = {shade_of_grey, shade_of_grey, shade_of_grey};
      grey_row.push_back(grey);
    }
    grey_data.push_back(grey_row);
    grey_row.clear();
  }
  image_ = grey_data;
}

// >> GETTERS, OTHER FUNCTIONS <<
size_t GrayscaleImage::Width() const { return width_; }

size_t GrayscaleImage::Height() const { return height_; }

unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }

const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_.at(row).at(col);
}

const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}

void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  if (ofs.fail()) throw "OFS FAIL";
  ofs << "P3"
      << "\n";
  ofs << width_ << " " << height_ << "\n";
  ofs << kMaxColorValue << "\n";
  // iterate through each pixel
  for (unsigned int h = 0; h < height_; h++) {
    for (unsigned int w = 0; w < width_; w++) {
      ofs << image_.at(h).at(w).Red() << " " << image_.at(h).at(w).Green()
          << " " << image_.at(h).at(w).Blue() << " ";
    }
    ofs << "\n";
  }
}
