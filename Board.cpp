#include "Board.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

#define BOARDFRAME 4
#define ADJACENT_SIZE 4

Board::Board()
    : grid(std::vector<std::vector<Tile> >(INIT_ROWS,
                                           std::vector<Tile>(INIT_COLS / 2))),
      leftDiagonals(0),
      rightDiagonals(0) {
  adjustCols(INIT_COLS);
}

Board::~Board() { clear(); }

void Board::clear() {
  leftDiagonals = 0;
  rightDiagonals = 0;

  // reset grid to initial size
  grid = std::vector<std::vector<Tile> >(INIT_ROWS,
                                         std::vector<Tile>(INIT_COLS / 2));
  adjustCols(INIT_COLS);
}

void Board::adjustCols(int cols) {
  if (cols % 2 != 0) {
    for (unsigned int i = 0; i < grid.size(); i++) {
      if (i % 2 == 0) grid[i].resize(cols / 2 + 1);
    }
  }
}

int Board::getRows() { return (int)grid.size(); }

int Board::getCols(int row) { return (int)grid[row].size(); }

bool Board::isInBounds(int row, int col) {
  unsigned int i = row, j = col;

  return i >= 0 && i < grid.size() && j >= 0 && j < grid[i].size();
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
  return grid[row][col].getColour() != Colour::NONE &&
         grid[row][col].getShape() != Shape::NONE;
}

bool Board::isOccupied(char row, int col) {
  return isOccupied(row - 'A', translateCol(col));
}

