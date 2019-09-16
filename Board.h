
#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <vector>
#include "Tile.h"
#define INITIAL_SIZE 48

class Board {
  size_t board_size;
  std::vector<Tile> grid;

 public:
  Board();
  ~Board();
  void clear();
  int getSize();
  Tile* getTile(int x, int y);
  void displayBoard();
};

#endif  // ASSIGN2_BOARD_H
