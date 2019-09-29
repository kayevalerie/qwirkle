#include "Game.h"
#include <iostream>
#include <string>

Game::Game() {}

Game::Game(std::string playerOneName, std::string playerTwoName) : 
  playerOne(new Player(playerOneName)),
  playerTwo(new Player(playerTwoName)) {
  
  char arr_color[] = {'R', 'O', 'Y', 'G', 'P', 'B'};
  int arr_shape[] = {1, 2, 3, 4, 5, 6};
  LinkedList* unshuffledBag = new LinkedList();

  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      Tile* newTile = new Tile(arr_color[i], arr_shape[j]);

      unshuffledBag->addTile(newTile);
      unshuffledBag->addTile(newTile);
    }
  }
  
  //tileBag->displayContents();
  tileBag = unshuffledBag.shuffle();
 //what is being returned 
  //tileBag->displayContents();

  //for loop for getting 6 tiles for each of the players and setting the hands
  
  //set current player
  
 }
 
 Game::~Game() {
  clear();
  }
  
void run() {
  std::cout << "Let's play\n";
  
  while(!finished) {
    
  
  }

}

