
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

Tile* LinkedList::get(int i) {
  Node* current = head;
  size_t index = 0;
  Tile* found = nullptr;

  if (i == 0) {  // if getting the start of the list
    found = head->tile;
  } else if (i == list_size - 1) {  // if getting the end of the list
    found = tail->tile;
  } else {
    while (current && index < i) {
      current = current->next;
      index++;
    }

    if (i == index) found = current->tile;
  }

  return found;
}

void LinkedList::addFront(Tile* tile) {
  if (list_size == 0) {
    head = new Node(tile, nullptr);
  } else {
    Node* node = new Node(tile, head->next);
    head = node;
  }

  list_size++;
}

void LinkedList::addBack(Tile* tile) {
  if (list_size == 0) {
    tail = new Node(tile, nullptr);
  } else {
    tail->next = new Node(tile, nullptr);
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

void LinkedList::deleteFront() { throw std::runtime_error("Not Implemented"); }

void LinkedList::deleteBack() { throw std::runtime_error("Not Implemented"); }
