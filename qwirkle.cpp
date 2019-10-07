#include <iostream>

#include "Game.h"
#include "Helper.h"

void displayMenu();
void showStudentInfo();
void loadGameMenu();
void newGameMenu();
void exitGame();

int main(void) {

  std::cout << "Welcome to Qwirkle!\n";
  displayMenu();
  exitGame();

  return EXIT_SUCCESS;
}

void displayMenu() {
  int choice = 0;
  bool quit = false;

  do {
    std::cout << "\n"
              << "Menu\n"
              << "-------\n"
              << "1. New Game\n"
              << "2. Load Game\n"
              << "3. Show student information\n"
              << "4. Quit\n"
              << "\n> ";

    std::cin >> choice;

    while (!std::cin >> choice) {
      std::cin.clear();
      std::cin.ignore(100, '\n');
    }

    if (choice == 1)
      newGameMenu();
    else if (choice == 2)
      loadGameMenu();
    else if (choice == 3)
      showStudentInfo();
    else if (choice == 4)
      exitGame();
    else if (std::cin.eof())
      quit = true;
    else
      std::cout << "This option does not exist, please try again\n";

  } while (!quit && choice != 4);
}

void newGameMenu() {
  std::string player1Name;
  std::string player2Name;
  std::cout << "\nStarting a new game of Qwirkle!\n";

  int end1 = 0;
  while (!end1) {
    std::cout << "\nEnter a name for player 1: \n";
    std::cout << "\n> ";
    
    while (std::cin.peek() == '\n') {
      std::cout << "Please input the name\n> ";
      std::cin.ignore();
    }
    std::cin >> player1Name;

    if (!Helper::isASCII(player1Name)) {
      std::cout << "Error: name must only contain letters. Please input your "
                   "name again\n";
                  //needs a test case
    } else {
      end1 = 1;
    }
  }

  std::cout << std::endl;


  int end2 = 0;
  while (!end2) {
    std::cout << "\nEnter a name for player 2: \n";
    std::cout << "\n> ";
    
    while (std::cin.peek() == '\n') {
      std::cout << "Please input the name\n> ";
      std::cin.ignore();
    }
    std::cin >> player2Name;

    if (!Helper::isASCII(player2Name)) {
      std::cout << "Error: name must only contain letters. Please input your "
                   "name again\n";
    } else {
      end2 = 1;
    }
  }
  std::cout << std::endl;

  std::cout << "Let's play!" << std::endl;

  Game game(player1Name, player2Name);
  game.run();
}

void loadGameMenu() {
  std::string fileName;
  bool valid = false;
  std::cout << "Enter the name of the file from which to load the game:\n";
  while (!valid) {
    do {
      std::cin >> fileName;
    } while (std::cin.good() && !std::cin.eof());
    if (Helper::isValidFormat(fileName)) {
        Game game("test", "test2");
        std::cout << "Qwirkle game loaded successfully. \n";
        valid = true;
        game.run();
    } else {
      std::cout << "The format of this file is not correct. Please try again\n";
    }
  }
}

void exitGame() { std::cout << "\n\nGoodbye! \n"; }

void showStudentInfo() {
  std::cout << "----------------------------------\n"
            << "Name: Tan Do\n"
            << "Student ID: s3712467\n"
            << "Email: s3712467@student.rmit.edu.au\n"
            << "\n"
            << "Name: Kaye Ng\n"
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
