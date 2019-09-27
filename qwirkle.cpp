#include <iostream>

#include "LinkedList.h"
#include "Player.h"

// Array
char arr_color[] = {'R', 'O', 'Y', 'G', 'P', 'B'};
int arr_shape[] = {1, 2, 3, 4, 5, 6};

int main(void) {
  LinkedList* tileBag = new LinkedList();

  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      Tile* newTile = new Tile(arr_color[i], arr_shape[j]);

      tileBag->addTile(newTile);
      tileBag->addTile(newTile);
    }
  }
  tileBag->displayContents();

  // shuffle contents of tileBag
  tileBag->shuffle();
  tileBag->displayContents();

  LinkedList* list = new LinkedList();
  // while loop here

  delete list;
  delete tileBag;

  return EXIT_SUCCESS;
}

int getPlayerChoice() {
  // todo

  // display menu here

  return -1;
}