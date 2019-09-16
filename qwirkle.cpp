
#include "LinkedList.h"
#include "Player.h"

#include <iostream>

#define EXIT_SUCCESS 0

int main(void) {
  LinkedList* list = new LinkedList();
  delete list;

  return EXIT_SUCCESS;
}

int getPlayerChoice() {
  // todo
  // display menu here

  return -1;
}

bool hasNoTilesLeft(Player player) {
  // todo
  return false;
}

bool isTileBagEmpty() {
  // todo

  return false;
}
