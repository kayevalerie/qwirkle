
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
  Tile* get(int i);

  void addFront(Tile* tile);
  void addBack(Tile* tile);

  bool contains(Tile* tile);
  void deleteFront();
  void deleteBack();

  void displayContents();
};

#endif  // ASSIGN2_LINKEDLIST_H
