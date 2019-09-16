
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
  Tile* tile;

 public:
  Node(Tile* tile, Node* next);
  Node(Node& other);
  Node* next;
  Tile* getTile();
};

#endif  // ASSIGN2_NODE_H