std::vector<int> Board::matchAdjacentTiles(Tile tile, int row, int col) {
  std::vector<int> match_adjacents = {-1, -1, -1, -1};
  Tile *toCheck = nullptr;

  if (row % 2 == 1) {  // if checking for odd col
    if (isInBounds(row - 1, col) &&
        isOccupied(row - 1, col)) {  // check top left

      toCheck = &grid[row - 1][col];
      // std::cout << "\nTL \t" << toCheck->toString() << "\tTO COMPARE SHAPE =
      // "
      //           << std::to_string((int)(toCheck->getShape()))
      //           << "TILE SHAPE = " << std::to_string((int)(tile.getShape()));

      if (toCheck->getColour() == tile.getColour())
        match_adjacents[0] = 0;
      else if (toCheck->getShape() == tile.getShape())
        match_adjacents[0] = 1;
      else
        match_adjacents[0] = 2;
    }

    if (isInBounds(row + 1, col + 1) &&
        isOccupied(row + 1, col + 1)) {  // check bottom right

      toCheck = &grid[row + 1][col + 1];
      // std::cout << "\nBR \t" << toCheck->toString() << "\tTO COMPARE SHAPE =
      // "
      //           << std::to_string((int)(toCheck->getShape()))
      //           << "TILE SHAPE = " << std::to_string((int)(tile.getShape()));

      if (toCheck->getColour() == tile.getColour())
        match_adjacents[1] = 0;
      else if (toCheck->getShape() == tile.getShape())
        match_adjacents[1] = 1;
      else
        match_adjacents[1] = 2;
    }

    if (isInBounds(row - 1, col + 1) &&
        isOccupied(row - 1, col + 1)) {  // check top right

      toCheck = &grid[row - 1][col + 1];
      // std::cout << "\nTR \t" << toCheck->toString() << "\tTO COMPARE SHAPE =
      // "
      //           << std::to_string((int)(toCheck->getShape()))
      //           << "TILE SHAPE = " << std::to_string((int)(tile.getShape()));

      if (toCheck->getColour() == tile.getColour())
        match_adjacents[2] = 0;
      else if ((toCheck->getShape()) == (tile.getShape()))
        match_adjacents[2] = 1;
      else
        match_adjacents[2] = 2;
    }

    if (isInBounds(row + 1, col) &&
        isOccupied(row + 1, col)) {  // check bottom left

      toCheck = &grid[row + 1][col];
      // std::cout << "\nBL \t" << toCheck->toString() << "\tTO COMPARE SHAPE =
      // "
      //           << std::to_string((int)(toCheck->getShape()))
      //           << "TILE SHAPE = " << std::to_string((int)(tile.getShape()));

      if (toCheck->getColour() == tile.getColour())
        match_adjacents[3] = 0;
      else if (toCheck->getShape() == tile.getShape())
        match_adjacents[3] = 1;
      else
        match_adjacents[3] = 2;
    }
  } else {  // if even col
    if (isInBounds(row - 1, col - 1) &&
        isOccupied(row - 1, col - 1)) {  // check top left

      toCheck = &grid[row - 1][col - 1];
      // std::cout << "\nTL \t" << toCheck->toString() << "\tTO COMPARE SHAPE =
      // "
      //           << std::to_string((int)(toCheck->getShape()))
      //           << "TILE SHAPE = " << std::to_string((int)(tile.getShape()));

      if (toCheck->getColour() == tile.getColour())
        match_adjacents[0] = 0;
      else if (toCheck->getShape() == tile.getShape())
        match_adjacents[0] = 1;
      else
        match_adjacents[0] = 2;
    }

    if (isInBounds(row + 1, col) &&
        isOccupied(row + 1, col)) {  // check bottom right

      toCheck = &grid[row + 1][col];
      // std::cout << "\nBR \t" << toCheck->toString() << "\tTO COMPARE SHAPE =
      // "
      //           << std::to_string((int)(toCheck->getShape()))
      //           << "TILE SHAPE = " << std::to_string((int)(tile.getShape()));

      if (toCheck->getColour() == tile.getColour())
        match_adjacents[1] = 0;
      else if (toCheck->getShape() == tile.getShape())
        match_adjacents[1] = 1;
      else
        match_adjacents[1] = 2;
    }

    if (isInBounds(row - 1, col) &&
        isOccupied(row - 1, col)) {  // check top right

      toCheck = &grid[row - 1][col];
      // std::cout << "\nTR \t" << toCheck->toString() << "\tTO COMPARE SHAPE =
      // "
      //           << std::to_string((int)(toCheck->getShape()))
      //           << "TILE SHAPE = " << std::to_string((int)(tile.getShape()));

      if (toCheck->getColour() == tile.getColour())
        match_adjacents[2] = 0;
      else if (toCheck->getShape() == tile.getShape())
        match_adjacents[2] = 1;
      else
        match_adjacents[2] = 2;
    }

    if (isInBounds(row + 1, col - 1) &&
        isOccupied(row + 1, col - 1)) {  // check bottom left

      toCheck = &grid[row + 1][col - 1];
      // std::cout << "\nBL \t" << toCheck->toString() << "\tTO COMPARE SHAPE =
      // "
      //           << std::to_string((int)(toCheck->getShape()))
      //           << "TILE SHAPE = " << std::to_string((int)(tile.getShape()));

      if (toCheck->getColour() == tile.getColour())
        match_adjacents[3] = 0;
      else if (toCheck->getShape() == tile.getShape())
        match_adjacents[3] = 1;
      else
        match_adjacents[3] = 2;
    }
  }

  // std::cout << "\tmatch_adjacents = ";
  // for (unsigned int i = 0; i < match_adjacents.size(); i++)
  //   std::cout << match_adjacents[i] << ',';
  // std::cout << '\n';

  return match_adjacents;
}

