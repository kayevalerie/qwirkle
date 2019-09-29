
#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include "Board.h"
#include "Player.h"

class Game {
  Board board;
  Player playerOne;
  Player playerTwo;
  LinkedList* tileBag;

  void clear();
  void createTileBag();
  void addPlayer(Player player);
  void placeTile(Player player,
                 Tile tile);  // (call board addTile)
  void computePoints(Player player);
  void takeTurn(Player player);

 public:
  Game();
  ~Game();
  void startGame();
  bool gameEnd();
  Player getPlayerOne();
  Player getPlayerTwo();
  Board getBoard();
};

#endif  // ASSIGN2_GAME_H
