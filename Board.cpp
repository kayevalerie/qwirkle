#include <Board.h>
#include <iostream>

Board::Board() : rows(ROWS), cols(COLS) {
  std::vector<Tile> vec(COLS);
  std::vector<std::vector<Tile> > grid(ROWS, vec);
}

Board::~Board() { clear(); }

void Board::clear() {
  rows = 0;
  cols = 0;
}

int Board::getRows() { return rows; }

int Board::getCols() { return cols; }

Tile Board::getTile(char row, int col) {
  int int_row = row - 'A';
  return grid[int_row][col];
}

void Board::displayBoard() {
  // todo

  // for (unsigned int i = 0; i < grid.size(); i++) {
  //   for (unsigned int j = 0; j < grid[i].size(); j++)
  //     std::cout << grid[i][j].getColour() << grid[i][j].getShape() << " ";
  //   std::cout << std::endl;
  // }
}