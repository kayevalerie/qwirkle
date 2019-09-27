
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>
#include "LinkedList.h"

class Player {
  LinkedList* tiles;
  std::string name;
  int points;
  void clear();
  void setHand(std::string hand);

 public:
  Player(std::string name, int points, std::string hand);
  ~Player();
  void setPoints(int points);
  int getPoints();
  void drawTile(LinkedList* tileBag);
  std::string getName();
  LinkedList* getHand();
};

#endif  // ASSIGN2_PLAYER_H
