#include "Game.h"
#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Helper.h"

#define PCOMMANDSIZE 4
#define RCOMMANDSIZE 2
#define PLAYER_HAND_SIZE 6
#define QWIRKLE_COUNT 6

Game::Game() : board(Board()), tileBag(nullptr) {}

Game::Game(std::string playerOneName, std::string playerTwoName)
    : playerOne(Player(playerOneName)),
      playerTwo(Player(playerTwoName)),
      board(Board()),
      tileBag(new LinkedList()) {
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

  delete playerOneHand;
  delete playerTwoHand;
}

Game::~Game() { clear(); }

void Game::clear() { delete tileBag; }

void Game::setPlayerOne(Player& newPlayerOne) { playerOne = newPlayerOne; }

void Game::setPlayerTwo(Player& newPlayerTwo) { playerTwo = newPlayerTwo; }

void Game::setCurrentPlayer(Player& player) { currentPlayer = &player; }
void Game::setTileBag(LinkedList* newTileBag) {
  tileBag = new LinkedList(*newTileBag);
}

void Game::run(int turn) {
  Player* currentPlayer;

  do {
    if (turn % 2 == 0)
      currentPlayer = &playerOne;
    else
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

    board.displayBoard(false);

    std::cout << "\nYour hand is\n";
    currentPlayer->getHand()->displayContents(false);
    if (handleCommand(currentPlayer)) turn++;

  } while (!isFinished());

  std::cout << "Game over\n"
            << "Score for " << playerOne.getName() << ": "
            << playerOne.getPoints() << "\n"
            << "Score for " << playerTwo.getName() << ": "
            << playerTwo.getPoints() << "\n";

  if (getWinningPlayer())
    std::cout << "Player " << getWinningPlayer()->getName() << " won!\n";
  else
    std::cout << "It's a draw!\n";
}

bool Game::isFinished() {
  return (tileBag->getSize() == 0 && (playerOne.getHand()->getSize() == 0 ||
                                      playerTwo.getHand()->getSize() == 0));
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
  bool validCommand, quit = false, hint;
  std::string userInput;

  do {
    validCommand = true;
    hint = false;

    std::cout << "> ";

    std::getline(std::cin, userInput);

    std::stringstream ss(userInput);
    std::string intermediate;
    std::vector<std::string> tokens;

    while (getline(ss, intermediate, ' ')) {
      if (!intermediate.empty()) tokens.push_back(intermediate);
    }

    if (std::cin.eof() || (tokens.size() == 1 && tokens[0] == "q")) {
      quit = true;
      std::cout << "\nGoodbye!\n";
      std::exit(EXIT_FAILURE);
    }

    else if (tokens.size() == 1 && tokens[0] == "s") {
      std::string filename;
      bool validFilename = true;

      do {
        std::cout << "\nInput filename of savefile\n> ";

        std::getline(std::cin, filename);

        char* cstr = new char[filename.length() + 1];
        std::strcpy(cstr, filename.c_str());
        FILE* fp = fopen(cstr, "wx");

        if (fp) {
          fclose(fp);
          validFilename = true;
        } else {
          validFilename = false;
          std::cout << "\nCan't save to the file. Are you trying to overwrite "
                       "an existing file?\n";
        }
      } while (!validFilename);

      saveGame(filename, currentPlayer);
      validCommand = false;
    }

    // place tile action
    else if (tokens.size() == PCOMMANDSIZE && !tokens[0].compare("place") &&
             !tokens[2].compare("at")) {
      if (tokens[1].length() == 2 && tokens[3].length() >= 2) {
        if (Helper::isASCII(tokens[3].substr(0, 1)) &&
            Helper::isNumber(tokens[3].substr(1, tokens[3].length()))) {
          if (!placeTile(tokens[1], tokens[3], currentPlayer)) {
            validCommand = false;
            hint = false;
          }
        } else {
          validCommand = false;
          hint = true;
        }
      } else {
        validCommand = false;
        hint = true;
      }

    }

    // replace tile action
    else if (tokens.size() == RCOMMANDSIZE && !tokens[0].compare("replace")) {
      if (tokens[1].length() == 2) {
        if (isCodeValid(tokens[1])) {
          Tile toReplace(static_cast<Colour>(tokens[1].at(0)),
                         static_cast<Shape>(tokens[1].at(1) - '0'));

          // check if the current tile is in the player's hand
          if (currentPlayer->getHand()->contains(toReplace)) {
            // draw a tile from the tilebag and switch it with the tile the
            // player wants to replace
            currentPlayer->getHand()->replaceTile(toReplace, drawTileFromBag());
          } else {
            validCommand = false;
            std::cout << "\nThat tile is not in your hand. Please try again\n";
          }
        } else {
          validCommand = false;
          hint = true;
        }
      } else {
        validCommand = false;
        hint = true;
      }
    } else {
      validCommand = false;
      hint = true;
    }

    if (hint)
      std::cout << "\nCommand not recognized. Try 'place <tile> at <location>' "
                   "or 'replace <tile>'\n";  // todo : UPDATE ERROR MESSAGES IN
                                             // UNIT TESTS
  } while (!quit && !validCommand);

  return !quit;
}

