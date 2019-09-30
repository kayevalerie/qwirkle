
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
  Player(std::string name, int points, LinkedList* tiles);
  Player(std::string name, int points);
  ~Player();
  void setPoints(int points);
  int getPoints();
  void drawTile(LinkedList* tileBag);
  std::string getName();
  LinkedList* getHand();
  void setHand(LinkedList* tiles);
};

#endif  // ASSIGN2_PLAYER_H
