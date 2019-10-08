
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
  Tile tile;
  Node* next;

 public:
  Node(Tile tile, Node* next);
  Node(const Node& other);
  void setNext(Node* next);
  Tile getTile();
  Node* getNext();
};

#endif  // ASSIGN2_NODE_H
