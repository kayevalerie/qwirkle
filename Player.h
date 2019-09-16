
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>
#include "LinkedList.h"

class Player {
  LinkedList* tiles;
  std::string name;
  int points;
  void clear();

 public:
  Player(std::string name, int points, std::string hand);
  ~Player();
  void clear();
  void setHand(std::string hand);
  void setPoints(int points);
  std::string getName();
  int getPoints();
  LinkedList* getTiles();
};

#endif  // ASSIGN2_PLAYER_H
