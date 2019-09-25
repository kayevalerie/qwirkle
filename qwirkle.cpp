
#include "LinkedList.h"
#include "Player.h"
#include <vector>
#include <iostream>
//#include <Tile.h>
//#include <Node.h>

using std::vector;

// Array
char arr_color [] = {'R','O','Y','G','P','B'};
int arr_shape [] = {1,2,3,4,5,6};
//
//char TileBag[] = {};
//

const int MAX_TILE = 72;
std::vector<Tile *> t;


int main(void) {
//  for(int i = 0; i <= arr_shape.size; ++i){
//      char temp = arr_color[i] + arr_shape[i];
//      TileBag[i] = temp;
//  }
/////////////////////////////////////////////

    LinkedList* tileBag = new LinkedList();
for (int i = 0; i < 6 ; ++i){
    for(int j = 0; j < 6; ++j){
        tileBag->addTile(new Tile(arr_color[j], arr_shape[j]));
        tileBag->addTile(new Tile(arr_color[j], arr_shape[j]));
        // t.push_back(new Tile(arr_color[j], arr_shape[j]));
        //t.push_back(new Tile(arr_color[j], arr_shape[j]));
    }
}
tileBag->displayContents();
//for (unsigned int i = 0; i < t.size(); ++i){
//    tileBag -> addTile(t[i]);
//}
//////////////////////////////////////////////
//  bool player1Turn = true;
//  bool gameOver = false;
//  char userChoice;
  /////////////////////////////////////
  LinkedList* list = new LinkedList();
  // while loop here

  delete list;

  return EXIT_SUCCESS;
}

int getPlayerChoice() {
  // todo

  // display menu here

  return -1;
}