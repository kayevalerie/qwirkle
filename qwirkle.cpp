#include <iostream>
#include "LinkedList.h"
#include "Player.h"

// Array
char arr_color[] = {'R', 'O', 'Y', 'G', 'P', 'B'};
int arr_shape[] = {1, 2, 3, 4, 5, 6};

int main(void) {
  
  //display welcome message
  //run 'display menu' method 
  //get user choice(get character method in the helper)
  //run appropriate method(if choice == 1->-get user input for the name of the players
  //                                       -create a new instance of the game class(run game constructor: 1 game, 1 board,
  //                                                                                 1 tile bag(linked list), 2 new players,
  //                                                                                 for each player initialize a linked list
  //                                                                                 with 6 tiles each taken from the tile bag,
  //                                                                                 initialize the score to 0)
  //                                       -display 'Let's play' message
  //                                       -run the while loop( while(!finished) display 'getCurrentPlayer(), it's your turn'
  //                                                             get user scores, display scores, display board, 
  //                                                             display current user's hand, display '>' for user prompt)
  //                                       -if out of the loop (display 'Goodbye' and exit)
  //                     (if choice == 2-> -get user input for the name of the file(check if the file exists and the format is corect)
  //                                       -create a new instance of the game class and set all the variables' values to the ones in
  //                                         the file
  //                                       -run regular while loop
  //                     (if choice == 3-> -display student's info
  //                                       -display menu)
  //                     (if choice == 4-> -display 'goodbye' 
  //                                       -exit)
  LinkedList* tileBag = new LinkedList();

  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      Tile* newTile = new Tile(arr_color[i], arr_shape[j]);

      tileBag->addTile(newTile);
      tileBag->addTile(newTile);
    }
  }
  tileBag->displayContents();

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
