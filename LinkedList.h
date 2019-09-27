
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include <iostream>
#include "Node.h"

class LinkedList {
  Node* head;
  Node* tail;
  size_t list_size;
  void clear();
  Tile getTile(int i);   // todo
  void deleteAt(int i);  // todo

 public:
  LinkedList();
  ~LinkedList();
  int getSize();
  Tile* getFront();  // return tile at the head
  void shuffle();
  bool contains(Tile* tile);
  void addTile(Tile* tile);  // add tile to the end of the list
  void deleteFront();
  void replaceTile(Tile* tile, Tile* newTile);  // remove specific tile from the
                                                // list and replace a new one
  void displayContents();
};

#endif  // ASSIGN2_LINKEDLIST_H
