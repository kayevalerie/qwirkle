
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
  int translateCol(int col);
  bool isOccupied(int row, int col);
  bool isInBounds(int row, int col);
  int countLeftDiagonalTiles(Tile tile, int row, int col);
  int countRightDiagonalTiles(Tile tile, int row, int col);
  int* hasValidAdjacentTiles(int* match_adjacents, Tile* tile, int row,
                             int col);

 public:
  Board();
  ~Board();
  int getRows();
  int getCols();
  bool addTile(Tile tile, char row, int col);
  bool isValidPosition(char row, int col);
  bool isInBounds(char row, int col);
  bool isOccupied(char row, int col);
  void displayBoard();
};

#endif  // ASSIGN2_BOARD_H