bool Board::hasValidAdjacentTiles(std::vector<int> match_adjacents) {
  bool valid = true;
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

bool Board::hasValidLeftDiagonalTiles(Tile tile, char row, int col) {
  leftDiagonals = 0;  // count current tile

  bool hasSameTile = false, foundOtherTile = false, colorMatch = false,
       shapeMatch = false, allMatch = true;

  // ================== validate top left ==========================

  int curRow = row - 'A';
  int curCol = translateCol(col);
  bool oddCol;

  if (col % 2 == 0) {  // if currently in even position
    oddCol = false;
  } else
    oddCol = true;

  std::vector<int> match_adjacents = matchAdjacentTiles(tile, curRow, curCol);

  if (match_adjacents[0] == 0) {  // found a color match
    colorMatch = true;

    // std::cout << "found color match, curr shapeMatch =" << shapeMatch
    //           << "\tcolorMatch =" << colorMatch << '\n';

  } else if (match_adjacents[0] == 1) {  // found a shape match
    shapeMatch = true;

    // std::cout << "found shape match, curr shapeMatch =" << shapeMatch
    //           << "\tcolorMatch =" << colorMatch << '\n';
  }

  while (allMatch && !hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      // std::cout << "curRow = " << curRow << "\tcurCol = " << curCol <<
      // "\t\t";

      match_adjacents =
          matchAdjacentTiles(getTile(curRow, curCol), curRow, curCol);

      if (match_adjacents[0] == 0) {  // found a color match
        colorMatch = true;
        if (shapeMatch) allMatch = false;

        // std::cout << "found color match, curr shapeMatch =" << shapeMatch
        //           << "\tcolorMatch =" << colorMatch << '\n';

      } else if (match_adjacents[0] == 1) {  // found a shape match

        shapeMatch = true;
        if (colorMatch) allMatch = false;

        // std::cout << "found shape match, curr shapeMatch =" << shapeMatch
        //           << "\tcolorMatch =" << colorMatch << '\n';
      }

      if (curRow != row - 'A' || curCol != translateCol(col)) {
        foundOtherTile = true;

        if (grid[curRow][curCol].equals(tile)) {
          hasSameTile = true;
        } else
          leftDiagonals++;
      }
    }

    curRow--;

    if (!oddCol) {  // if currently in even position
      curCol--;
      oddCol = true;
    } else
      oddCol = false;

  }  // while

  // ================== validate bottom right ==========================

  curRow = row - 'A';
  curCol = translateCol(col);

  if (col % 2 != 0) {
    oddCol = true;
  } else
    oddCol = false;

  match_adjacents = matchAdjacentTiles(tile, curRow, curCol);

  if (match_adjacents[1] == 0) {  // found a color match
    colorMatch = true;

    // std::cout << "found color match, curr shapeMatch =" << shapeMatch
    //           << "\tcolorMatch =" << colorMatch << '\n';

  } else if (match_adjacents[1] == 1) {  // found a shape match
    shapeMatch = true;

    // std::cout << "found shape match, curr shapeMatch =" << shapeMatch
    //           << "\tcolorMatch =" << colorMatch << '\n';
  }

  while (allMatch && !hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      // std::cout << "curRow = " << curRow << "\tcurCol = " << curCol <<
      // "\t\t";

      match_adjacents =
          matchAdjacentTiles(getTile(curRow, curCol), curRow, curCol);

      if (match_adjacents[1] == 0) {  // found a color match
        colorMatch = true;
        if (shapeMatch) allMatch = false;

        // std::cout << "found shape match, curr shapeMatch =" << shapeMatch
        //           << "\tcolorMatch =" << colorMatch << '\n';

      } else if (match_adjacents[1] == 1) {  // found a shape match
        shapeMatch = true;
        if (colorMatch) allMatch = false;

        // std::cout << "found shape match, curr shapeMatch =" << shapeMatch
        //           << "\tcolorMatch =" << colorMatch << '\n';
      }

      if (curRow != row - 'A' || curCol != translateCol(col)) {
        foundOtherTile = true;

        if (grid[curRow][curCol].equals(tile)) {
          hasSameTile = true;
        } else
          leftDiagonals++;
      }
    }

    curRow++;

    if (oddCol) {  // if currently in odd position
      curCol++;
      oddCol = false;
    } else
      oddCol = true;

  }  // while

  if (!foundOtherTile) leftDiagonals++;

  return !hasSameTile && allMatch;
}

