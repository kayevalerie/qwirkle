
#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <vector>
#include "Tile.h"
#define INITIALSIZE 48

class Board {
  size_t size;
  std::vector<Tile> grid();

 public:
  Board();
  ~Board();
  void displayBoard();
  int getSize();
  Tile getTile(int x, int y);
};

#endif  // ASSIGN2_BOARD_H
