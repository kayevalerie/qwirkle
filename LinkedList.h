
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
  void replaceTile(Tile* tile, Tile* newTile);  // remove specific tile from the
                                                // list and replace a new one
  void displayContents();
};

#endif  // ASSIGN2_LINKEDLIST_H