bool Board::hasValidRightDiagonalTiles(Tile tile, char row, int col) {
  rightDiagonals = 0;

  bool hasSameTile = false, foundOtherTile = false, colorMatch = false,
       shapeMatch = false, allMatch = true;

  // ================== validate top right ==========================
  int curRow = row - 'A';
  int curCol = translateCol(col);
  bool oddCol;

  if (col % 2 != 0) {
    oddCol = true;
  } else
    oddCol = false;

  std::vector<int> match_adjacents = matchAdjacentTiles(tile, curRow, curCol);

  if (match_adjacents[2] == 0) {  // found a color match
    colorMatch = true;

    // std::cout << "found color match, curr shapeMatch =" << shapeMatch
    //           << "\tcolorMatch =" << colorMatch << '\n';

  } else if (match_adjacents[2] == 1) {  // found a shape match
    shapeMatch = true;

    // std::cout << "found shape match, curr shapeMatch =" << shapeMatch
    //           << "\tcolorMatch =" << colorMatch << '\n';
  }

  while (allMatch && !hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      // std::cout << "curRow = " << curRow << "\tcurCol = " << curCol <<
      // "\t\t";

      match_adjacents =
          matchAdjacentTiles(getTile(curRow, curCol), curRow, curCol);

      if (match_adjacents[2] == 0) {  // found a color match

        colorMatch = true;
        if (shapeMatch) allMatch = false;

        // std::cout << "found color match, curr shapeMatch =" << shapeMatch
        //           << "\tcolorMatch =" << colorMatch << '\n';

      } else if (match_adjacents[2] == 1) {  // found a shape match
        shapeMatch = true;
        if (colorMatch) allMatch = false;

        // std::cout << "found shape match, curr shapeMatch =" << shapeMatch
        //           << "\tcolorMatch =" << colorMatch << '\n';
      }

      if (curRow != row - 'A' || curCol != translateCol(col)) {
        foundOtherTile = true;

        if (grid[curRow][curCol].equals(tile)) {
          hasSameTile = true;
        } else
          rightDiagonals++;
      }
    }

    curRow--;

    if (oddCol) {
      curCol++;        // if currently in odd position
      oddCol = false;  // next position is an even position
    } else
      oddCol = true;

  }  // while

  // ================== validate bottom left ==========================
  curRow = row - 'A';
  curCol = translateCol(col);

  if (col % 2 == 0) {
    oddCol = false;
  } else
    oddCol = true;

  match_adjacents = matchAdjacentTiles(tile, curRow, curCol);

  if (match_adjacents[3] == 0) {  // found a color match
    colorMatch = true;

    // std::cout << "found color match, curr shapeMatch =" << shapeMatch
    //           << "\tcolorMatch =" << colorMatch << '\n';

  } else if (match_adjacents[3] == 1) {  // found a shape match
    shapeMatch = true;

    // std::cout << "found shape match, curr shapeMatch =" << shapeMatch
    //           << "\tcolorMatch =" << colorMatch << '\n';
  }

  while (allMatch && !hasSameTile && isInBounds(curRow, curCol)) {
    if (isOccupied(curRow, curCol)) {
      std::cout << "curRow = " << curRow << "\tcurCol = " << curCol << "\t\t";

      match_adjacents =
          matchAdjacentTiles(getTile(curRow, curCol), curRow, curCol);

      if (match_adjacents[3] == 0) {  // found a color match

        colorMatch = true;
        if (shapeMatch) allMatch = false;

        // std::cout << "found color match, curr shapeMatch =" << shapeMatch
        //           << "\tcolorMatch =" << colorMatch << '\n';

      } else if (match_adjacents[3] == 1) {  // found a shape match

        shapeMatch = true;
        if (colorMatch) allMatch = false;

        // std::cout << "found shape match, curr shapeMatch =" << shapeMatch
        //           << "\tcolorMatch =" << colorMatch << '\n';
      }

      if (curRow != row - 'A' || curCol != translateCol(col)) {
        foundOtherTile = true;

        if (grid[curRow][curCol].equals(tile)) {
          hasSameTile = true;
        } else
          rightDiagonals++;
      }
    }

    curRow++;

    if (!oddCol) {  // if currently in even position
      curCol--;
      oddCol = true;
    } else  // next position is an odd position
      oddCol = false;

  }  // while

  if (!foundOtherTile) rightDiagonals = 0;

  return !hasSameTile && allMatch;
}

