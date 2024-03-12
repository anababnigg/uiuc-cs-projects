#include "path_image.hpp"

void PathImage::ColorPath() {
  unsigned int min = 0;
  unsigned int minrow = 0;
  for (unsigned int row = 0; row < height_; ++row) {
    if (paths_.at(row).EleChange() < min || row == 0) {
      min = paths_.at(row).EleChange();
      minrow = row;
    }
    for (unsigned r = 0; r < width_; r++) {
      int change_row = static_cast<int>(paths_.at(row).GetPath().at(r));
      path_image_.at(change_row).at(r) = kRed;
    }
  }
  for (unsigned int g = 0; g < paths_.at(minrow).Length(); g++) {
    int change_row = static_cast<int>(paths_.at(minrow).GetPath().at(g));
    path_image_.at(change_row).at(g) = kGreen;
  }
}

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  path_image_ = image.GetImage();
  std::vector<Path> best_path_row;
  width_ = dataset.Width();
  height_ = dataset.Height();
  for (unsigned int row = 0; row < height_; row++) {
    int ele_diff = 0;
    unsigned int temprow = row;
    Path current_path = {width_, row};
    current_path.SetLoc(0, row);
    unsigned int row_for_path = row;
    for (unsigned int col = 1; col < width_; col++) {
      int prev_elevation = dataset.GetData().at(row).at(col - 1);
      int lowest = abs(prev_elevation - dataset.GetData().at(row).at(col));
      if (row >= 1 && abs(prev_elevation -
                          dataset.GetData().at(row - 1).at(col)) < lowest) {
        lowest = abs(prev_elevation - dataset.GetData().at(row - 1).at(col));
        row_for_path = row - 1;
      }
      if (row < height_ - 1 &&
          abs(prev_elevation - dataset.GetData().at(row + 1).at(col)) <=
              lowest) {
        lowest = abs(prev_elevation - dataset.GetData().at(row + 1).at(col));
        row_for_path = row + 1;
      }
      if (abs(prev_elevation - dataset.GetData().at(row).at(col)) <= lowest) {
        lowest = abs(prev_elevation - dataset.GetData().at(row).at(col));
        row_for_path = row;
      }
      ele_diff += lowest;
      row = row_for_path;
      current_path.SetLoc(col, row);
    }
    current_path.IncEleChange(ele_diff);
    best_path_row.push_back(current_path);
    row = temprow;
  }
  paths_ = best_path_row;
  ColorPath();
}

size_t PathImage::Width() const { return width_; }

size_t PathImage::Height() const { return height_; }

unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }

const std::vector<Path>& PathImage::Paths() const { return paths_; }

const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  if (ofs.fail()) throw "OFS FAIL";
  ofs << "P3"
      << "\n";
  ofs << width_ << ' ' << height_ << "\n";
  ofs << kMaxColorValue << "\n";
  for (unsigned int h = 0; h < height_; h++) {
    for (unsigned int w = 0; w < width_; w++) {
      ofs << path_image_.at(h).at(w).Red() << ' '
          << path_image_.at(h).at(w).Green() << ' '
          << path_image_.at(h).at(w).Blue() << ' ';
    }
    ofs << "\n";
  }
}
