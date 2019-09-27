#include <Board.h>
#include <iomanip>
#include <iostream>

#define BOARDFRAME 4

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

Tile Board::getTile(int row, int col) { return grid[row][col]; }

bool Board::isValidPosition(int row, int col) {
  // check if accessible position

  // check if already occupied
}

bool Board::hasValidAdjacentTiles(Tile tile, int row, int col) {
  // check if tile's DIRECT adjacents match
}

void Board::addTile(Tile tile, char row, int col) {
  int row_pos = row - 'A';
  int col_pos = -1;

  if (col % 2) {  // even column
    col_pos = col / 2;
  } else {
    col_pos = (col - 1) / 2;
  }

  if (isValidPosition(row_pos, col_pos)) {
    if (hasValidAdjacentTiles(tile, row_pos, col_pos)) {
      grid[row_pos][col_pos] = tile;
    }
  }
}

void Board::displayBoard() {
  char rowLetter = 'A';

  for (int i = 0; i < COLS; i++) {
    if (i % 2 == 0) {
      std::cout << std::setw(5) << i;
    }
  }

  std::cout << "\n  ";
  for (int i = 0; i < getPrintedBoardWidth(COLS); i++) {
    std::cout << '-';
  }
  std::cout << "\n";
  for (unsigned int i = 0; i < grid.size(); i++) {
    std::cout << rowLetter << " ";
    for (unsigned int j = 0; j < grid[i].size(); j++) {
      if (i % 2 == 0) {
        std::cout << "| " << grid[i][j].toString() << " ";
      } else if (i % 2 != 0) {
        if (j == 0) {
          std::cout << "   | " << grid[i][j].toString() << " ";
        } else
          std::cout << "| " << grid[i][j].toString() << " ";
      }
      if (j == grid[i].size() - 1) {
        std::cout << "|\n";
      }
    }
    rowLetter += 1;
  }
  std::cout << "  ";
  for (int i = 0; i < getPrintedBoardWidth(COLS); i++) {
    std::cout << '-';
  }
  std::cout << "\n   ";
  for (int i = 0; i < COLS; i++) {
    if (i % 2 != 0) {
      std::cout << std::setw(5) << i;
    }
  }

  std::cout << "\n  ";
}

int Board::getPrintedBoardWidth(int regularWidth) {
  return (regularWidth * 2) + (regularWidth / 2) + BOARDFRAME;
}
