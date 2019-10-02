
#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H
#define SIZE 6

#include "Board.h"
#include "Player.h"

class Game {
  Board* board;
  Player* playerOne;
  Player* playerTwo;
  LinkedList* tileBag;
  char arr_color[SIZE];
  int arr_shape[SIZE];

  void clear();
  void addPlayer(Player player);
  void placeTile(Player player,
                 Tile tile);  // (call board addTile)
  void computePoints(Player player);
  void takeTurn(Player player);
  bool isFinished();
  Player* getWinningPlayer();

 public:
  Game();
  Game(std::string playerOneName, std::string playerTwoName);
  ~Game();
  void run();
  Player getPlayerOne();
  Player getPlayerTwo();
  Board getBoard();
};

#endif  // ASSIGN2_GAME_H
