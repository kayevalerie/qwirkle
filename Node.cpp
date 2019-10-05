
#include "Node.h"
Node::Node() {}

Node::Node(Tile tile, Node* next) : tile(tile), next(next) {}

Node::Node(const Node& other) : tile(other.tile), next(other.next) {}

Tile Node::getTile() { return tile; }