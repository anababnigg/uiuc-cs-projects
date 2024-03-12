#include "elevation_dataset.hpp"

// >> MAIN METHODS <<
ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height) {
  int eleval = 0;
  int max = kLowestnum;
  int min = kHighestnum;
  std::ifstream ifs(filename);
  if (ifs.fail()) throw std::runtime_error("File Fail");
  for (unsigned int h = 0; h < height; h++) {
    std::vector<int> data_row;
    for (unsigned int w = 0; w < width; w++) {
      ifs >> eleval;
      if (ifs.fail()) throw "ifs fail";
      if (min >= eleval) min = eleval;
      if (max <= eleval) max = eleval;
      data_row.push_back(eleval);
    }
    data_.push_back(data_row);
  }
  while (ifs.good()) {
    ifs >> eleval;
    if (ifs.fail()) break;
    throw std::runtime_error("error: timed out");
  }
  width_ = width;
  height_ = height;
  max_ele_ = max;
  min_ele_ = min;
}

// >> GETTERS <<
size_t ElevationDataset::Width() const { return width_; }

size_t ElevationDataset::Height() const { return height_; }

int ElevationDataset::MaxEle() const { return max_ele_; }

int ElevationDataset::MinEle() const { return min_ele_; }

int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_.at(row).at(col);
}

const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}
