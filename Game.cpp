#include "Game.h"
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <sstream>

#define PCOMMANDSIZE 4
#define RCOMMANDSIZE 2
#define PLAYER_HAND_SIZE 6
#define QWIRKLE_COUNT 6

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

  // tileBag->shuffle();

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

  delete playerOneHand;
  delete playerTwoHand;
}

Game::~Game() { clear(); }

void Game::clear() { delete tileBag; }

void Game::run() {
  Player* currentPlayer = &playerOne;
  int turn = 0;

  while (!isFinished()) {
    if (turn % 2 == 0)
      currentPlayer = &playerOne;
    else if (turn % 2 != 0)
      currentPlayer = &playerTwo;

    // for now
    // std::cout << "tile bag is: ";
    // tileBag->displayContents();
    // std::cout << "\n";

    std::cout << '\n' << currentPlayer->getName() << ", it's your turn\n\n";
    std::cout << "Score for " << playerOne.getName() << ": "
              << playerOne.getPoints() << '\n';
    std::cout << "Score for " << playerTwo.getName() << ": "
              << playerTwo.getPoints() << '\n';

    board.displayBoard();

    std::cout << "\nYour hand is\n";
    currentPlayer->getHand()->displayContents();

    if (handleCommand(currentPlayer, turn)) turn++;
  }

  std::cout << "Game over\n"
            << "Score for " << playerOne.getName() << ": "
            << playerOne.getPoints() << "\n"
            << "Score for " << playerTwo.getName() << ": "
            << playerTwo.getPoints() << "\n"
            << "Player " << getWinningPlayer()->getName() << " won!\n";

  // quit & print goodbye if user types ctrl+d
}

bool Game::isFinished() {
  return (tileBag->getSize() == 0) && (playerOne.getHand()->getSize() == 0 ||
                                       playerTwo.getHand()->getSize() == 0);
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

bool Game::handleCommand(Player* currentPlayer, int turn) {
  bool validCommand;
  std::string userInput;

  do {
    validCommand = true;
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
        if (!placeTile(tokens[1], tokens[3], currentPlayer, turn)) {
          validCommand = false;
        }
      } else {  // if the 2nd and 4th tokens don't have a length of two
        validCommand = false;
        std::cout
            << "\nCommand not recognized. Try 'place <tile> at <location>' "
               "or 'replace <tile>'\n";
      }
    }

    else if (tokens.size() == RCOMMANDSIZE && !tokens[0].compare("replace")) {
      // replace tile method
      if (tokens[1].length() == 2) {
        if (isCodeValid(tokens[1])) {
          Tile toReplace(static_cast<Colour>(tokens[1].at(0)),
                         static_cast<Shape>(tokens[1].at(1) - '0'));

          if (currentPlayer->getHand()->contains(toReplace)) {
            currentPlayer->getHand()->replaceTile(toReplace, drawTileFromBag());
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
        std::cout << "\nThis tile does not exist. Please try again\n";
      }
    }

    else {
      validCommand = false;
      std::cout << "\nCommand not recognized. Try 'place <tile> at <location>' "
                   "or 'replace <tile>'\n";  // todo : UPDATE ERROR MESSAGES IN
                                             // UNIT TESTS
    }
  } while (std::cin.good() && !std::cin.eof() && !validCommand);

  return validCommand;
}

bool Game::placeTile(std::string tileInput, std::string locationInput,
                     Player* currentPlayer, int turn) {
  bool valid = true;
  char row = locationInput.at(0);
  int col = locationInput.at(1) - '0';

  if (isCodeValid(tileInput)) {
    if (board.isValidPosition(row, col) && board.isInBounds(row, col)) {
      if (!board.isOccupied(row, col)) {
        Tile tile(static_cast<Colour>(tileInput.at(0)),
                  static_cast<Shape>(tileInput.at(1) - '0'));

        if (currentPlayer->getHand()->contains(tile)) {
          if (!board.hasSameTileInLines(tile, row, col)) {
            if (board.addTile(tile, row, col, turn)) {
              computePoints(currentPlayer, tile, row, col);
              currentPlayer->getHand()->deleteTile(tile);
              currentPlayer->getHand()->addTile(drawTileFromBag());
            } else {
              valid = false;
              std::cout
                  << "\nThat tile cannot be placed there. Please try again\n";
            }
          }  // hasSameTileInLines
          else {
            valid = false;
            std::cout << "\nThe same tile already exists in the line. Please "
                         "try again\n";
          }
        }  // contains
        else {
          valid = false;
          std::cout << "\nThat tile is not in your hand. Please try again\n";
        }
      }  // isOccupied
      else {
        valid = false;
        std::cout << "\nThat spot is already taken. Please try again\n";
      }
    }  // isValidPosition
    else {
      valid = false;
      std::cout << "\nThat spot does not exist. Please try again\n";
    }
  }  // isCodeValid
  else {
    valid = false;
    std::cout << "That tile does not exist. Please try again\n";
  }

  return valid;
}

void Game::computePoints(Player* currentPlayer, Tile tile, char row, int col) {
  int left = board.countLeftDiagonalTiles(tile, row, col, false);
  int right = board.countRightDiagonalTiles(tile, row, col, false);
  bool qwirkle = false;

  if (left == QWIRKLE_COUNT) {
    left += QWIRKLE_COUNT;
    qwirkle = true;
  }

  if (right == QWIRKLE_COUNT) {
    right += QWIRKLE_COUNT;
    qwirkle = true;
  }

  if (qwirkle) std::cout << "\nQWIRKLE!!!\n";

  currentPlayer->setPoints(currentPlayer->getPoints() + left + right);
}

Tile Game::drawTileFromBag() {
  Tile tile = tileBag->getFront();

  // delete from tileBag
  tileBag->deleteFront();

  return tile;
}

Board Game::getBoard() { return board; }

void Game::setTileBag(LinkedList* tileBag) {
  this->tileBag = new LinkedList(*tileBag);
}