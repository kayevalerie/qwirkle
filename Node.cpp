
#include "Node.h"

Node::Node(Tile* tile, Node* next) : tile(tile), next(next) {}

Node::Node(Node& other) {
  // TODO
}

Tile* Node::getTile() { return tile; }