bool Game::placeTile(std::string tileInput, std::string locationInput,
                     Player* currentPlayer) {
  bool valid = true;
  char row = locationInput.at(0);
  int col = std::stoi(locationInput.substr(1, locationInput.length()));

  if (isCodeValid(tileInput)) {
    if (board.isValidPosition(row, col) && board.isInBounds(row, col)) {
      if (!board.isOccupied(row, col)) {
        Tile tile(static_cast<Colour>(tileInput.at(0)),
                  static_cast<Shape>(tileInput.at(1) - '0'));

        if (currentPlayer->getHand()->contains(tile)) {
          if (board.addTile(tile, row, col)) {
            updatePoints(currentPlayer);
            currentPlayer->getHand()->deleteTile(tile);
            currentPlayer->getHand()->addTile(drawTileFromBag());
          } else {
            valid = false;
            std::cout
                << "\nThat tile cannot be placed there. Please try again\n";
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

void Game::updatePoints(Player* currentPlayer) {
  int points = board.getLeftDiagonalTiles() + board.getRightDiagonalTiles();

  // if a tile is placed for the first time
  if (board.getFilledSpaces() == 1) points++;  // add one point

  bool qwirkle = false;

  if (board.getLeftDiagonalTiles() == QWIRKLE_COUNT) {
    points += QWIRKLE_COUNT;
    qwirkle = true;
  }

  if (board.getRightDiagonalTiles() == QWIRKLE_COUNT) {
    points += QWIRKLE_COUNT;
    qwirkle = true;
  }

  if (qwirkle) std::cout << "\nQWIRKLE!!!\n";

  currentPlayer->setPoints(currentPlayer->getPoints() + points);
}

Tile Game::drawTileFromBag() {
  Tile tile = tileBag->getFront();

  // delete from tileBag
  tileBag->deleteFront();

  return tile;
}

void Game::saveGame(std::string filename, Player* currentPlayer) {
  std::ofstream fw;
  fw.open(filename);

  fw << playerOne.getName() << "\n";
  fw << playerOne.getPoints() << "\n";
  std::streambuf* oldbuf = std::cout.rdbuf();
  std::cout.rdbuf(fw.rdbuf());
  playerOne.getHand()->displayContents(
      true);                // contents to cout will be written to file
  std::cout.rdbuf(oldbuf);  // reset back to standard input
  // SOURCE https://stackoverflow.com/a/10151286  (to include as reference)

  fw << playerTwo.getName() << "\n";
  fw << playerTwo.getPoints() << "\n";
  oldbuf = std::cout.rdbuf();
  std::cout.rdbuf(fw.rdbuf());
  playerTwo.getHand()->displayContents(true);

  board.displayBoard(true);

  tileBag->displayContents(true);

  std::cout.rdbuf(oldbuf);

  fw << currentPlayer->getName();

  fw.close();

  std::cout << "\nGame successfully saved\n";
}

Board* Game::getBoard() { return &board; }
