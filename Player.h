
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>
#include "LinkedList.h"

class Player {
  std::string name;
  int points;
  LinkedList* hand;
  void clear();

 public:
  Player(std::string name);
  Player(std::string name, int points, LinkedList* tiles);
  Player(const Player& toCopy);
  ~Player();
  std::string getName();
  void setPoints(int points);
  int getPoints();
  void setHand(LinkedList* tiles);
  LinkedList* getHand();
};

#endif  // ASSIGN2_PLAYER_H
