#include "Game.h"
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <sstream>

#define PCOMMANDSIZE 4
#define RCOMMANDSIZE 2
#define PLAYER_HAND_SIZE 6

Game::Game(std::string playerOneName, std::string playerTwoName)
    : playerOne(Player(playerOneName)),
      playerTwo(Player(playerTwoName)),
      board(Board()) {
  tileBag = new LinkedList();

  for (int i = 0; i < PLAYER_HAND_SIZE; ++i) {
    for (int j = 0; j < PLAYER_HAND_SIZE; ++j) {
      Tile tile = Tile(colours.at(i), shapes.at(j));

      tileBag->addTile(tile);
      tileBag->addTile(tile);
    }
  }

  tileBag->shuffle();

  LinkedList* playerOneHand = new LinkedList();
  LinkedList* playerTwoHand = new LinkedList();

  for (int i = 0; i < PLAYER_HAND_SIZE; ++i) {
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

void Game::clear() {
  // todo
}

void Game::run() {
  Player* currentPlayer = &playerOne;
  int turn = 0;

  while (!isFinished()) {
    if (!turn % 2)
      currentPlayer = &playerOne;
    else if (turn % 2)
      currentPlayer = &playerTwo;

    std::cout << '\n' << currentPlayer->getName() << ", it's your turn\n";
    std::cout << "Score for " << playerOne.getName() << ": "
              << playerOne.getPoints() << '\n';
    std::cout << "Score for " << playerTwo.getName() << ": "
              << playerTwo.getPoints() << '\n';
    board.displayBoard();

    std::cout << "\nYour hand is\n";
    currentPlayer->getHand()->displayContents();
    std::cout << "> ";

    handleCommand(currentPlayer);
    // add tile to board(draw tile, update score)
    // replace tile

    turn++;
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
  // todo

  std::string userInput;

  while (std::cin.peek() == '\n') {
    std::cout << "Command not recognized. Try 'place X at Y' or 'replace X'\n";
    std::cin.ignore();
  }

  std::getline(std::cin, userInput);

  std::cout << userInput;

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

void Game::placeTile(std::string tileInput, std::string locationInput,
                     Player* currentPlayer) {
  // int n = tileInput.length();
  // char* c_tile = nullptr;

  // if (n == 2) {
  //   *c_tile = tileInput[2];
  //   strcpy(c_tile, tileInput.c_str());
  // }

  // n = locationInput.length();
  // char* c_index = nullptr;
  // if (n == 2) {
  //   *c_index = locationInput[2];
  //   strcpy(c_index, locationInput.c_str());
  // }

  // char row = c_index[0];
  // int col = c_index[1] - '0';

  char row = tileInput.at(0);
  int col = tileInput.at(1) - '0';

  if (isCodeValid(locationInput) && board.isValidPosition(row, col)) {
    Tile tile(static_cast<Colour>(locationInput.at(0)),
              static_cast<Shape>(locationInput.at(1) - '0'));
    bool hasTile = currentPlayer->getHand()->contains(tile);

    if (!hasTile) {
      board.addTile(tile, row, col);
      currentPlayer->getHand()->deleteTile(tile);
      currentPlayer->getHand()->addTile(drawTileFromBag());
    }
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

Tile Game::drawTileFromBag() {
  Tile tile = tileBag->getFront();

  // delete from tileBag
  tileBag->deleteFront();

  return tile;
}
