#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Helper.h"

// input validation methods

namespace Helper {

bool isASCII(std::string n) {
  unsigned int i;

  for (i = 0; i < n.size(); i++) {
    if (isalpha(n[i]) == 0) {
      return false;
    }
  }
  return true;
}

bool isNumber(std::string h) {
  unsigned int i;

  for (i = 0; i < h.size(); i++) {
    if (isdigit(h[i]) == 0) {
      return false;
    }
  }
  return true;
}

bool isHandValid(std::string a) {
  std::string tile;
  while (a.good()) {
    getline(a, tile, ',');
    if (Game::isTileValid(tile) == false) {
      return false;
    }
  }
  return true;
}

bool isValidFormat(std::string fileName) {
  bool fileVal = true;
  bool nameVal = true;
  bool scoreVal = true;
  bool handVal = true;
  bool boardVal = true;
  bool bagVal = true;

  bool valid = false;
  std::fstream infile;
  infile.open(fileName);

  if (infile.fail()) {
    std::cout << "File Does Not Exist" << std::endl;
    fileVal = false;
  }

  std::string hold[50];
  std::string line;
  int count = 0;

  while (getline(infile, line)) {
    hold[count] = line;
    count++;
  }

  // validate name is ASCII - check each char of string

  if (isASCII(hold[0]) == false && isASCII(hold[3]) == false) {
    std::cout << hold[0] << std::endl;
    std::cout << hold[3] << std::endl;
    std::cout << "Incorrect Format - Name Must Only Contain Letters"
              << std::endl;
    nameVal = false;
  }

  // validate score is number
  else if (isNumber(hold[1]) == false && isNumber(hold[4]) == false) {
    std::cout << "Incorrect File Format - Score Not Number" << std::endl;
    scoreVal = false;
  }

  // validate player hands

  // change this (to check format)
  else if (isHandValid(hold[2]) == false && isHandValid(hold[5]) == false) {
    std::cout << "Incorrect File Format - Tile Hands" << std::endl;
    handVal = false;
  }

  // //validate board is same as cout

  // else if (hold[6].find){
  std::string test;
  std::vector<std::string> token;

  while (getline(hold[6], test, "    ")) {
    token.push_back(test);
  }
  for (int i = 0, i < token.size(), i++) {
    if (isNumber(token[i]) && token[0] == 0 && token[i + 1] == token[i] + 2) {
    }
  }

  int rowLength = hold[7].length();
  int dashCount = 0;
  if (rowLength > 0) {
    char dashRow[rowLength];
    strcpy(dashRow, hold[7].c_str());
    if (dashRow[0] == " " && dashRow[1] == " ") {
      for (int i = 2, i <= rowLength, i++) {
        dashRow[i] == "-";
        dashCount++;
      }
    }
  }
  std::vector<std::string> token2;
  while (getline(hold[8], test, "|")) {
    token.push_back(test);
  }

  // hold[6] to hold[14]

  //     }

  return (fileVal && nameVal && scoreVal && handVal && boardVal && handVal);
}

}  // namespace Helper
