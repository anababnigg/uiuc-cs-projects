#include "seam_carver.hpp"
// implement the rest of SeamCarver's functions here

const ImagePPM& SeamCarver::GetImage() const	{
  return image_;
}

int SeamCarver::GetHeight() const	{
  return height_;
}

int SeamCarver::GetWidth() const {
  return width_;
}

int SeamCarver::TBsides(int row, int col) const {
  Pixel pixel_top = {};
  Pixel pixel_bottom= {};
  if (row != 0 && row != height_ - 1) {
    pixel_top = image_.GetPixel(row - 1, col);
    pixel_bottom = image_.GetPixel(row + 1, col);
  } else if(row == 0) {
    pixel_top = image_.GetPixel(height_ - 1, col);
    pixel_bottom = image_.GetPixel(row + 1, col);
  } else {
    pixel_top = image_.GetPixel(row - 1, col);
    pixel_bottom = image_.GetPixel(0, col);
  }
  int blue = pixel_top.GetBlue() - pixel_bottom.GetBlue();
  int green = pixel_top.GetGreen() - pixel_bottom.GetGreen();
  int red = pixel_top.GetRed() - pixel_bottom.GetRed();
  blue = blue * blue;
  green = green * green;
  red = red * red;
  return blue + green + red;
}

int SeamCarver::LRsides(int row, int col) const {
    Pixel pixel_right = {};
    Pixel pixel_left = {};
  if (col != 0 && col != width_ - 1) {
    pixel_right = image_.GetPixel(row, col + 1);
    pixel_left = image_.GetPixel(row, col - 1);
  } else if(col == 0) {
    pixel_right = image_.GetPixel(row, col + 1);
    pixel_left = image_.GetPixel(row , width_ - 1);
  } else {
    pixel_right = image_.GetPixel(row, 0);
    pixel_left = image_.GetPixel(row, col - 1);
  }
  int blue = pixel_right.GetBlue() - pixel_left.GetBlue();
  int green = pixel_right.GetGreen() - pixel_left.GetGreen();
  int red = pixel_right.GetRed() - pixel_left.GetRed();
  blue = blue * blue;
  green = green * green;
  red = red * red;
  return blue + green + red;
}


int SeamCarver::GetEnergy(int row, int col) const {
  return TBsides(row, col) + LRsides(row, col);
}


int** SeamCarver::VerticalArr() const {
  int** ppt = new int*[height_];
  for (int row = 0; row < height_; row++) {ppt[row] = new int[width_];}
  for(int row = height_ - 1; row >= 0; --row) {
    for (int col = 0; col < width_; ++col) {
      int least = 0;
      int energy = GetEnergy(row,col);
      if (row == height_ - 1) {ppt[row][col] = energy; continue;}        
        if (col != 0) {least = ppt[row + 1][col - 1] + energy;}
        if(least > ppt[row + 1][col] + energy || col == 0) {
          least = ppt[row + 1][col] + energy;
        }
        if (col != width_ - 1 && least > ppt[row + 1][col + 1] + energy){
          least = ppt[row + 1][col + 1] + energy;
        }
      ppt[row][col] = least;
    }
  }
  return ppt;
  for(int row = 0; row <height_; row++) {
    delete[] ppt[row];
  }
  delete[] ppt;
}

int** SeamCarver::HorizontalArr() const {
  int** ppt = new int*[height_];
  for (int row = 0; row < height_; row++) {
    ppt[row] = new int[width_];
  }
  for(int col = width_ - 1; col >= 0; col--) {
    for (int row = 0; row < height_; ++row) {
      int least = 0;
      int energy = GetEnergy(row,col);
      if (col == width_ - 1) {ppt[row][col] = energy; continue;}        
        if (row != 0) {least = ppt[row - 1][col + 1] + energy;}
        if(least > ppt[row][col + 1] + energy || row == 0) {
          least = ppt[row][col + 1] + energy;
        }
        if (row != height_ - 1 && least > ppt[row + 1][col + 1] + energy){
          least = ppt[row + 1][col + 1] + energy;
        }
      ppt[row][col] = least;
    }
  }
  return ppt;
}


int* SeamCarver::GetHorizontalSeam() const {
  int* ret = new int[width_];
  int**arr = HorizontalArr();
  int least = arr[0][0];
  int leastrow = 0;
  ret[0] = leastrow;
  for (int i = 0; i < height_; i++) {
    if (arr[i][0] < least) {
      least = arr[i][0]; 
      ret[0] = i; 
      leastrow = i;}
  }
  for (int col = 1; col < width_; ++col) {
    least = 0;
    int temp = leastrow;
    if (leastrow != height_ - 1) {least = arr[leastrow + 1][col]; temp = leastrow + 1;}
    if ((leastrow != 0 && least >= arr[leastrow - 1][col]) || leastrow == height_ - 1) {
      least = arr[leastrow - 1][col];
      temp = leastrow - 1;
    }
    if (least >= arr[leastrow][col]) {temp = leastrow;}
    leastrow = temp;
    ret[col] = leastrow;
  }
  for(int row = 0; row < height_; ++row) {
    delete[] arr[row];
  }
  delete[] arr;
return ret;
}

int* SeamCarver::GetVerticalSeam() const {
  int* ret = new int[height_];
  int**arr = VerticalArr();
  int least = arr[0][0];
  int leastcol = 0;
  ret[0] = leastcol;
  for (int i = 1; i < width_; i++) {
    if (arr[0][i] < least) {
      least = arr[0][i]; 
      ret[0] = i; 
      leastcol = i;
    }
  }
  for (int row = 1; row < height_; ++row) {
    least = 0;
    int temp = 0;
    if (leastcol != width_ - 1) least = arr[row][leastcol + 1]; temp = leastcol + 1;
    if ((leastcol != 0 && least >= arr[row][leastcol - 1]) || leastcol == width_ - 1) {
      least = arr[row][leastcol - 1];
      temp = leastcol - 1;
    }
    if (least >= arr[row][leastcol]) {temp = leastcol;}
    leastcol = temp;
    ret[row] = leastcol;
  }
  for(int row = 0; row < height_; ++row) {
    delete[] arr[row];
  }
  delete[] arr;
  return ret;
}

void SeamCarver::RemoveHorizontalSeam()	{
  const int* seam = GetHorizontalSeam();
  image_.RemoveHorizontalSeam(seam);
  height_ = height_ - 1;
  delete[] seam;
}

void SeamCarver::RemoveVerticalSeam()	{
  const int* seam = GetVerticalSeam();
  image_.RemoveVerticalSeam(seam);
  width_ = width_ - 1;
  delete[] seam;
}

// !! given functions below, DO NOT MODIFY !!

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
