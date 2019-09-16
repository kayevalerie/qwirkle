
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
 public:
  LinkedList();
  ~LinkedList();

  int size();
  void clear();
  int get(int i);

  void addFront(int data);
  void addBack(int data);

  bool contains(int value);
  void deleteFront();
  void deleteBack();

  void displayContents();

 private:
  Node* head;
};

#endif  // ASSIGN2_LINKEDLIST_H
