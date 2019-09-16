#include <Board.h>

Board::Board() : board_size(INITIAL_SIZE) {
  std::vector<Tile> grid(INITIAL_SIZE);
}

Board::~Board() { clear(); }

void Board::clear() { board_size = 0; }

int Board::getSize() { return board_size; }

Tile* Board::getTile(int x, int y) {
  // todo
}

void Board::displayBoard() {
  // todo
}