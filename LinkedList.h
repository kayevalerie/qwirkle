
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include <iostream>
#include "Node.h"

class LinkedList {
  Node* head;
  Node* tail;
  size_t list_size;  // remove this? (additional cost)

 public:
  LinkedList();
  ~LinkedList();
  void clear();
  int getSize();
  Tile* getFront();  // return tile at the head
  bool contains(Tile* tile);
  void addTile(Tile* tile);  // add tile to the end of the list
  void deleteFront();
  void deleteTile(Tile* tile);  // remove specific tile from the list
  void displayContents();
};

#endif  // ASSIGN2_LINKEDLIST_H
