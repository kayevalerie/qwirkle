#include <iostream>
#include "LinkedList.h"
#include "Player.h"
#include "Helper.h"

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
  //                                                             display current user's hand, display '>' for user prompt
  //                                                             get user prompt, check if command correct, run command, update 
  //                                                             data structures, change currentPlayer)
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

void newGameMenu()
{
    std::string player1Name;
    std::string player2Name;
    std::cout << "Starting a new game !\n"
              << "Enter A Name For Player 1: \n";
    
    //Placeholder for test

    std::cin >> player1Name;
    std::cout << std::endl;

    std::cout << "Enter A Name For Player 2: \n";
    
    //Placeholder for test
    
    std::cin >> player2Name;
    std::cout << std::endl;

    //initialise new game here

    std::cout << "Let's Play!\n";
}

void loadGameMenu()
{
    std::string fileName;
    std::cout << "Enter the filename of game you wish to load : \n";
    std::cin >> fileName;
    
    Help::Helper b;

    if (b.isValidFormat(fileName) == true)
    {

        std::cout << "Qwirkle game loaded succesfully. \n";

        //load game to previous state here
    }
    else
    {
        std::cout << "Invalid file!";
    }
}

void exitGame()
{
    std::cout << "Goodbye. \n";
}

void showStudentInfo()
{
    std::cout << "----------------------------------\n"
              << "Name: Tan Do\n"
              << "Student ID: s3712467\n"
              << "Email: s3712467@student.rmit.edu.au\n"
              << "\n"
              << "Name: Kay Ng\n"
              << "Student ID: s3766374\n"
              << "Email: s3766374@student.rmit.edu.au\n"
              << "\n"
              << "Name: Ewa Rusiecka\n"
              << "Student ID: s3797191\n"
              << "Email: s3797191@student.rmit.edu.au\n"
              << "\n"
              << "Name: Vincent Gallo\n"
              << "Student ID: s3602478\n"
              << "Email: s3602478@student.rmit.edu.au\n"
              << "----------------------------------\n";
}

void displayMainMenu()
{
    int choice = 0;
    do
    {
        std::cout << "\n"
                  << "Menu\n"
                  << "----\n"
                  << "1. New Game\n"
                  << "2. Load Game\n"
                  << "3. Show Student Information\n"
                  << "4. Quit\n"
                  << std::endl;

        std::cin >> choice;
        while (!std::cin >> choice)
        {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (choice == 1)
        {
            newGameMenu();
        }

        else if (choice == 2)
        {
            loadGameMenu();
        }

        else if (choice == 3)
        {
            showStudentInfo();
        }

        else if (choice == 4)
        {
            exitGame();
        }
        else
        {
            std::cout << "Invalid Input" << std::endl;
        }

    } while (choice != 4 && !std::cin.eof());

}
