
#include "LinkedList.h"

#include <iostream>
#include <random>

LinkedList::LinkedList() : head(nullptr), tail(nullptr), list_size(0) {}

LinkedList::LinkedList(const LinkedList& toCopy)
    : head(nullptr), tail(nullptr), list_size(0) {
  Node* current = toCopy.head;

  while (current) {
    addTile(current->getTile());
    current = current->getNext();
  }
}

LinkedList::~LinkedList() { clear(); }

void LinkedList::clear() {
  Node* current = head;
  Node* next = nullptr;

  while (current) {
    next = current->getNext();
    delete current;
    current = next;
  }

  list_size = 0;
}

int LinkedList::getSize() { return list_size; }

Tile LinkedList::getFront() { return head->getTile(); }

Node* LinkedList::get(unsigned int i) {
  Node* node = nullptr;

  if (i == 0) {
    node = head;
  } else if (i == list_size - 1) {
    node = tail;
  } else if (i < list_size) {
    Node* current = head->getNext();
    unsigned int index = 1;

    while (index < i) {
      current = current->getNext();
      index++;
    }
    node = current;
  } else {
    // error: invalid index
  }

  return node;
}

bool LinkedList::contains(Tile tile) {
  bool found = false;
  Node* current = head;

  while (!found && current) {
    if (current->getTile().equals(tile)) {
      found = true;
    }
    current = current->getNext();
  }

  return found;
}

void LinkedList::addTile(Tile tile) {
  Node* temp = new Node(tile, nullptr);

  if (list_size == 0) {  // if list is empty
    tail = temp;
    head = tail;
  } else {
    tail->setNext(temp);
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
      head = head->getNext();
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
    Node* current = head->getNext();
    Node* prev = head;
    unsigned int index = 1;

    while (index < i) {
      prev = current;
      current = current->getNext();
      index++;
    }

    if (!current->getNext()) {  // deleting the last node in the list
      prev->setNext(nullptr);
      tail = prev;
    } else {
      prev->setNext(current->getNext());
    }

    delete current;
    list_size--;

  } else {
    // error: invalid index
  }
}

void LinkedList::replaceTile(Tile tile, Tile newTile) {
  if (list_size == 0) {
    // error: list is empty
  } else {
    bool found = false;
    Node* newNode = new Node(newTile, nullptr);

    if (tile.equals(head->getTile())) {  // if tile to delete is at head
      newNode->setNext(head->getNext());
      delete head;
      head = newNode;
    } else {  // if tile to delete is at the end or in the middle
      Node* current = head;
      Node* prev = nullptr;

      while (!found && current) {
        if (current->getTile().equals(tile)) {
          found = true;
        } else {
          prev = current;
          current = current->getNext();
        }
      }

      if (found) {
        prev->setNext(newNode);

        // if the element to replace is the last element in the list
        if (!current->getNext()) {
          // set it as the new tail
          tail = newNode;
        } else {
          newNode->setNext(current->getNext());
        }

        delete current;
      }
    }
  }
}

void LinkedList::deleteTile(Tile tile) {
  if (list_size == 0) {
    // error: list is empty
  } else if (contains(tile)) {
    bool found = false;

    if (tile.equals(head->getTile())) {  // if tile to delete is at head
      deleteFront();
    } else {  // if tile to delete is at the end or in the middle
      Node* current = head;
      Node* prev = nullptr;

      while (!found && current) {
        if (current->getTile().equals(tile)) {
          found = true;
        } else {
          prev = current;
          current = current->getNext();
        }
      }

      if (found) {
        // if the element to delete is the last element in the list
        if (!current->getNext())
          tail = prev;  // set the previous node as the new tail

        prev->setNext(current->getNext());
        delete current;
        list_size--;
      }
    }
  } else {
    // error: element was not found
  }
}

void LinkedList::displayContents() {
  if (list_size > 0) {  // if list is not empty
    Node* current = head;
    unsigned int i = 0;

    while (i < list_size) {
      std::cout << current->getTile().toString();

      if (i != list_size - 1) std::cout << ",";

      current = current->getNext();
      i++;
    }

    std::cout << "\n";
  }
}

void LinkedList::shuffle() {
  int minS = 0;
  int maxS = 200;
  int seedS = 100;

  std::default_random_engine engineS(seedS);
  std::uniform_int_distribution<int> uniform_distS(minS, maxS);
  int seed = uniform_distS(engineS);

  int min = 0;
  int max = list_size;
  std::default_random_engine engine(seed);

  for (unsigned int i = 0; i < list_size; i++) {
    std::uniform_int_distribution<int> uniform_dist(min, max);
    int randomIndex = uniform_dist(engine);
    Node* toBeShuffled = get(randomIndex);
    addTile(toBeShuffled->getTile());
    deleteAt(randomIndex);
    max--;
  }
}