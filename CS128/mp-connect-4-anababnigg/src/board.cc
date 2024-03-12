#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// MAIN FUNCTION: IN BOUNDS must be placed here for helpers.
bool BoardLocationInBounds(int row, int col) {
  return (col >= 0 && col < Board::kBoardWidth && row >= 0 &&
          row < Board::kBoardHeight);
}

// ****************** HELPERS (for CheckForWinner) ************************
// KHorizontal: Checks for a win horizontally
bool KHorizontal(Board& b, DiskType disk) {
  for (unsigned int row = 0; row < Board::kBoardHeight; row++) {
    int count = 0;
    for (unsigned int col = 0; col < Board::kBoardWidth; col++) {
      if (b.board[row][col] == disk) {
        count++;
        if (count == 4) {
          return true;
        }
      } else {
        count = 0;
      }
    }
  }
  return false;
}

// KVertical: Checks for a win vertically
bool KVertical(Board& b, DiskType disk) {
  for (unsigned int col = 0; col < Board::kBoardWidth; col++) {
    int count = 0;
    for (unsigned int row = 0; row < Board::kBoardHeight; row++) {
      if (b.board[row][col] == disk) {
        count++;
        if (count == 4) {
          return true;
        }
      } else {
        count = 0;
      }
    }
  }
  return false;
}

// KLeftDiag: Checks for a win on left diagonal
bool KLeftDiag(Board& b, DiskType disk) {
  for (unsigned int col = 0; col < Board::kBoardWidth; col++) {
    int count = 0;
    for (unsigned int row = 0; row < Board::kBoardHeight; row++) {
      if (b.board[row][col] == disk) {
        for (unsigned int i = 0; i < 4; i++) {
          if (BoardLocationInBounds((int)(row + i), (int)(col - i)) &&
              b.board[row + i][col - i] == disk) {
            count++;
            if (count == 4) {
              return true;
            }
          } else {
            count = 0;
          }
        }
      }
    }
  }
  return false;
}

// KRightDiag: Checks for a win on right diagonal
bool KRightDiag(Board& b, DiskType disk) {
  for (unsigned int col = 0; col < Board::kBoardWidth; col++) {
    int count = 0;
    for (unsigned int row = 0; row < Board::kBoardHeight; row++) {
      if (b.board[row][col] == disk) {
        for (unsigned int i = 0; i < 4; i++) {
          if (BoardLocationInBounds((int)(row + i), (int)(col + i)) &&
              b.board[row + i][col + i] == disk) {
            count++;
            if (count == 4) {
              return true;
            }
          } else {
            count = 0;
          }
        }
      }
    }
  }
  return false;
}

// ************************************************************************

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  for (unsigned int row = 0; row < Board::kBoardHeight; row++) {
    for (unsigned int col = 0; col < Board::kBoardWidth; col++) {
      b.board[row][col] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  // VALIDITY:
  if (col < 0 || col > Board::kBoardWidth) {
    throw std::runtime_error("invalid column");
  }
  if (b.board[Board::kBoardHeight - 1][col] != DiskType::kEmpty) {
    throw std::runtime_error("column full");
  }
  // DROP DISK:
  for (unsigned int row = 0; row < Board::kBoardHeight; row++) {
    if (b.board[row][col] == DiskType::kEmpty) {
      b.board[row][col] = disk;
      break;
    }
  }
}

bool CheckForWinner(Board& b, DiskType disk) {
  return SearchForWinner(b, disk, WinningDirection::kHorizontal) ||
         SearchForWinner(b, disk, WinningDirection::kVertical) ||
         SearchForWinner(b, disk, WinningDirection::kLeftDiag) ||
         SearchForWinner(b, disk, WinningDirection::kRightDiag);
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  bool winner_true = false;
  switch (to_check) {
  case WinningDirection::kHorizontal:
    winner_true = KHorizontal(b, disk);
    break;
  case WinningDirection::kVertical:
    winner_true = KVertical(b, disk);
    break;
  case WinningDirection::kLeftDiag:
    winner_true = KLeftDiag(b, disk);
    break;
  case WinningDirection::kRightDiag:
    winner_true = KRightDiag(b, disk);
    break;
  }
  return winner_true;
}

// ******************************************************************

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}