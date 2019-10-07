
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include "Tile.h"

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
  Tile getFront();  // return tile at the head
  void shuffle();
  bool contains(Tile tile);
  void addTile(Tile tile);  // add tile to the end of the list
  void deleteFront();
  void replaceTile(Tile tile,
                   Tile newTile);  // remove a specific tile from the
                                   // list and replace with a new one
  void deleteTile(Tile tile);
  void displayContents();
};

#endif  // ASSIGN2_LINKEDLIST_H
