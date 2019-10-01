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
  
  std::cout<<"Welcome to Qwirkle!\n";
  displayMenu();
  exitGame();

  return EXIT_SUCCESS;
}

void displayMenu()
{
    int choice = 0;
    do
    {
        std::cout << "\n"
                  << "Menu\n"
                  << "-------\n"
                  << "1. New Game\n"
                  << "2. Load Game\n"
                  << "3. Show student information\n"
                  << "4. Quit\n"
                  << "\n>"
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
            loadGame();
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
            std::cout << "This option does not exist, please try again" << std::endl;
        }

    } while (choice != 4 && !std::cin.eof());

}

void newGameMenu()
{
    std::string player1Name;
    std::string player2Name;
    std::cout << "Starting a new game of Qwirkle!\n"
              << "Enter a name for player 1: \n";
    
    //Placeholder for test
  
    std::cout << "> ";

    std::cin >> player1Name;
  //better input handling needed
    std::cout << std::endl;

    std::cout << "Enter a name for player 2: \n";
    
    //Placeholder for test
    
    std::cout << "> ";
    std::cin >> player2Name;
  //better input handling needed
    std::cout << std::endl;

    Game game = new Game(player1Name, player2Name);
    game.run();
}

void loadGameMenu()
{
    std::string fileName;
    std::cout << "Enter the name of the file from which to load the game\n";
    std::cin >> fileName;
    
    Help::Helper b;

    //
    if (b.isValidFormat(fileName) == true)
    {

        std::cout << "Qwirkle game loaded succesfully. \n";
        //need a method that goes through the file line by line and initializes the variables and data structures
        Game game = new Game();
        game.run();
    }
    else
    {
        std::cout << "The format of this file is not correct. Please try again";
    }
}

void exitGame()
{
    std::cout << "Goodbye! \n";
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


