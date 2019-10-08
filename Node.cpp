
#include "Node.h"

Node::Node(Tile tile, Node* next) : tile(tile), next(next) {}

Node::Node(const Node& other) : tile(other.tile), next(other.next) {}

void Node::setNext(Node* next) { this->next = next; }

Node* Node::getNext() { return next; }

Tile Node::getTile() { return tile; }