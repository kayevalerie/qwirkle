
#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <vector>
#include "Tile.h"

#define INIT_ROWS 6
#define INIT_COLS 8

class Board {
  std::vector<std::vector<Tile>> grid;
  int leftDiagonals;
  int rightDiagonals;

  int getPrintedBoardWidth(int regularWidth);
  void clear();

  int translateCol(int row);

  bool isOccupied(int row, int col);
  bool isInBounds(int row, int col);

  // bool hasValidAdjacentTiles(Tile tile, int row, int col, int turn);
  std::vector<int> matchAdjacentTiles(Tile tile, int row, int col);
  bool hasValidAdjacentTiles(std::vector<int> match_adjacents);
  bool hasValidLeftDiagonalTiles(Tile tile, char row, int col);
  bool hasValidRightDiagonalTiles(Tile tile, char row, int col);
  void resize();
  void adjustCols(int cols);

  Tile getTile(int row, int col);

 public:
  Board();
  ~Board();
  int getRows();
  int getCols(int row);
  bool addTile(Tile tile, char row, int col, int turn);
  bool addTileFromSave(Tile tile, char row, int col);
  bool isValidPosition(char row, int col);
  bool isInBounds(char row, int col);
  bool isOccupied(char row, int col);
  // bool hasSameTileInLines(Tile tile, char row, int col);
  void displayBoard();
  int getLeftDiagonalTiles();
  int getRightDiagonalTiles();
};

#endif  // ASSIGN2_BOARD_H
