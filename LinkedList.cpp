
#include "LinkedList.h"
#include <stdexcept>

LinkedList::LinkedList() {
  head = nullptr;
  tail = nullptr;
  list_size = 0;
}

LinkedList::~LinkedList() { clear(); }

int LinkedList::size() { return list_size; }

void LinkedList::clear() {
  Node* current = head;
  Node* next;

  while (current) {
    next = current->next;
    delete current;
    current = next;
  }

  list_size = 0;
}

Tile* LinkedList::getFront() { return head->tile; }

// Tile* LinkedList::get(int i) {
//   Node* current = head;
//   size_t index = 0;
//   Tile* found = nullptr;

//   if (i == 0) {  // if getting the start of the list
//     found = head->tile;
//   } else if (i == list_size - 1) {  // if getting the end of the list
//     found = tail->tile;
//   } else {
//     while (current && index < i) {
//       current = current->next;
//       index++;
//     }

//     if (i == index) found = current->tile;
//   }

//   return found;
// }

// void LinkedList::addFront(Tile* tile) {
//   if (list_size == 0) {
//     head = new Node(tile, nullptr);
//   } else {
//     Node* node = new Node(tile, head->next);
//     head = node;
//   }

//   list_size++;
// }

void LinkedList::addTile(Tile* tile) {
  Node* temp = new Node(tile, nullptr);

  if (list_size == 0) {  // if list is empty
    tail = temp;
    head = tail;
  } else {
    tail->next = temp;
    tail = temp;  // set new tail pointer
  }

  list_size++;
}

bool LinkedList::contains(Tile* tile) {
  bool found = false;

  Node* current = head;

  while (!found && current) {
    if (current->tile->equals(tile)) {
      found = true;
    }
    current = current->next;
  }

  return found;
}

void LinkedList::deleteFront() {
  if (list_size > 0) {
    Node* prevHead = head;
    head = head->next;
    delete prevHead;
    list_size--;
  } else {
    // error: no tile to remove
  }
}

void LinkedList::deleteTile(Tile* tile) {
  bool found = false;
  if (head == nullptr) {
    // error: nothing to delete
  } else {
    if (tile->equals(head->tile)) {  // if tile to delete is at head
      deleteFront();
    } else {  // if tile to delete is at the end or in the middle
      Node* current = head->next;
      Node* prev = current;

      while (!found && current) {
        if (current->tile->equals(tile)) {
          prev->next = current->next;
          delete current;
          list_size--;
          found = true;
        }
        prev = current;
        current = current->next;
      }
    }
  }
}

void displayContents() {
  // todo
}