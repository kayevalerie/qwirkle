
#include "Node.h"

Node::Node(Tile* tile, Node* next) : tile(tile), next(next) {}

Node::Node(const Node& other) : tile(other.tile), next(nullptr) {}

Tile* Node::getTile() { return tile; }