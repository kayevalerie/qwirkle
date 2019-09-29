
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include <iostream>
#include "Node.h"

class LinkedList {
  Node* head;
  Node* tail;
  size_t list_size;
  void clear();
  Tile* get(unsigned int i);
  void deleteAt(unsigned int i);

 public:
  LinkedList();
  LinkedList(const LinkedList& src);
  ~LinkedList();
  int getSize();
  Tile* getFront();  // return tile at the head
  LinkedList* shuffle();
  bool contains(Tile* tile);
  void addTile(Tile* tile);  // add tile to the end of the list
  void deleteFront();
  void replaceTile(Tile* tile, Tile* newTile);  // remove specific tile from the
                                                // list and replace a new one
  void displayContents();
};

#endif  // ASSIGN2_LINKEDLIST_H
