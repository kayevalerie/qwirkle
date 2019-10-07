#include "Board.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

#define BOARDFRAME 4
#define ADJACENT_SIZE 4

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

bool Board::isInBounds(int row, int col) {
  return row >= 0 && row < rows && col >= 0 && col < cols;
}

bool Board::isInBounds(char row, int col) {
  int row_pos = row - 'A';
  int col_pos = translateCol(col);

  return isInBounds(row_pos, col_pos);
}

bool Board::isValidPosition(char row,
                            int col) {  // does not accept positions like A1, B2
  int row_pos = row - 'A';

  return (row_pos % 2 && col % 2) || (!(row_pos % 2) && !(col % 2));
}

bool Board::isOccupied(int row, int col) {
  Tile tile;
  tile = grid[row][col];

  std::cout << "in isOccupied, row = " << row << " col = " << col << "\n";

  return tile.getColour() != Colour::NONE && tile.getShape() != Shape::NONE;
}

// bool Board::isOccupied(char row, int col) {
//   int row_pos = row - 'A';
//   int col_pos = translateCol(col);

//   return isOccupied(row_pos, col_pos);
// }

bool Board::hasValidAdjacentTiles(Tile tile, int row, int col) {
  bool valid = true;
  int match_adjacents[ADJACENT_SIZE] = {-1, -1, -1, -1};

  if (!row % 2) {  // if checking for odd col
    if (isInBounds(row - 1, col) &&
        isOccupied(row - 1, col)) {  // check top left
      if (grid[row - 1][col].getColour() == tile.getColour())
        match_adjacents[0] = 0;
      else if (grid[row - 1][col].getShape() == tile.getShape())
        match_adjacents[0] = 1;
      else
        match_adjacents[0] = 2;
    }

    if (isInBounds(row + 1, col + 1) &&
        isOccupied(row + 1, col + 1)) {  // check bottom right
      if (grid[row + 1][col + 1].getColour() == tile.getColour())
        match_adjacents[1] = 0;
      else if (grid[row + 1][col + 1].getShape() == tile.getShape())
        match_adjacents[1] = 1;
      else
        match_adjacents[0] = 2;
    }

    if (isInBounds(row - 1, col + 1) &&
        isOccupied(row - 1, col + 1)) {  // check top right
      if (grid[row - 1][col + 1].getColour() == tile.getColour())
        match_adjacents[2] = 0;
      else if (grid[row - 1][col + 1].getShape() == tile.getShape())
        match_adjacents[2] = 1;
      else
        match_adjacents[0] = 2;
    }

    if (isInBounds(row + 1, col) &&
        isOccupied(row + 1, col)) {  // check bottom left
      if (grid[row + 1][col].getColour() == tile.getColour())
        match_adjacents[3] = 0;
      else if (grid[row + 1][col].getShape() == tile.getShape())
        match_adjacents[3] = 1;
      else
        match_adjacents[0] = 2;
    }
  } else {  // if even col
    if (isInBounds(row - 1, col - 1) &&
        isOccupied(row - 1, col - 1)) {  // check top left
      if (grid[row - 1][col - 1].getColour() == tile.getColour())
        match_adjacents[0] = 0;
      else if (grid[row - 1][col - 1].getShape() == tile.getShape())
        match_adjacents[0] = 1;
      else
        match_adjacents[0] = 2;
    }

    if (isInBounds(row + 1, col) &&
        isOccupied(row + 1, col)) {  // check bottom right
      if (grid[row + 1][col].getColour() == tile.getColour())
        match_adjacents[1] = 0;
      else if (grid[row + 1][col].getShape() == tile.getShape())
        match_adjacents[1] = 1;
      else
        match_adjacents[0] = 2;
    }

    if (isInBounds(row - 1, col) &&
        isOccupied(row - 1, col)) {  // check top right
      if (grid[row - 1][col].getColour() == tile.getColour())
        match_adjacents[2] = 0;
      else if (grid[row - 1][col].getShape() == tile.getShape())
        match_adjacents[2] = 1;
      else
        match_adjacents[0] = 2;
    }

    if (isInBounds(row + 1, col - 1) &&
        isOccupied(row + 1, col - 1)) {  // check bottom left
      if (grid[row + 1][col - 1].getColour() == tile.getColour())
        match_adjacents[3] = 0;
      else if (grid[row + 1][col - 1].getShape() == tile.getShape())
        match_adjacents[3] = 1;
      else
        match_adjacents[0] = 2;
    }
  }

  int count = 0;
  for (int i = 0; i < ADJACENT_SIZE; i++) {
    if (match_adjacents[i] == -1) count++;
  }

  if (count == 0) {
    if (match_adjacents[0] == 2 || match_adjacents[1] == 2 ||
        match_adjacents[2] == 2 || match_adjacents[3] == 2 ||
        match_adjacents[0] != match_adjacents[1] ||
        match_adjacents[2] != match_adjacents[3])
      valid = false;
  } else if (count == 1) {
    if (match_adjacents[0] == -1) {  // top left cell empty
      if (match_adjacents[2] == 2 || match_adjacents[3] == 2 ||
          match_adjacents[1] == 2 || match_adjacents[2] != match_adjacents[3])
        valid = false;
    } else if (match_adjacents[1] == -1) {  // bottom right cell empty
      if (match_adjacents[0] == 2 || match_adjacents[2] == 2 ||
          match_adjacents[3] == 2 || match_adjacents[2] != match_adjacents[3])
        valid = false;
    } else if (match_adjacents[2] == -1) {  // top right cell empty
      if (match_adjacents[0] == 2 || match_adjacents[3] == 2 ||
          match_adjacents[1] == 2 || match_adjacents[0] != match_adjacents[1])
        valid = false;
    } else if (match_adjacents[3] == -1) {  // bottom left cell empty
      if (match_adjacents[2] == 2 || match_adjacents[0] == 2 ||
          match_adjacents[1] == 2 || match_adjacents[0] != match_adjacents[1])
        valid = false;
    }
  } else if (count == 2) {
    if (match_adjacents[0] == -1 &&
        match_adjacents[1] == -1) {  // left diagonals empty
      if (match_adjacents[2] == 2 || match_adjacents[3] == 2 ||
          (match_adjacents[2] == 0 && match_adjacents[3] == 1) ||
          (match_adjacents[2] == 1 && match_adjacents[3] == 0))
        valid = false;
    } else if (match_adjacents[2] == -1 &&
               match_adjacents[3] == -1) {  // right diagonals empty
      if (match_adjacents[0] == 2 || match_adjacents[1] == 2 ||
          (match_adjacents[0] == 0 && match_adjacents[1] == 1) ||
          (match_adjacents[0] == 1 && match_adjacents[1] == 0))
        valid = false;
    } else if (match_adjacents[0] == -1 &&
               match_adjacents[2] == -1) {  // top cells empty
      if (match_adjacents[1] == 2 || match_adjacents[3] == 2 ||
          (match_adjacents[1] == 0 && match_adjacents[3] == 1) ||
          (match_adjacents[1] == 1 && match_adjacents[3] == 0))
        valid = false;
    } else if (match_adjacents[1] == -1 &&
               match_adjacents[3] == -1) {  // bottom cells empty
      if (match_adjacents[0] == 2 || match_adjacents[2] == 2 ||
          (match_adjacents[0] == 0 && match_adjacents[2] == 1) ||
          (match_adjacents[0] == 1 && match_adjacents[2] == 0))
        valid = false;
    } else if (match_adjacents[0] == -1 &&
               match_adjacents[3] == -1) {  // left cells empty
      if (match_adjacents[1] == 2 || match_adjacents[2] == 2 ||
          (match_adjacents[1] == 0 && match_adjacents[2] == 1) ||
          (match_adjacents[1] == 1 && match_adjacents[2] == 0))
        valid = false;
    } else if (match_adjacents[1] == -1 &&
               match_adjacents[2] == -1) {  // right cells empty
      if (match_adjacents[0] == 2 || match_adjacents[3] == 2 ||
          (match_adjacents[0] == 0 && match_adjacents[3] == 1) ||
          (match_adjacents[0] == 1 && match_adjacents[3] == 0))
        valid = false;
    }
  } else if (count == 3) {
    if (match_adjacents[0] == 2 || match_adjacents[1] == 2 ||
        match_adjacents[2] == 2 || match_adjacents[3] == 2)
      valid = false;
  }

  std::cout << "in hasValidAdjacentTiles(), VALID = " << valid << '\n';

  return valid;
}

