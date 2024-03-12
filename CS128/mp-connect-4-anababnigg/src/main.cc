#include <iostream>

#include "board.hpp"

int main() {
  // Board b;
  //  CheckForWinner(student, DiskType::kPlayer2);
  // bool result = SearchForWinner(b, DiskType::kPlayer2,
  // WinningDirection::kHorizontal); std::cout << result << std::endl;

  Board student;
  bool check = CheckForWinner(student, DiskType::kPlayer2);
  std::cout << check << std::endl;
}