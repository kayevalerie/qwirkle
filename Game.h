
#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include "Board.h"
#include "LinkedList.h"
#include "Player.h"

#include <string>

class Game {
  Player playerOne;
  Player playerTwo;
  Board board;
  LinkedList* tileBag;

  void clear();
  bool handleCommand(Player* currentPlayer, int turn);
  bool placeTile(std::string tileInput, std::string locationInput,
                 Player* currentPlayer, int turn);
  Tile drawTileFromBag();
  bool isFinished();
  void computePoints(Player* currentPlayer, Tile tile, char row, int col);
  Player* getWinningPlayer();

 public:
  Game(std::string playerOneName, std::string playerTwoName);
  Game();
  ~Game();
  void run();
  void setPlayerOne(Player& newPlayerOne);
  void setPlayerTwo(Player& newPlayerTwo);
  void setTileBag(LinkedList* newTileBag);
  Board getBoard();
};

#endif  // ASSIGN2_GAME_H
