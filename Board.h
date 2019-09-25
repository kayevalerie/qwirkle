
#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <vector>
#include "Tile.h"
#define ROWS 6
#define COLS 8

class Board {
  int rows;
  int cols;
  std::vector<std::vector<Tile>> grid;

 public:
  Board();
  ~Board();
  void clear();
  int getRows();
  int getCols();
  Tile getTile(char row, int col);
  void displayBoard();
  int getPrintedBoardWidth(int regularWidth);
};

#endif  // ASSIGN2_BOARD_H
