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

bool isValidFormat(std::string fileName) {
  std::fstream infile;
  infile.open(fileName);

  if (infile.fail()) {
    std::cout << "File Does Not Exist" << std::endl;
    return false;
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
    return false;
  }

  // validate score is number
  else if (isNumber(hold[1]) == false && isNumber(hold[4]) == false) {
    std::cout << "Incorrect File Format - Score Not Number" << std::endl;
    return false;
  }

  // std::stringstream p1h(hold[2]);
  // std::stringstream p2h(hold[5]);
  // std::stringstream tbc(hold[7]);

  // validate player hands and tilebags is comma seperated list
  //     else if (hold[2] || hold[5] || hold[7]){

  //     }

  // //validate board is same as cout
  //     else if (hold[6]){

  //     }

  return true;
}

}  // namespace Helper
