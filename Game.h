
#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include "Board.h"
#include "LinkedList.h"
#include "Player.h"

#include <string>
#define NUM_PLAYERS 4

class Game {
  // std::array<Player, NUM_PLAYERS> players;
  Player playerOne;
  Player playerTwo;
  Board board;
  LinkedList* tileBag;
  Player* currentPlayer;

  void clear();
  bool handleCommand(Player* currentPlayer);
  bool placeTile(std::string tileInput, std::string locationInput,
                 Player* currentPlayer);
  void updatePoints(Player* currentPlayer);
  Tile drawTileFromBag();
  bool isFinished();
  Player* getWinningPlayer();
  void saveGame(std::string filename, Player* currentPlayer);

 public:
  Game(std::string playerOneName, std::string playerTwoName);
  // Game(std::string playerOneName, std::string playerTwoName, std::string
  // playerThreeName, std::string playerFourName);
  Game();
  ~Game();
  void run(int turn);
  void setPlayerOne(Player& newPlayerOne);
  void setPlayerTwo(Player& newPlayerTwo);
  void setTileBag(LinkedList* newTileBag);
  void setCurrentPlayer(Player& player);
  Board* getBoard();
};

#endif  // ASSIGN2_GAME_H
