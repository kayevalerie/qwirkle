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
    std::cout << "\n\n";

    if (handleCommand(currentPlayer)) turn++;
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

bool Game::handleCommand(Player* currentPlayer) {
  bool validCommand = true;
  bool action = false;

  std::string userInput;

  do {
    std::cout << "> ";
    std::getline(std::cin, userInput);

    std::stringstream ss(userInput);
    std::string intermediate;
    std::vector<std::string> tokens;

    while (getline(ss, intermediate, ' ')) {
      if (!intermediate.empty()) tokens.push_back(intermediate);
    }

    if (tokens.size() == PCOMMANDSIZE && !tokens[0].compare("place") &&
        !tokens[2].compare("at")) {
      if (tokens[1].length() == 2 && tokens[3].length() == 2) {
        if (placeTile(tokens[1], tokens[3], currentPlayer)) {
          action = true;
        } else {
          validCommand = false;
          std::cout
              << "\nCommand not recognized. Try 'place <tile> at <location>' "
                 "or 'replace <tile>'\n";
        }
      } else  // if the 2nd and 4th tokens don't have a length of two
        validCommand = false;
    }

    else if (tokens.size() == RCOMMANDSIZE && !tokens[0].compare("replace")) {
      // replace tile method
      if (tokens[1].length() == 2) {
        if (isCodeValid(tokens[1])) {
          Tile toReplace(static_cast<Colour>(tokens[1].at(0)),
                         static_cast<Shape>(tokens[1].at(1) - '0'));

          if (currentPlayer->getHand()->contains(toReplace)) {
            currentPlayer->getHand()->replaceTile(toReplace, drawTileFromBag());
            action = true;
            // std::cout << "tile replaced, player hand: ";
            // currentPlayer->getHand()->displayContents();
          } else {
            validCommand = false;
            std::cout << "\nThis tile is not in your hand. Please try again\n";
          }
        } else {
          validCommand = false;
          std::cout << "\nThis tile does not exist. Please try again\n";
        }
      } else {
        validCommand = false;
        std::cout
            << "\nCommand not recognized. Try 'place <tile> at <location>' "
               "or 'replace <tile>'\n";
      }
    }

    else {
      validCommand = false;
      std::cout << "\nCommand not recognized. Try 'place <tile> at <location>' "
                   "or 'replace <tile>'\n";  // todo : UPDATE ERROR MESSAGES IN
                                             // UNIT TESTS
    }
  } while (std::cin.good() && !std::cin.eof() && (!validCommand || !action));

  return validCommand;
}

bool Game::placeTile(std::string tileInput, std::string locationInput,
                     Player* currentPlayer, int turn) {
  bool valid = true;

  char row = tileInput.at(0);
  int col = tileInput.at(1) - '0';

  if (isCodeValid(tileInput)) {
    std::cout << "row = " << row << " col = " << col;
    if (board.isValidPosition(row, col)) {
      Tile tile(static_cast<Colour>(tileInput.at(0)),
                static_cast<Shape>(tileInput.at(1) - '0'));

      if (currentPlayer->getHand()->contains(tile)) {
        if (board.addTile(tile, row, col)) {
          currentPlayer->getHand()->deleteTile(tile);
          currentPlayer->getHand()->addTile(drawTileFromBag());
        } else {
          valid = false;
          std::cout << "\nThat tile cannot be placed there. Please try again\n";
        }
      } else {
        valid = false;
        std::cout << "\nThat tile is not in your hand. Please try again\n";
      }
    } else {
      valid = false;
      // do we need to check for out of bounds?
      std::cout << "\nThat spot does not exist. Please try again\n";
    }
  } else {
    valid = false;
    std::cout << "That tile does not exist. Please try again\n";
  }

  return valid;
}

Tile Game::drawTileFromBag() {
  Tile tile = tileBag->getFront();

  // delete from tileBag
  tileBag->deleteFront();

  return tile;
}