int Board::translateCol(int col) {
  int curCol = -1;

  if (col % 2 == 0) {  // even column
    if (col == 0)
      curCol = 0;
    else
      curCol = (col / 2);
  } else {  // odd column
    curCol = (col - 1) / 2;
  }

  // std::cout << "in translatecol, col = " << col << " curCol = " << curCol;

  return curCol;
}

int Board::countLeftDiagonalTiles(Tile tile, int row, int col) {
  int count = 1;  // count current tile

  // validate top left
  int curRow = row;
  int curCol = col;
  bool hasSameTile = false;

  while (!hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      count++;
      if (grid[curRow][curCol].equals(tile)) {
        hasSameTile = true;
        count = -1;
      }
    }

    curRow--;

    if (curRow % 2) curCol--;  // if currently in even position
  }                            // while

  // validate bottom right
  curRow = row;
  curCol = col;

  while (!hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      count++;
      if (grid[curRow][curCol].equals(tile)) {
        hasSameTile = true;
        count = -1;
      }
    }

    curRow++;

    if (!curRow % 2) curCol++;  // if currently in odd position
  }                             // while

  return count;
}

int Board::countRightDiagonalTiles(Tile tile, int row, int col) {
  // validate top right
  int curRow = row;
  int curCol = col;
  bool hasSameTile = false;
  int count = 1;

  while (!hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      count++;
      if (grid[curRow][curCol].equals(tile)) {
        hasSameTile = true;
        count = -1;
      }
    }

    curRow--;

    if (!curRow % 2) curCol++;  // if currently in odd position
  }                             // while

  // validate bottom left
  curRow = row;
  curCol = col;

  while (!hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      count++;
      if (grid[curRow][curCol].equals(tile)) {
        hasSameTile = true;
        count = -1;
      }
    }

    curRow++;

    if (curRow % 2) curCol--;  // if currently in even position
  }                            // while

  return count;
}

bool Board::addTile(Tile tile, char row, int col) {
  bool valid = true;
  int row_pos = row - 'A';
  int col_pos = translateCol(col);

  // std::cout << "\nIN ADDTILE(), COL_POS = " << col_pos;

  if (hasValidAdjacentTiles(tile, row_pos, col_pos)) {
    // std::cout << "row = " << row_pos << " col = " << col_pos << '\n';
    grid.at(row_pos).at(col_pos) = tile;
    std::cout << " valid adjacent tiles\n";
  } else
    valid = false;

  return valid;
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

  std::cout << "\n";
}

int Board::getPrintedBoardWidth(int regularWidth) {
  return (regularWidth * 2) + (regularWidth / 2) + BOARDFRAME;
}