void Board::resize() {
  if (getRows() < 26) {
    grid.resize(getRows() + 2);

    for (int i = 0; i < getRows(); i++) {
      grid[i].resize(getRows() / 2);
    }

    adjustCols(getRows());
  }
}

bool Board::addTile(Tile tile, char row, int col, int turn) {
  bool valid = true;
  int row_pos = row - 'A';
  int col_pos = translateCol(col);

  if (turn == 0)
    grid.at(row_pos).at(col_pos) = tile;

  else {
    if (hasValidAdjacentTiles(matchAdjacentTiles(tile, row_pos, col_pos)) &&
        hasValidLeftDiagonalTiles(tile, row, col) &&
        hasValidRightDiagonalTiles(tile, row, col)) {
      grid.at(row_pos).at(col_pos) = tile;

      // expand the board when user places a tile at the last column
      if (col_pos == getCols(row_pos) - 1) {
        resize();
      }
    } else
      valid = false;
  }

  return valid;
}

int Board::getLeftDiagonalTiles() { return leftDiagonals; }

int Board::getRightDiagonalTiles() { return rightDiagonals; }

Tile Board::getTile(int row, int col) { return grid[row][col]; }

bool Board::addTileFromSave(Tile tile, char row, int col) {
  bool valid = true;
  int row_pos = row - 'A';
  int col_pos = translateCol(col);
  grid.at(row_pos).at(col_pos) = tile;
  return valid;
}

void Board::displayBoard(bool saveFile) {
  char rowLetter = 'A';

  for (unsigned int i = 0; i < grid[1].size() * 2; i++) {
    if (i % 2 == 0) {
      std::cout << std::setw(5) << i;
    }
  }

  std::cout << "\n  ";
  for (int i = 0; i < getPrintedBoardWidth(grid[1].size() * 2); i++) {
    std::cout << '-';
  }
  std::cout << "\n";
  for (unsigned int i = 0; i < grid.size(); i++) {
    std::cout << rowLetter << " ";
    for (unsigned int j = 0; j < grid[i].size(); j++) {
      if (i % 2 == 0) {
        std::cout << "| ";
        if (saveFile)
          std::cout << grid[i][j].noColorString();
        else
          std::cout << grid[i][j].toString();
        std::cout << " ";
      } else if (i % 2 != 0) {
        if (j == 0) {
          std::cout << "   | ";
          if (saveFile)
            std::cout << grid[i][j].noColorString();
          else
            std::cout << grid[i][j].toString();
          std::cout << " ";
        } else {
          std::cout << "| ";
          if (saveFile)
            std::cout << grid[i][j].noColorString();
          else
            std::cout << grid[i][j].toString();
          std::cout << " ";
        }
      }
      if (j == grid[i].size() - 1) {
        std::cout << "|\n";
      }
    }
    rowLetter += 1;
  }
  std::cout << "  ";
  for (int i = 0; i < getPrintedBoardWidth(grid[1].size() * 2); i++) {
    std::cout << '-';
  }
  std::cout << "\n   ";
  for (unsigned int i = 0; i < grid[1].size() * 2; i++) {
    if (i % 2 != 0) {
      std::cout << std::setw(5) << i;
    }
  }

  std::cout << "\n";
}

int Board::getPrintedBoardWidth(int regularWidth) {
  return (regularWidth * 2) + (regularWidth / 2) + BOARDFRAME;
}
