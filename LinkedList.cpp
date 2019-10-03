
#include "LinkedList.h"
#include <stdlib.h>
#include <iostream>
#include <random>

LinkedList::LinkedList() : head(nullptr), tail(nullptr), list_size(0) {}

LinkedList::LinkedList(const LinkedList& src)
    : head(nullptr), tail(nullptr), list_size(0) {
  Node* current = src.head;

  while (current) {
    addTile(new Tile(*(current->getTile())));
    current = current->next;
  }
}

LinkedList::~LinkedList() { clear(); }

void LinkedList::clear() {
  Node* current = head;
  Node* next = nullptr;

  while (current) {
    next = current->next;
    delete current;
    current = next;
  }

  list_size = 0;
}

int LinkedList::getSize() { return list_size; }

Tile* LinkedList::getFront() { return head->getTile(); }

Tile* LinkedList::get(unsigned int i) {
  Tile* tile = nullptr;

  if (i == 0) {
    tile = head->getTile();
  } else if (i == list_size - 1) {
    tile = tail->getTile();
  } else if (i < list_size) {
    Node* current = head->next;
    unsigned int index = 1;

    while (index < i) {
      current = current->next;
      index++;
    }
    tile = current->getTile();
  } else {
    // error: invalid index
  }

  return tile;
}

bool LinkedList::contains(Tile* tile) {
  bool found = false;
  Node* current = head;

  while (!found && current) {
    if (current->getTile()->equals(tile)) {
      found = true;
    }
    current = current->next;
  }

  return found;
}

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

void LinkedList::deleteFront() {
  if (list_size > 0) {
    if (list_size == 1) {  // if there's only one element in the list
      delete head;
      head = nullptr;
      tail = nullptr;
    } else {
      Node* prevHead = head;
      head = head->next;
      delete prevHead;
      list_size--;
    }
  } else {
    // error: list is empty
  }
}

void LinkedList::deleteAt(unsigned int i) {
  if (i == 0) {
    deleteFront();
  } else if (i < list_size) {  // delete at the end or in the middle
    Node* current = head->next;
    Node* prev = head;
    unsigned int index = 1;

    while (index < i) {
      prev = current;
      current = current->next;
      index++;
    }

    if (!current->next) {  // deleting the last node in the list
      prev->next = nullptr;
      tail = prev;
    } else {
      prev->next = current->next;
    }

    delete current;
    list_size--;

  } else {
    // error: invalid index
  }
}

void LinkedList::replaceTile(Tile* tile, Tile* newTile) {
  if (list_size == 0) {
    // error: list is empty
  } else {
    bool found = false;
    Node* newNode = new Node(newTile, nullptr);

    if (tile->equals(head->getTile())) {  // if tile to delete is at head
      deleteFront();
    } else {  // if tile to delete is at the end or in the middle
      Node* current = head;
      Node* prev = nullptr;

      while (!found && current) {
        if (current->getTile()->equals(tile)) {
          found = true;
        } else {
          prev = current;
          current = current->next;
        }
      }

      if (found) {
        prev->next = newNode;

        // if the element to replace is the last element in the list
        if (!current->next) {
          // set it as the new tail
          tail = newNode;
        } else {
          newNode->next = current->next;
        }

        delete current;
      }
    }
  }
}

void LinkedList::displayContents() {
  if (list_size > 0) {  // if list is not empty
    Node* current = head;
    unsigned int i = 0;

    while (i < list_size) {
      std::cout << current->getTile()->toString();

      if (i != list_size - 1) std::cout << ",";

      current = current->next;
      i++;
    }

    std::cout << std::endl;
  }
}

void LinkedList::shuffle() {
  int min = 0;
  int max = list_size;
  int seed = 98;
  std::default_random_engine engine(seed);
  // int value = -1;

  for (unsigned int i = 0; i < list_size; i++) {
    std::uniform_int_distribution<int> uniform_dist(min, max);
    int randomIndex = uniform_dist(engine);
    Tile* toBeShuffled = get(randomIndex);
    deleteAt(randomIndex);
    addTile(toBeShuffled);
    min++;
  }
}