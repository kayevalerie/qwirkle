#include <Board.h>
#include <iostream>

Board::Board()
    : rows(ROWS),
      cols(COLS),
      grid(std::vector<std::vector<Tile> >(ROWS, std::vector<Tile>(COLS / 2))) {
  if (COLS % 2) {
    for (unsigned int i = 0; i < grid.size(); i++) {
      if (i % 2 == 0) grid[i].resize(COLS / 2 + 1);
    }
  }
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