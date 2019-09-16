
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
  Node* head;
  Node* tail;
  size_t list_size;

 public:
  LinkedList();
  ~LinkedList();

  int size();
  void clear();
  bool contains(Tile* tile);
  Tile* getFront();  // return tile at the head

  void addTile(Tile* tile);     // add tile to the end of the list
  void deleteTile(Tile* tile);  // remove specific tile from the list
  void deleteFront();

  void displayContents();
};

#endif  // ASSIGN2_LINKEDLIST_H
