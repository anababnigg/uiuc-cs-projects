#ifndef ELEVATION_DATASET_H
#define ELEVATION_DATASET_H

#include <cstdlib>  // for size_t
#include <fstream>
#include <string>
#include <vector>

class ElevationDataset {
public:
  // constructor
  ElevationDataset(const std::string& filename, size_t width, size_t height);
  // getters
  size_t Width() const;
  size_t Height() const;
  int MaxEle() const;
  int MinEle() const;
  // methods
  int DatumAt(size_t row, size_t col) const;
  const std::vector<std::vector<int>>& GetData() const;

private:
  // variables
  size_t width_;
  size_t height_;
  std::vector<std::vector<int>> data_;
  int max_ele_;
  int min_ele_;
  // helper vars
  const int kLowestnum = -999999999;
  const int kHighestnum = 999999999;
};

#endif