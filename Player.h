
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>
#include "LinkedList.h"

class Player {
  LinkedList* hand;
  std::string name;
  int points;
  void clear();

 public:
  Player(std::string name);
  Player(std::string name, int points, LinkedList* tiles);
  ~Player();
  std::string getName();
  void setPoints(int points);
  int getPoints();
  void setHand(LinkedList* tiles);
  LinkedList* getHand();
  void drawTile(LinkedList* tileBag);
};

#endif  // ASSIGN2_PLAYER_H
