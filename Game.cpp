#include "Game.h"
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

#define PCOMMANDSIZE 4
#define RCOMMANDSIZE 2

Game::Game(std::string playerOneName, std::string playerTwoName)
    : playerOne(Player(playerOneName)),
      playerTwo(Player(playerTwoName)),
      board(Board()) {
  arr_color[0] = 'R';
  arr_color[1] = 'O';
  arr_color[2] = 'Y';
  arr_color[3] = 'G';
  arr_color[4] = 'P';
  arr_color[5] = 'B';
  arr_shape[0] = 1;
  arr_shape[1] = 2;
  arr_shape[2] = 3;
  arr_shape[3] = 4;
  arr_shape[4] = 5;
  arr_shape[5] = 6;

  tileBag = new LinkedList();

  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      Tile* newTile = new Tile(arr_color[i], arr_shape[j]);

      tileBag->addTile(newTile);
      tileBag->addTile(newTile);
    }
  }

  tileBag->shuffle();

  LinkedList* playerOneHand = new LinkedList();
  LinkedList* playerTwoHand = new LinkedList();

  for (int i = 0; i < 6; ++i) {
    playerOneHand->addTile(tileBag->getFront());
    tileBag->deleteFront();
    playerTwoHand->addTile(tileBag->getFront());
    tileBag->deleteFront();
  }

  playerOne.setHand(playerOneHand);
  playerTwo.setHand(playerTwoHand);

  // tentative
  // delete[] playerOneHand;
  // delete[] playerTwoHand;
}

Game::~Game() { clear(); }

void Game::run() {
  Player* currentPlayer = &playerOne;
  int count = 0;
  std::cout << "Let's play\n";

  while (!isFinished()) {
    if (!count % 2)
      currentPlayer = &playerOne;
    else if (count % 2)
      currentPlayer = &playerTwo;

    std::cout << currentPlayer->getName() << ", it's your turn\n";
    std::cout << "Score for " << playerOne.getName() << ": "
              << playerOne.getPoints();
    std::cout << "Score for " << playerTwo.getName() << ": "
              << playerTwo.getPoints();
    board.displayBoard();

    std::cout << "Your hand is\n";
    currentPlayer->getHand()->displayContents();
    std::cout << "> ";

    handleCommand(currentPlayer);
    // handle command
    // add tile to board(draw tile, update score)/replace tile
    count++;
  }

  std::cout << "Game over\n"
            << "Score for " << playerOne.getName() << ": "
            << playerOne.getPoints() << "\n"
            << "Score for " << playerTwo.getName() << ": "
            << playerTwo.getPoints() << "\n"
            << "Player " << getWinningPlayer()->getName() << " won!\n";
}

bool Game::isFinished() {
  return ((tileBag->getSize() == 0) && ((playerOne.getHand()->getSize() == 0) ||
                                        (playerTwo.getHand()->getSize() == 0)));
}

Player* Game::getWinningPlayer() {
  Player* winningPlayer = nullptr;

  if (playerOne.getPoints() > playerTwo.getPoints()) {
    winningPlayer = &playerOne;
  } else if (playerOne.getPoints() < playerTwo.getPoints()) {
    winningPlayer = &playerTwo;
  }
  return winningPlayer;
}

void Game::handleCommand(Player* currentPlayer) {
  std::string userInput = "";
  while (std::cin.peek() == '\n') {
    std::cout << "Command not recognized. Try 'place X at Y' or 'replace X'\n";
    std::cin.ignore();
  }

  std::getline(std::cin, userInput);
  std::stringstream ss(userInput);
  std::string intermediate;
  std::vector<std::string> tokens;

  while (getline(std::cin, intermediate, ' ')) {
    tokens.push_back(intermediate);
  }

  if (tokens.size() == PCOMMANDSIZE && !tokens[0].compare("place") &&
      !tokens[2].compare("at")) {
    placeTile(tokens[1], tokens[3], currentPlayer);
  } else if (tokens.size() == RCOMMANDSIZE && !tokens[0].compare("replace")) {
    // replace tile method
  }
}

void Game::placeTile(std::string tile, std::string index,
                     Player* currentPlayer) {
  int n = tile.length();
  if (n == 2) {
      char c_tile[2];
      strcpy(c_tile, tile.c_str());
  }
  int k = index.length();
  if (k == 2) {
      char c_index[2];
      strcpy(c_index, index.c_str());
  }
  char row = c_index[0];
  int col = c_index[1] - '0';

  bool tileValid = isTileValid(c_tile);
  bool indexValid = board.isValidPosition(row, col);
  
  Tile tile(c_tile[0], c_tile[1]);                    
  bool hasTile = currentPlayer->getHand->contains(&tile);
  
  if (tileValid && indexValid) {
    board.addTile(&tile, row, col);
  }

  // check if the user has that tile in their hand
  // check if it's a valid index
  // check if that spot is not taken already
  // check if the user can put that specific tile there(refer to qwirkle rules)
  // add that tile to the board vector
  // delete that tile from the user's hand
  // draw another tile from the tile bag and add it to the user's hand
  // calculate the score and update the user's score
}

bool Game::isTileValid(char* c_tile) {
  bool colorValid = std::find(std::begin(arr_color), std::end(arr_color),
                               c_tile[0] - '0') != std::end(arr_color);

  bool shapeValid = std::find(std::begin(arr_shape), std::end(arr_shape),
                               c_tile[1] - '0') != std::end(arr_shape);

  return colorValid && shapeValid;
}
