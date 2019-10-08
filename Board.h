
#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <vector>
#include "Tile.h"

#define ROWS 6
#define COLS 8

class Board {
  size_t rows;
  size_t cols;
  std::vector<std::vector<Tile>> grid;

  int getPrintedBoardWidth(int regularWidth);
  void clear();
  Tile getTile(int row, int col);
  int translateCol(int row);
  bool isOccupied(int row, int col);
  bool isInBounds(int row, int col);
  bool hasValidAdjacentTiles(Tile tile, int row, int col, int turn);

 public:
  Board();
  ~Board();
  size_t getRows();
  size_t getCols();
  bool addTile(Tile tile, char row, int col, int turn);
  bool isValidPosition(char row, int col);
  bool isInBounds(char row, int col);
  bool isOccupied(char row, int col);
  bool hasSameTileInLines(Tile tile, char row, int col);
  int countLeftDiagonalTiles(Tile tile, char row, int col, bool check);
  int countRightDiagonalTiles(Tile tile, char row, int col, bool check);
  void displayBoard();
};

#endif  // ASSIGN2_BOARD_H
