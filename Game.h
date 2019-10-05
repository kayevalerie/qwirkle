
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
  void addPlayer(Player player);
  void handleCommand(Player* currentPlayer);
  void placeTile(std::string tileInput, std::string locationInput,
                 Player* currentPlayer);
  Tile drawTileFromBag();
  void computePoints(Player player);  // todo
  bool isFinished();
  Player* getWinningPlayer();

 public:
  Game(std::string playerOneName, std::string playerTwoName);
  ~Game();
  void run();
};

#endif  // ASSIGN2_GAME_H
