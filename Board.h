
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

  int getPrintedBoardWidth(int regularWidth);
  void clear();
  Tile getTile(int row, int col);
  bool isValidPosition(int row, int col);
  bool hasValidAdjacentTiles(Tile tile, int row, int col);

 public:
  Board();
  ~Board();
  int getRows();
  int getCols();
  void addTile(Tile tile, char row, int col);
  void displayBoard();
};

#endif  // ASSIGN2_BOARD_H
