
#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H
#define SIZE 6

#include "Board.h"
#include "Player.h"

class Game {
  Board board;
  Player playerOne;
  Player playerTwo;
  LinkedList* tileBag;
  char arr_color[SIZE];
  int arr_shape[SIZE];

  void clear();
  void addPlayer(Player player);
  bool placeTile(std::string tileInput, std::string locationInput,
                 Player* currentPlayer);
  void computePoints(Player player);
  void takeTurn(Player player);
  bool isFinished();
  bool isTileValid(char* c_tile);
  bool handleCommand(Player* currentPlayer);
  Tile drawTileFromBag();
  Player* getWinningPlayer();

 public:
  Game(std::string playerOneName, std::string playerTwoName);
  ~Game();
  void run();
};

#endif  // ASSIGN2_GAME_H
