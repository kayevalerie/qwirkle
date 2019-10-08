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

size_t Board::getRows() { return rows; }

size_t Board::getCols() { return cols; }

Tile Board::getTile(int row, int col) { return grid[row][col]; }

bool Board::isInBounds(int row, int col) {
  unsigned int i = row, j = col;
  return i >= 0 && i < rows && j >= 0 && j < cols;
}

bool Board::isInBounds(char row, int col) {
  return isInBounds(row - 'A', translateCol(col));
}

bool Board::isValidPosition(char row,
                            int col) {  // does not accept positions like A1, B2
  int row_pos = row - 'A';

  return (row_pos % 2 && col % 2) || (!(row_pos % 2) && !(col % 2));
}

bool Board::isOccupied(int row, int col) {
  Tile tile = grid[row][col];

  return tile.getColour() != Colour::NONE && tile.getShape() != Shape::NONE;
}

bool Board::isOccupied(char row, int col) {
  return isOccupied(row - 'A', translateCol(col));
}

bool Board::hasValidAdjacentTiles(Tile tile, int row, int col, int turn) {
  bool valid = true;
  int match_adjacents[ADJACENT_SIZE] = {-1, -1, -1, -1};

  if (row % 2 == 1) {  // if checking for odd col
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
    std::cout << "COUNT = 3\n";
    if (match_adjacents[0] == 2 || match_adjacents[1] == 2 ||
        match_adjacents[2] == 2 || match_adjacents[3] == 2)
      valid = false;
  } else if (count == 4 && turn != 0) {
    valid = false;
  }

  return valid;
}

int Board::translateCol(int col) {
  int curCol = -1;

  if (col % 2 == 0) {  // even column
    curCol = (col / 2);
  } else  // odd column
    curCol = (col - 1) / 2;

  return curCol;
}

bool Board::hasSameTileInLines(Tile tile, char row, int col) {
  return countLeftDiagonalTiles(tile, row, col, true) == -1 ||
         countRightDiagonalTiles(tile, row, col, true) == -1;
}

int Board::countLeftDiagonalTiles(Tile tile, char row, int col, bool check) {
  int count = 1;  // count current tile
  bool hasSameTile = false;

  // validate top left
  int curRow = row - 'A';
  int curCol = translateCol(col);
  bool oddCol;

  if (col % 2 == 0) {  // if currently in even position
    oddCol = false;
  } else
    oddCol = true;

  while (!hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      std::cout << "curRow = " << curRow << "\tcurCol = " << curCol << "\n";

      if (curRow != row - 'A' && curCol != translateCol(col)) {
        if (grid[curRow][curCol].equals(tile)) {
          hasSameTile = true;
          count = -1;
        } else
          count++;
      }
    }

    curRow--;

    if (!oddCol) {  // if currently in even position
      curCol--;
      oddCol = true;
    } else
      oddCol = false;

  }  // while

  // validate bottom right
  curRow = row - 'A';
  curCol = translateCol(col);

  if (col % 2 != 0) {
    oddCol = true;
  } else
    oddCol = false;

  while (!hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      std::cout << "curRow = " << curRow << "\tcurCol = " << curCol << "\n";

      if (curRow != row - 'A' && curCol != translateCol(col)) {
        if (grid[curRow][curCol].equals(tile)) {
          hasSameTile = true;
          count = -1;
        } else
          count++;
      }
    }

    curRow++;

    if (oddCol) {  // if currently in odd position
      curCol++;
      oddCol = false;
    } else
      oddCol = true;

  }  // while

  return count;
}

// PROBLEM WITH COUNT: MUST BE COUNTED TWICE IF EXISTS IN TWO LINES

int Board::countRightDiagonalTiles(Tile tile, char row, int col, bool check) {
  bool hasSameTile = false;
  int count = 0;

  // validate top right
  int curRow = row - 'A';
  int curCol = translateCol(col);
  bool oddCol;

  if (col % 2 != 0) {
    oddCol = true;
  } else
    oddCol = false;

  while (!hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      std::cout << "curRow = " << curRow << "\tcurCol = " << curCol << "\n";

      if (curRow != row - 'A' && curCol != translateCol(col)) {
        if (grid[curRow][curCol].equals(tile)) {
          hasSameTile = true;
          count = -1;
        } else
          count++;
      }
    }

    curRow--;

    if (oddCol) {
      curCol++;        // if currently in odd position
      oddCol = false;  // next position is an even position
    } else
      oddCol = true;

  }  // while

  // validate bottom left
  curRow = row - 'A';
  curCol = translateCol(col);

  if (col % 2 == 0) {
    oddCol = false;
  } else
    oddCol = true;

  while (!hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      std::cout << "curRow = " << curRow << "\tcurCol = " << curCol << "\n";

      if (curRow != row - 'A' && curCol != translateCol(col)) {
        if (grid[curRow][curCol].equals(tile)) {
          hasSameTile = true;
          count = -1;
        } else
          count++;
      }
    }

    curRow++;

    if (!oddCol) {  // if currently in even position
      curCol--;
      oddCol = true;
    } else  // next position is an odd position
      oddCol = false;

  }  // while

  return count;
}

int Board::getFilledTiles() {
  int count = 0;

  for (unsigned int i = 0; i < rows; i++)
    for (unsigned int j = 0; j < cols; j++)
      if (grid[i][j].getColour() != Colour::NONE &&
          grid[i][j].getShape() != Shape::NONE)
        count++;

  return count;
}

bool Board::addTile(Tile tile, char row, int col, int turn) {
  bool valid = true;
  int row_pos = row - 'A';
  int col_pos = translateCol(col);

  if (hasValidAdjacentTiles(tile, row_pos, col_pos, turn)) {
    grid.at(row_pos).at(col_pos) = tile;
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
