
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
  Tile tile;

 public:
  Node();  // to remove
  Node(Tile tile, Node* next);
  Node(const Node& other);
  Node* next;
  Tile getTile();
};

#endif  // ASSIGN2_NODE_H
