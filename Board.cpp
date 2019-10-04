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

bool Board::isInBounds(int row, int col) {
  return row >= 0 && row <= rows && col >= 0 && col <= cols;
}

bool Board::isValidPosition(char row, int col) {
  int row_pos = row - 'A';
  int col_pos = -1;
  bool validCoordinates = true;

  if (row_pos % 2 && col % 2) {  // even row and column
    col_pos = col / 2;
  } else if (!row_pos % 2 && !col % 2) {  // odd row and column
    col_pos = (col - 1) / 2;
  } else {
    validCoordinates = false;
  }

  return validCoordinates && isInBounds(row_pos, col_pos);
}

bool Board::isOccupied(int row, int col) {
  bool occupied = false;
  Tile* tile = nullptr;
  *tile = grid[row][col];

  if (tile) occupied = true;

  return occupied;
}

int* Board::hasValidAdjacentTiles(Tile* tile, int row, int col) {
  int match_adjacents[BOARDFRAME] = {-1, -1, -1, -1};

  if (!row % 2) {  // if checking for odd col
    if (isValidPosition(row - 1, col) &&
        isOccupied(row - 1, col)) {  // check top left
      if (grid[row - 1][col].getColour() == tile->getColour())
        match_adjacents[0] = 0;
      else if (grid[row - 1][col].getShape() == tile->getShape())
        match_adjacents[0] = 1;
    }

    if (isValidPosition(row + 1, col + 1) &&
        isOccupied(row + 1, col + 1)) {  // check bottom right
      if (grid[row + 1][col + 1].getColour() == tile->getColour())
        match_adjacents[1] = 0;
      else if (grid[row + 1][col + 1].getShape() == tile->getShape())
        match_adjacents[1] = 1;
    }

    if (isValidPosition(row - 1, col + 1) &&
        isOccupied(row - 1, col + 1)) {  // check top right
      if (grid[row - 1][col + 1].getColour() == tile->getColour())
        match_adjacents[2] = 0;
      else if (grid[row - 1][col + 1].getShape() == tile->getShape())
        match_adjacents[2] = 1;
    }

    if (isValidPosition(row + 1, col) &&
        isOccupied(row + 1, col)) {  // check bottom left
      if (grid[row + 1][col].getColour() == tile->getColour())
        match_adjacents[3] = 0;
      else if (grid[row + 1][col].getShape() == tile->getShape())
        match_adjacents[3] = 1;
    }
  } else {  // if even col
    if (isValidPosition(row - 1, col - 1) &&
        isOccupied(row - 1, col - 1)) {  // check top left
      if (grid[row - 1][col - 1].getColour() == tile->getColour())
        match_adjacents[0] = 0;
      else if (grid[row - 1][col - 1].getShape() == tile->getShape())
        match_adjacents[0] = 1;
    }

    if (isValidPosition(row + 1, col) &&
        isOccupied(row + 1, col)) {  // check bottom right
      if (grid[row + 1][col].getColour() == tile->getColour())
        match_adjacents[1] = 0;
      else if (grid[row + 1][col].getShape() == tile->getShape())
        match_adjacents[1] = 1;
    }

    if (isValidPosition(row - 1, col) &&
        isOccupied(row - 1, col)) {  // check top right
      if (grid[row - 1][col].getColour() == tile->getColour())
        match_adjacents[2] = 0;
      else if (grid[row - 1][col].getShape() == tile->getShape())
        match_adjacents[2] = 1;
    }

    if (isValidPosition(row + 1, col - 1) &&
        isOccupied(row + 1, col - 1)) {  // check bottom left
      if (grid[row + 1][col - 1].getColour() == tile->getColour())
        match_adjacents[3] = 0;
      else if (grid[row + 1][col - 1].getShape() == tile->getShape())
        match_adjacents[3] = 1;
    }
  }

  return match_adjacents;
}

int translateCol(int col) {
  int curCol = -1;

  if (col % 2) {  // even column
    curCol = col / 2;
  } else if (!col % 2) {  // odd column
    curCol = (col - 1) / 2;
  }
  return curCol;
}

int Board::countLeftDiagonalTiles(Tile* tile, int row, int col) {
  int count = 1;  // count current tile

  // validate top left
  int curRow = row;
  int curCol = col;
  bool hasSameTile = false;

  while (!hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      count++;
      if (grid[curRow][curCol].equals(tile)) hasSameTile = true;
    }

    curRow--;

    if (row % 2) curCol--;  // if currently in even position
  }                         // while

  // validate bottom right
  curRow = row;
  curCol = col;

  while (!hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      count++;
      if (grid[curRow][curCol].equals(tile)) hasSameTile = true;
    }

    curRow++;

    if (!row % 2) curCol++;  // if currently in odd position
  }                          // while

  return count;
}

int Board::countRightDiagonalTiles(Tile* tile, int row, int col) {
  // validate top right
  int curRow = row;
  int curCol = col;
  bool hasSameTile = false;
  int count = 1;

  while (!hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      count++;
      if (grid[curRow][curCol].equals(tile)) hasSameTile = true;
    }

    curRow--;

    if (!row % 2) curCol++;  // if currently in odd position
  }                          // while

  // validate bottom left
  curRow = row;
  curCol = col;

  while (!hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      count++;
      if (grid[curRow][curCol].equals(tile)) hasSameTile = true;
    }

    curRow++;

    if (row % 2) curCol--;  // if currently in even position
  }                         // while

  return count;
}

bool Board::addTile(Tile* tile, char row, int col) {
  bool validMove = true;
  int row_pos = row - 'A';
  int col_pos = translateCol(col);

  if (hasValidAdjacentTiles(tile, row_pos, col_pos))
    grid[row_pos][col_pos] = *tile;
  else
    validMove = false;

  return validMove;
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
