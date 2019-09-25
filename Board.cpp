#include <Board.h>
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

Tile Board::getTile(char row, int col) {
  int int_row = row - 'A';
  return grid[int_row][col];
}

void Board::displayBoard() {
 
    char rowLetter = 'A';
	for (int i=0; i<COLS; i++) {
		if (i%2 == 0) {
			std::cout<<setw(5)<<i;
		}
	}

	std::cout<<"\n  ";
	for (int i=0;i<getPrintedBoardWidth(COLS);i++) {
		std::cout<<'-';
	}
	std::cout<<"\n";
	for (int i=0; i< grid.size(); i++) {
		std::cout<<rowLetter<<" ";
		for (int j=0; j<grid[i].size(); j++) {
			if (i%2 == 0) {
				std::cout<<"| "<<grid[i][j].getColour()<< grid[i][j].getShape() <<" " ;
			}
			else if (i%2 != 0) {
				std::cout<<"   | "<<grid[i][j].getColour()<< grid[i][j].getShape() " ";
			}
			if (j == grid[i].size() - 1) {
				std::cout<< "|\n";
			}
		}
		rowLetter += 1;
	}
	std::cout<<"  ";
	for (int i=0;i<getPrintedBoardWidth(COLS);i++) {
		std::cout<<'-';
	}
	std::cout<< "\n   ";
	for (int i=0; i<COLS; i++) {
		if (i%2 != 0) {
			std::cout<<setw(5)<<i;
		}
	}

	std::cout<<"\n  ";
  
}

int Board::getPrintedBoardWidth(int regularWidth) {
	return (regularWidth*2) + (regularWidth/2) + BOARDFRAME);
}
